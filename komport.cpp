/**************************************************************************
*   Author <mike@8bitgeek.net> Mike Sharkey                               *
*   Copyright (C) 2010 by Pike Aerospace Research Corporation             *
*                                                                         *
*   This program is free software: you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation, either version 3 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
**************************************************************************/
#include "komport.h"
#include "ui_komport.h"
#include "ui_settingsdialog.h"

#include "cemulationANSI.h"
#include "cemulationVT102.h"

#include <QMessageBox>
#include <QSettings>
#include <QColorDialog>
#include <QClipboard>
#include <QFileDialog>
#include <QFile>
#include <QByteArray>
#include <QProgressDialog>
#include <QTime>
#include <QElapsedTimer>
#include <QProcess>

#ifdef Q_OS_WIN32
	#include <QWindowsStyle>
#endif

#define BANNER tr("Komport ")+QString(KOMPORT_VERSION)+tr(" Serial Communications")
#define COPYRIGHT "Copyright (c) 2011-2020 by Mike Sharkey &lt;mike@8bitgeek.net&gt;"
#define WEBSITE "https://github.com/8bitgeek/komport"

#define CHUNK_SIZE	64

Komport::Komport(QWidget *parent)
: QMainWindow(parent)
, mSerial(NULL)
, mScreen(NULL)
, mEmulation(NULL)
, ui(new Ui::Komport)
, settingsUi(new Ui::SettingsDialog)
, mRxLED(NULL)
, mTxLED(NULL)
{
	ui->setupUi(this);
	settingsUi->setupUi(&settingsDialog);
	QObject::connect(settingsUi->BackgroundColorButton,SIGNAL(clicked()),this,SLOT(openBackgroundColorDialog()));
	QObject::connect(settingsUi->ForegroundColorButton,SIGNAL(clicked()),this,SLOT(openForegroundColorDialog()));
	QObject::connect(settingsUi->buttonHelp,SIGNAL(clicked()),this,SLOT(settingsHelp()));

	#ifdef Q_OS_WIN32
		settingsUi->DeviceComboBox->clear();
		settingsUi->DeviceComboBox->addItem("COM1:");
		settingsUi->DeviceComboBox->addItem("COM2:");
		settingsUi->DeviceComboBox->addItem("COM3:");
		settingsUi->DeviceComboBox->addItem("COM4:");
		settingsUi->DeviceComboBox->addItem("COM5:");
		settingsUi->DeviceComboBox->addItem("COM6:");
		settingsUi->DeviceComboBox->addItem("COM7:");
		settingsUi->DeviceComboBox->addItem("COM8:");
		settingsUi->DeviceComboBox->setCurrentIndex(0);
	#endif

	statusBar()->addPermanentWidget((mRxLED = new CLed()));
	statusBar()->addPermanentWidget((mTxLED = new CLed()));

	createActions();
	createMenus();
	createToolBars();
	createStatusBar();

	this->setWindowIcon(QIcon(":/images/terminal.png"));

	readSettings();
}

Komport::~Komport()
{
	serial()->close();
	delete mSerial;
	delete ui;
}

void Komport::readSettings()
{
	QSettings settings( QSettings::IniFormat, QSettings::UserScope, "8bit.zapto.org", "komport-1.1" );
	settings.beginGroup("main");
		restoreGeometry(settings.value("geometry").toByteArray());
		restoreState(settings.value("windowState").toByteArray());
	settings.endGroup();

	settings.beginGroup("device");
		QString device	= settings.value("device",		settingsUi->DeviceComboBox->currentText()).toString();
		int		baud	= settings.value("baud",		settingsUi->BaudRateComboBox->currentText().toInt()).toInt();
		int		dbits	= settings.value("dbits",		settingsUi->DataBitsComboBox->currentText().toInt()).toInt();
		int		sbits	= settings.value("sbits",		settingsUi->StopBitsComboBox->currentText().toInt()).toInt();
		QString parity	= settings.value("parity",		settingsUi->ParityComboBox->currentText()).toString();
		QString flow	= settings.value("flow",		settingsUi->FlowControlComboBox->currentText()).toString();
	settings.endGroup();

	settings.beginGroup("terminal");
		QString emulation		= settings.value("emulation",	settingsUi->EmulationComboBox->currentText()).toString();
		int		cols			= settings.value("cols",		settingsUi->ColumnsSpinBox->value()).toInt();
		int		rows			= settings.value("rows",		settingsUi->RowsSpinBox->value()).toInt();
		bool	visualbell		= settings.value("visualbell",	settingsUi->VisualBellCheckBox->isChecked()).toBool();
		bool	localecho		= settings.value("localecho",	settingsUi->LocalEchoCheckBox->isChecked()).toBool();
		QRgb	backgroundColor = settings.value("background",	settingsUi->BackgroundColorButton->palette().color(QPalette::Button).rgb()).toUInt();
		QRgb	foregroundColor = settings.value("foreground",	settingsUi->ForegroundColorButton->palette().color(QPalette::Button).rgb()).toUInt();
	settings.endGroup();

	if ( mScreen != NULL ) delete mScreen;
	if ( mSerial != NULL ) delete mSerial;
	if ( mEmulation != NULL ) delete mEmulation;

	settingsUi->DeviceComboBox->setEditText(device);
	settingsUi->BaudRateComboBox->setCurrentIndex(settingsUi->BaudRateComboBox->findText(QString::number(baud)));
	settingsUi->FlowControlComboBox->setCurrentIndex(settingsUi->FlowControlComboBox->findText(flow));
	settingsUi->ParityComboBox->setCurrentIndex(settingsUi->ParityComboBox->findText(parity));
	settingsUi->DataBitsComboBox->setCurrentIndex(settingsUi->DataBitsComboBox->findText(QString::number(dbits)));
	settingsUi->StopBitsComboBox->setCurrentIndex(settingsUi->StopBitsComboBox->findText(QString::number(sbits)));
	settingsUi->EmulationComboBox->setCurrentIndex(settingsUi->EmulationComboBox->findText(emulation));
	settingsUi->ColumnsSpinBox->setValue(cols);
	settingsUi->RowsSpinBox->setValue(rows);
	settingsUi->VisualBellCheckBox->setChecked(visualbell);
	settingsUi->LocalEchoCheckBox->setChecked(localecho);
	QPalette backgroundPalette = settingsUi->BackgroundColorButton->palette();
	backgroundPalette.setColor(QPalette::Button,QColor::fromRgb(backgroundColor));
	settingsUi->BackgroundColorButton->setPalette(backgroundPalette);
	QPalette foregroundPalette = settingsUi->ForegroundColorButton->palette();
	foregroundPalette.setColor(QPalette::Button,QColor::fromRgb(foregroundColor));
	settingsUi->ForegroundColorButton->setPalette(foregroundPalette);

	settingsUi->BackgroundColorButton->setStyleSheet("QPushButton {background-color:#"+colorToHex(backgroundColor)+"; }");
	settingsUi->ForegroundColorButton->setStyleSheet("QPushButton {background-color:#"+colorToHex(foregroundColor)+"; }");

	mScreen = new CScreen();

	screen()->setDefaultForegroundColor(QColor::fromRgb(foregroundColor));
	screen()->setDefaultBackgroundColor(QColor::fromRgb(backgroundColor));

	screen()->setForegroundColor(QColor::fromRgb(foregroundColor));
    screen()->setBackgroundColor(QColor::fromRgb(backgroundColor));

	setCentralWidget(screen());
	screen()->setEnabled(true);

	mSerial = new CSerial(device);
	if ( emulation == "VT102" )
	{
		mEmulation = new CEmulationVT102(screen());
		mEmulation->setVisualBell(visualbell);
		mEmulation->setLocalEcho(localecho);
		mEmulation->setGrid(cols,rows);
	}
	else
	if ( emulation == "ANSI" )
	{
		mEmulation = new CEmulationANSI(screen());
		mEmulation->setVisualBell(visualbell);
		mEmulation->setLocalEcho(localecho);
		mEmulation->setGrid(cols,rows);
	}
	else
	{
		QMessageBox::warning(this, "No Emulation", "Emulation '"+emulation+"' not supported.");
	}
	QObject::connect(mSerial,SIGNAL(beginRx()),this,SLOT(rxLedOn()));
	QObject::connect(mSerial,SIGNAL(endRx()),this,SLOT(rxLedOff()));
	QObject::connect(mSerial,SIGNAL(beginTx()),this,SLOT(txLedOn()));
	QObject::connect(mSerial,SIGNAL(endTx()),this,SLOT(txLedOff()));
	screen()->setCursorPos(0,0);

	if ( openSerial() )
	{
		serial()->setLineControl(baud,dbits,sbits,parity,flow);
	}
	screen()->setContextMenuPolicy(Qt::ActionsContextMenu);
	screen()->addAction(copyAct);
	screen()->addAction(pasteAct);
}

void Komport::writeSettings()
{
	QSettings settings( QSettings::IniFormat, QSettings::UserScope, "8bit.zapto.org", "komport-1.1" );
	settings.beginGroup("main");
		settings.setValue("geometry", saveGeometry());
		settings.setValue("windowState", saveState());
	settings.endGroup();

	settings.beginGroup("device");
		settings.setValue("device",	settingsUi->DeviceComboBox->currentText() );
		settings.setValue("baud",	settingsUi->BaudRateComboBox->currentText().toInt() );
		settings.setValue("dbits",	settingsUi->DataBitsComboBox->currentText().toInt() );
		settings.setValue("sbits",	settingsUi->StopBitsComboBox->currentText().toInt() );
		settings.setValue("parity",	settingsUi->ParityComboBox->currentText() );
		settings.setValue("flow",	settingsUi->FlowControlComboBox->currentText() );
	settings.endGroup();

	settings.beginGroup("terminal");
		settings.setValue("emulation",	settingsUi->EmulationComboBox->currentText() );
		settings.setValue("cols",		settingsUi->ColumnsSpinBox->value());
		settings.setValue("rows",		settingsUi->RowsSpinBox->value());
		settings.setValue("visualbell",	settingsUi->VisualBellCheckBox->isChecked());
		settings.setValue("localecho",	settingsUi->LocalEchoCheckBox->isChecked());
		settings.setValue("foreground", screen()->foregroundColor().rgb());
		settings.setValue("background", screen()->backgroundColor().rgb());
	settings.endGroup();

}

/** Key press handler */
void Komport::keyPressEvent(QKeyEvent *e)
{
	emulation()->keyPressEvent(e);
}

/** Edit->Copy */
void Komport::doCopy()
{
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(screen()->selectedText());
}

/** Edit->Paste */
void Komport::doPaste()
{
	QClipboard *clipboard = QApplication::clipboard();
	QString text = clipboard->text();
    serial()->sendAsciiString(text.toLatin1().data());
}

void Komport::createActions()
{
	exitAct = new QAction(QIcon(":/images/exit.png"),tr("E&xit"), this);
	exitAct->setShortcut(tr("Ctrl+Shift+Q"));
	exitAct->setStatusTip(tr("Exit Komport"));
	QObject::connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	copyAct = new QAction(QIcon(":/images/editcopy.png"), tr("&Copy"), this);
	copyAct->setShortcut(tr("Ctrl+Shift+C"));
	copyAct->setStatusTip(tr("Copy the current selection's contents to the clipboard."));
	QObject::connect(copyAct,SIGNAL(triggered()),this,SLOT(doCopy()));

	pasteAct = new QAction(QIcon(":/images/editpaste.png"), tr("&Paste"), this);
	pasteAct->setShortcut(tr("Ctrl+Shift+V"));
	pasteAct->setStatusTip(tr("Paste the clipboard's contents."));
	QObject::connect(pasteAct,SIGNAL(triggered()),this,SLOT(doPaste()));

	settingsAct = new QAction(QIcon(":/images/settings.png"), tr("Se&ttings"), this);
	settingsAct->setShortcut(tr("Ctrl+Shift+T"));
	settingsAct->setStatusTip(tr("Edit Kompotr settings"));
	QObject::connect(settingsAct, SIGNAL(triggered()), this, SLOT(editSettings()));

	aboutAct = new QAction(QIcon(":/images/about.png"),tr("&About"), this);
	aboutAct->setStatusTip(tr("Show information about Komport"));
	QObject::connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

	copyAct->setEnabled(true);
	pasteAct->setEnabled(true);
}

void Komport::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));

	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(copyAct);
	editMenu->addAction(pasteAct);

	configMenu = menuBar()->addMenu(tr("&Configuration"));
	configMenu->addAction(settingsAct);

	menuBar()->addSeparator();

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAct);
}

void Komport::createToolBars()
{
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->setObjectName("FileToolBar");
	fileToolBar->addAction(exitAct);
	fileToolBar->addSeparator();

	editToolBar = addToolBar(tr("Edit"));
	editToolBar->setObjectName("EditToolBar");
	editToolBar->addAction(copyAct);
	editToolBar->addAction(pasteAct);

	configToolBar = addToolBar(tr("Configuration"));
	configToolBar->setObjectName("ConfigToolBar");
	configToolBar->addAction(settingsAct);
}

void Komport::createStatusBar()
{
	statusBar()->showMessage(tr("Ready"));
}

void Komport::closeEvent(QCloseEvent *event)
{
	writeSettings();
	if ( serial() != NULL && serial()->isOpen() )
	{
		serial()->close();
	}
	event->accept();
}

void Komport::about()
{
	QMessageBox::about( this, BANNER,
				QString ("<br />"
				"<b>"+QString(BANNER)+"<br />"+QString(COPYRIGHT)+"<br /></b>"
				"All rights reserved.<br />"
				"<br /><a href=\""+QString(WEBSITE)+"\">"+QString(WEBSITE)+"</a><br />"
				"<br />"
				"This program is free software; you can redistribute it and/or modify<br />"
				"it under the terms of the GNU General Public License as published by<br />"
				" the Free Software Foundation; either version 2 of the License, or <br />"
				"(at your option) any later version. <br />"
				"<br />"
				"This program is distributed in the hope that it will be useful,    <br />"
				"but WITHOUT ANY WARRANTY; without even the implied warranty of<br />"
				" MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the <br />"
				"GNU General Public License for more details.   <br />"
				"<br />"
				"You should have received a copy of the GNU General Public License  <br />"
				"along with this program; if not, write to the  <br />"
				"<b>"
				"Free Software Foundation, Inc.,<br />"
				"59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. <br />"
				"</b>"
				"<br />"));
}

void Komport::settingsHelp()
{
	QMessageBox::about( this, "Komport Serial Communications - Settings Help",
				QString (
				"<b><u>Terminal Tab</u></b><br /><br />"
				"<b>Emulation</b>: Select the terminal type to emulate.<br /><br />"
				"<b>Visual Bell</b>: If enabled, flahses the screen rather than ringing the audio bell in response to the ascii BEL character.<br /><br />"
				"<b>Local Echo</b>: If enabled, echo characters to the screen as they are typed.<br /><br />"
				"<b>Cols/Rows</b>: Defines the screen size in character columns and rows.<br /><br />"
				"<b>Background/Foreground</b>: Defines the foreground and background color of the screen area.<br /><br />"
				"<b><u>Device Tab</u></b><br /><br />"
				"<b>Device</b>: Used to select the operating system logical device for performing serial data input/output.<br /><br />"
				"<b>Baud Rate</b>: The bit rate to transmit and receive in terms of bits per second.<br /><br />"
				"<b><u>Framing</u></b><br /><br />"
				"<b>Data bits</b>: The number of data bits in a character.<br /><br />"
				"<b>Stop bits</b>: The number of stop bits in a character.<br /><br />"
				"<b>Parity</b>: Parity bit interpretation NONE/EVEN/ODD.<br /><br />"
				"<b>Flow Control</b>: Data flow control method NONE/[XON/XOFF]/[RTS/CTS].<br /><br />"
				"<br />")
				);

}

void Komport::editSettings()
{
	if ( settingsDialog.exec() == QDialog::Accepted )
	{
		writeSettings();
		readSettings();
	}
}

void Komport::openBackgroundColorDialog()
{
	QColorDialog dialog;
	if ( dialog.exec() == QDialog::Accepted )
	{
		QPalette backgroundPalette = settingsUi->BackgroundColorButton->palette();
		QColor color = dialog.selectedColor();
		backgroundPalette.setColor(QPalette::Button,color);
		backgroundPalette.setColor(QPalette::Window,color);
		settingsUi->BackgroundColorButton->setPalette(backgroundPalette);
		settingsUi->BackgroundColorButton->update();
		settingsUi->BackgroundColorButton->setStyleSheet("QPushButton {background-color:#"+colorToHex(color)+"; }");
		screen()->setDefaultBackgroundColor(color);
		screen()->setBackgroundColor(color);
		screen()->update();
	}
}

void Komport::openForegroundColorDialog()
{
	QColorDialog dialog;
	if ( dialog.exec() == QDialog::Accepted )
	{
		QPalette foregroundPalette = settingsUi->ForegroundColorButton->palette();
		QColor color = dialog.selectedColor();
		foregroundPalette.setColor(QPalette::Button,color);
		foregroundPalette.setColor(QPalette::Window,color);
		settingsUi->ForegroundColorButton->setPalette(foregroundPalette);
		settingsUi->ForegroundColorButton->update();
		settingsUi->ForegroundColorButton->setStyleSheet("QPushButton {background-color:#"+colorToHex(color)+"; }");
		screen()->setDefaultForegroundColor(color);
		screen()->setForegroundColor(color);
		screen()->update();
	}
}

/**
  * Convert a QColor to a hex ascii string suitable for style sheet
  */
QString Komport::colorToHex(QColor c)
{
	QString hex;
	hex.asprintf("%02x%02x%02x", c.red(), c.green(), c.blue() );
	return hex;
}

/**
  * @brief Open the serial port and notify of there was any trouble
  */
bool Komport::openSerial()
{
	if ( serial()->open() )
	{
		connectSerialToEmulation();
		return true;
	}
	QMessageBox::warning(this, "Open Failed", "Open '"+settingsUi->DeviceComboBox->currentText()+"' failed");
	return false;
}

/**
  * @brief Disconnect serial I/O from the emulation.
  */
void Komport::disconnectSerialFromEmulation()
{
	QObject::disconnect(emulation(),SIGNAL(sendAsciiChar(char)),serial(),SLOT(sendAsciiChar(char)));
	QObject::disconnect(emulation(),SIGNAL(sendAsciiString(const char*)),serial(),SLOT(sendAsciiString(const char*)));
	QObject::disconnect(serial(),SIGNAL(rx(unsigned char)),emulation(),SLOT(receiveChar(unsigned char)));
}

/**
  * @brief Connect serial I/O from the emulation
  */
void Komport::connectSerialToEmulation()
{
	QObject::connect(emulation(),SIGNAL(sendAsciiChar(char)),serial(),SLOT(sendAsciiChar(char)));
	QObject::connect(emulation(),SIGNAL(sendAsciiString(const char*)),serial(),SLOT(sendAsciiString(const char*)));
	QObject::connect(serial(),SIGNAL(rx(unsigned char)),emulation(),SLOT(receiveChar(unsigned char)));
}

/**
  * @brief Sleep for a given milliseconds.
  */
void Komport::msleep(int msec)
{
	QEventLoop loop;
	QElapsedTimer timer;
	for(timer.start(); timer.elapsed() < msec;)
	{
		loop.processEvents();
	}
}

/**
  * @brief clear the log
  */
void Komport::clearLog()
{
	settingsUi->log->clear();
}

void Komport::log(QString msg,bool show)
{
	msg = msg.trimmed();
	for(int n=0; n < msg.length(); n++)
	{
		if ( msg[n] == '\n' || msg[n] == '\r' )
		{
			msg.resize(n);
			break;
		}
	}
	settingsUi->log->append(msg);
	if ( show )
	{
		statusBar()->showMessage(msg);
	}
}



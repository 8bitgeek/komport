/**************************************************************************
*   Author <mike@pikeaero.com> Mike Sharkey                               *
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

#ifdef Q_OS_WIN32
	#include <QWindowsStyle>
#endif

#define BANNER tr("Komport ")+QString(KOMPORT_VERSION)+tr(" Serial Communications")
#define COPYRIGHT "Copyright (c) 2011 by Mike Sharkey &lt;mike@pikeaero.com&gt;"
#define WEBSITE "http://www.sourceforge.net/komport2"



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
	QObject::connect(settingsUi->uploadPathButton,SIGNAL(clicked()),this,SLOT(uploadPathSelect()));
	QObject::connect(settingsUi->downloadPathButton,SIGNAL(clicked()),this,SLOT(downloadPathSelect()));

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
	QSettings settings( QSettings::IniFormat, QSettings::UserScope, "pikeaero.com", "komport-0.9" );
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

	settings.beginGroup("fileTransfer");
		settingsUi->characterDelay->setValue(settings.value("characterDelay",DEFAULT_CH_DELAY).toInt());
		settingsUi->newlineDelay->setValue(settings.value("newlineDelay",DEFAULT_LF_DELAY).toInt());
		settingsUi->carriageReturnDelay->setValue(settings.value("carriageReturn",DEFAULT_CR_DELAY).toInt());

		settingsUi->uploadPath->setText(settings.value("uploadPath",DEFAULT_UPLOAD_PATH).toString());
		settingsUi->downloadPath->setText(settings.value("downloadPath",DEFAULT_DOWNLOAD_PATH).toString());

		settingsUi->xmodemDownload->setText(settings.value("xmodemDownload",DEFAULT_XMODEM_DOWNLOAD).toString());
		settingsUi->xmodemUpload->setText(settings.value("xmodemUpload",DEFAULT_XMODEM_UPLOAD).toString());

		settingsUi->ymodemDownload->setText(settings.value("ymodemDownload",DEFAULT_YMODEM_DOWNLOAD).toString());
		settingsUi->ymodemUpload->setText(settings.value("ymodemUpload",DEFAULT_YMODEM_UPLOAD).toString());

		settingsUi->zmodemDownload->setText(settings.value("zmodemDownload",DEFAULT_ZMODEM_DOWNLOAD).toString());
		settingsUi->zmodemUpload->setText(settings.value("zmodemUpload",DEFAULT_ZMODEM_UPLOAD).toString());

		settingsUi->kermitDownload->setText(settings.value("kermitDownload",DEFAULT_KERMIT_DOWNLOAD).toString());
		settingsUi->kermitUpload->setText(settings.value("kermitUpload",DEFAULT_KERMIT_UPLOAD).toString());

		settingsUi->defaultUploadAscii->setChecked(settings.value("defaultUploadAscii",true).toBool());
		settingsUi->defaultUploadKermit->setChecked(settings.value("defaultUploadKermit",false).toBool());
		settingsUi->defaultUploadXModem->setChecked(settings.value("defaultUploadXModem",false).toBool());
		settingsUi->defaultUploadYModem->setChecked(settings.value("defaultUploadYModem",false).toBool());
		settingsUi->defaultUploadZModem->setChecked(settings.value("defaultUploadZModem",false).toBool());

		settingsUi->defaultDownloadAscii->setChecked(settings.value("defaultDownloadAscii",false).toBool());
		settingsUi->defaultDownloadKermit->setChecked(settings.value("defaultDownloadKermit",false).toBool());
		settingsUi->defaultDownloadXModem->setChecked(settings.value("defaultDownloadXModem",false).toBool());
		settingsUi->defaultDownloadYModem->setChecked(settings.value("defaultDownloadYModem",false).toBool());
		settingsUi->defaultDownloadZModem->setChecked(settings.value("defaultDownloadZModem",false).toBool());

		setDefaultUpDownAct();

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
	QSettings settings( QSettings::IniFormat, QSettings::UserScope, "pikeaero.com", "komport-0.9" );
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

	settings.beginGroup("fileTransfer");
		settings.setValue("characterDelay",	settingsUi->characterDelay->value() );
		settings.setValue("newlineDelay",	settingsUi->newlineDelay->value() );
		settings.setValue("carriageReturn",	settingsUi->carriageReturnDelay->value() );

		settings.setValue("uploadPath",		settingsUi->uploadPath->text());
		settings.setValue("downloadPath",	settingsUi->downloadPath->text());

		settings.setValue("xmodemDownload",	settingsUi->xmodemDownload->text());
		settings.setValue("xmodemUpload",	settingsUi->xmodemUpload->text());

		settings.setValue("ymodemDownload",	settingsUi->ymodemDownload->text());
		settings.setValue("ymodemUpload",	settingsUi->ymodemUpload->text());

		settings.setValue("zmodemDownload",	settingsUi->zmodemDownload->text());
		settings.setValue("zmodemUpload",	settingsUi->zmodemUpload->text());

		settings.setValue("kermitDownload",	settingsUi->kermitDownload->text());
		settings.setValue("kermitUpload",	settingsUi->kermitUpload->text());

		settings.setValue("defaultUploadAscii",	settingsUi->defaultUploadAscii->isChecked());
		settings.setValue("defaultUploadKermit",	settingsUi->defaultUploadKermit->isChecked());
		settings.setValue("defaultUploadXModem",	settingsUi->defaultUploadXModem->isChecked());
		settings.setValue("defaultUploadYModem",	settingsUi->defaultUploadYModem->isChecked());
		settings.setValue("defaultUploadZModem",	settingsUi->defaultUploadZModem->isChecked());

		settings.setValue("defaultDownloadAscii",	settingsUi->defaultDownloadAscii->isChecked());
		settings.setValue("defaultDownloadKermit",	settingsUi->defaultDownloadKermit->isChecked());
		settings.setValue("defaultDownloadXModem",	settingsUi->defaultDownloadXModem->isChecked());
		settings.setValue("defaultDownloadYModem",	settingsUi->defaultDownloadYModem->isChecked());
		settings.setValue("defaultDownloadZModem",	settingsUi->defaultDownloadZModem->isChecked());

	settings.endGroup();

}

/** Open the serial port and notify of there was any trouble */
bool Komport::openSerial()
{
	if ( serial()->open() )
	{
		QObject::connect(emulation(),SIGNAL(sendAsciiChar(char)),serial(),SLOT(sendAsciiChar(char)));
		QObject::connect(emulation(),SIGNAL(sendAsciiString(const char*)),serial(),SLOT(sendAsciiString(const char*)));
		QObject::connect(serial(),SIGNAL(rx(unsigned char)),emulation(),SLOT(receiveChar(unsigned char)));
		return true;
	}
	QMessageBox::warning(this, "Open Failed", "Open '"+settingsUi->DeviceComboBox->currentText()+"' failed");
	return false;
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
	serial()->sendAsciiString(text.toAscii().data());
}

void Komport::createActions()
{
	exitAct = new QAction(QIcon(":/images/exit.png"),tr("E&xit"), this);
	exitAct->setShortcut(tr("Ctrl+Shift+Q"));
	exitAct->setStatusTip(tr("Exit Komport"));
	QObject::connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));


	uploadAct = new QAction(QIcon(":/images/upload.png"),tr("&Upload"), this);
	uploadAct->setShortcut(tr("Ctrl+Shift+U"));
	uploadAct->setStatusTip(tr("Upload a File"));
	QObject::connect(uploadAct, SIGNAL(triggered()), this, SLOT(upload()));

	uploadAsciiAct = new QAction(QIcon(":/images/uploadascii.png"),tr("Upload &Ascii"), this);
	uploadAsciiAct->setShortcut(tr("Ctrl+Shift+A"));
	uploadAsciiAct->setStatusTip(tr("Upload a File using Ascii protocol"));
	QObject::connect(uploadAsciiAct, SIGNAL(triggered()), this, SLOT(uploadAscii()));

	uploadKermitAct = new QAction(QIcon(":/images/uploadkermit.png"),tr("Upload &Kermit"), this);
	uploadKermitAct->setShortcut(tr("Ctrl+Shift+K"));
	uploadKermitAct->setStatusTip(tr("Upload a File using Kermit protocol"));
	QObject::connect(uploadKermitAct, SIGNAL(triggered()), this, SLOT(uploadKermit()));

	uploadXModemAct = new QAction(QIcon(":/images/uploadxmodem.png"),tr("Upload &X-Modem"), this);
	uploadXModemAct->setShortcut(tr("Ctrl+Shift+X"));
	uploadXModemAct->setStatusTip(tr("Upload a File using X-Modem protocol"));
	QObject::connect(uploadXModemAct, SIGNAL(triggered()), this, SLOT(uploadXModem()));

	uploadYModemAct = new QAction(QIcon(":/images/uploadymodem.png"),tr("Upload &Y-Modem"), this);
	uploadYModemAct->setShortcut(tr("Ctrl+Shift+Y"));
	uploadYModemAct->setStatusTip(tr("Upload a File using Y-Modem protocol"));
	QObject::connect(uploadYModemAct, SIGNAL(triggered()), this, SLOT(uploadYModem()));

	uploadZModemAct = new QAction(QIcon(":/images/uploadzmodem.png"),tr("Upload &Z-Modem"), this);
	uploadZModemAct->setShortcut(tr("Ctrl+Shift+X"));
	uploadZModemAct->setStatusTip(tr("Upload a File using Z-Modem protocol"));
	QObject::connect(uploadZModemAct, SIGNAL(triggered()), this, SLOT(uploadZModem()));


	downloadAct = new QAction(QIcon(":/images/download.png"),tr("&Download"), this);
	downloadAct->setShortcut(tr("Ctrl+Alt+D"));
	downloadAct->setStatusTip(tr("Download a File"));
	QObject::connect(downloadAct, SIGNAL(triggered()), this, SLOT(download()));

	downloadAsciiAct = new QAction(QIcon(":/images/downloadascii.png"),tr("Download &Ascii"), this);
	downloadAsciiAct->setShortcut(tr("Ctrl+Alt+A"));
	downloadAsciiAct->setStatusTip(tr("Download a File unsing Ascii Protocol"));
	QObject::connect(downloadAsciiAct, SIGNAL(triggered()), this, SLOT(downloadAscii()));

	downloadKermitAct = new QAction(QIcon(":/images/downloadkermit.png"),tr("Download &Kermit"), this);
	downloadKermitAct->setShortcut(tr("Ctrl+Alt+K"));
	downloadKermitAct->setStatusTip(tr("Download a File unsing Kermit Protocol"));
	QObject::connect(downloadKermitAct, SIGNAL(triggered()), this, SLOT(downloadKermit()));

	downloadXModemAct = new QAction(QIcon(":/images/downloadxmodem.png"),tr("Download &X-Modem"), this);
	downloadXModemAct->setShortcut(tr("Ctrl+Alt+X"));
	downloadXModemAct->setStatusTip(tr("Download a File unsing X-Modem Protocol"));
	QObject::connect(downloadXModemAct, SIGNAL(triggered()), this, SLOT(downloadXModem()));

	downloadYModemAct = new QAction(QIcon(":/images/downloadymodem.png"),tr("Download &Y-Modem"), this);
	downloadYModemAct->setShortcut(tr("Ctrl+Alt+Y"));
	downloadYModemAct->setStatusTip(tr("Download a File unsing Y-Modem Protocol"));
	QObject::connect(downloadYModemAct, SIGNAL(triggered()), this, SLOT(downloadYModem()));

	downloadZModemAct = new QAction(QIcon(":/images/downloadzmodem.png"),tr("Download &Z-Modem"), this);
	downloadZModemAct->setShortcut(tr("Ctrl+Alt+Z"));
	downloadZModemAct->setStatusTip(tr("Download a File unsing Z-Modem Protocol"));
	QObject::connect(downloadZModemAct, SIGNAL(triggered()), this, SLOT(downloadZModem()));


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
	uploadMenu = fileMenu->addMenu(QIcon(":/images/upload.png"),tr("&Upload"));
	uploadMenu->addAction(uploadAsciiAct);
	uploadMenu->addAction(uploadKermitAct);
	uploadMenu->addAction(uploadXModemAct);
	uploadMenu->addAction(uploadYModemAct);
	uploadMenu->addAction(uploadZModemAct);
	downloadMenu = fileMenu->addMenu(QIcon(":/images/download.png"),tr("&Download"));
	downloadMenu->addAction(downloadAsciiAct);
	downloadMenu->addAction(downloadKermitAct);
	downloadMenu->addAction(downloadXModemAct);
	downloadMenu->addAction(downloadYModemAct);
	downloadMenu->addAction(downloadZModemAct);

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
	fileToolBar->addAction(uploadAct);
	fileToolBar->addAction(downloadAct);

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
	hex.sprintf("%02x%02x%02x", c.red(), c.green(), c.blue() );
	return hex;
}

/**
  * brief set the visuals of the default up/down actions to look appropriately based on the default value.
  */
void Komport::setDefaultUpDownAct()
{
	if ( settingsUi->defaultUploadAscii->isChecked() )
	{
		uploadAct->setIcon(uploadAsciiAct->icon());
		uploadAct->setText(uploadAsciiAct->text());
		uploadAct->setToolTip(uploadAsciiAct->toolTip());
	}
	else if ( settingsUi->defaultUploadKermit->isChecked() )
	{
		uploadAct->setIcon(uploadKermitAct->icon());
		uploadAct->setText(uploadKermitAct->text());
		uploadAct->setToolTip(uploadKermitAct->toolTip());
	}
	else if ( settingsUi->defaultUploadXModem->isChecked() )
	{
		uploadAct->setIcon(uploadXModemAct->icon());
		uploadAct->setText(uploadXModemAct->text());
		uploadAct->setToolTip(uploadXModemAct->toolTip());
	}
	else if ( settingsUi->defaultUploadYModem->isChecked() )
	{
		uploadAct->setIcon(uploadYModemAct->icon());
		uploadAct->setText(uploadYModemAct->text());
		uploadAct->setToolTip(uploadYModemAct->toolTip());
	}
	else if ( settingsUi->defaultUploadZModem->isChecked() )
	{
		uploadAct->setIcon(uploadZModemAct->icon());
		uploadAct->setText(uploadZModemAct->text());
		uploadAct->setToolTip(uploadZModemAct->toolTip());
	}

	if ( settingsUi->defaultDownloadAscii->isChecked() )
	{
		downloadAct->setIcon(downloadAsciiAct->icon());
		downloadAct->setText(downloadAsciiAct->text());
		downloadAct->setToolTip(downloadAsciiAct->toolTip());
	}
	else if ( settingsUi->defaultDownloadKermit->isChecked() )
	{
		downloadAct->setIcon(downloadKermitAct->icon());
		downloadAct->setText(downloadKermitAct->text());
		downloadAct->setToolTip(downloadKermitAct->toolTip());
	}
	else if ( settingsUi->defaultDownloadXModem->isChecked() )
	{
		downloadAct->setIcon(downloadXModemAct->icon());
		downloadAct->setText(downloadXModemAct->text());
		downloadAct->setToolTip(downloadXModemAct->toolTip());
	}
	else if ( settingsUi->defaultDownloadYModem->isChecked() )
	{
		downloadAct->setIcon(downloadYModemAct->icon());
		downloadAct->setText(downloadYModemAct->text());
		downloadAct->setToolTip(downloadYModemAct->toolTip());
	}
	else if ( settingsUi->defaultDownloadZModem->isChecked() )
	{
		downloadAct->setIcon(downloadZModemAct->icon());
		downloadAct->setText(downloadZModemAct->text());
		downloadAct->setToolTip(downloadZModemAct->toolTip());
	}
}

/**
  * upload a file using default upload protocol
  */
void Komport::upload()
{
	if ( settingsUi->defaultUploadAscii->isChecked() )			uploadAscii();
	else if ( settingsUi->defaultUploadKermit->isChecked() )	uploadKermit();
	else if ( settingsUi->defaultUploadXModem->isChecked() )	uploadXModem();
	else if ( settingsUi->defaultUploadYModem->isChecked() )	uploadYModem();
	else if ( settingsUi->defaultUploadZModem->isChecked() )	uploadZModem();
}

void Komport::uploadAscii()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("Upload Ascii File"),settingsUi->uploadPath->text());
	if ( !fileName.isEmpty() )
	{
		QFile file(fileName);
		if (file.open(QIODevice::ReadOnly))
		{
			int sent=0;
			QProgressDialog progress(tr("Uploading..."),tr("Abort"), 0, file.size(), this);
			progress.setWindowModality(Qt::WindowModal);
			while(!file.atEnd() && !progress.wasCanceled())
			{
				QByteArray bytes = file.read(1024);
				for(int n=0; n < bytes.count() && !progress.wasCanceled();n++)
				{
					char ch = bytes[n];
					progress.setValue(++sent);
					serial()->sendAsciiChar(ch);
					msleep(settingsUi->characterDelay->value());
					if ( ch == 0x0D ) msleep(settingsUi->carriageReturnDelay->value());
					if ( ch == 0x0A ) msleep(settingsUi->newlineDelay->value());
				}
			}
			progress.setValue(file.size());
			file.close();
		}
		else
		{
			QMessageBox::warning(this,"Open Failed",tr("Failed to open '")+fileName+"'");
		}
	}
}

void Komport::uploadKermit()
{
}

void Komport::uploadXModem()
{
}

void Komport::uploadYModem()
{
}

void Komport::uploadZModem()
{
}

/**
  * download a file
  */
void Komport::download()
{
	if ( settingsUi->defaultDownloadAscii->isChecked() )		downloadAscii();
	else if ( settingsUi->defaultDownloadKermit->isChecked() )	downloadKermit();
	else if ( settingsUi->defaultDownloadXModem->isChecked() )	downloadXModem();
	else if ( settingsUi->defaultDownloadYModem->isChecked() )	downloadYModem();
	else if ( settingsUi->defaultDownloadZModem->isChecked() )	downloadZModem();
}

void Komport::downloadAscii()
{
}

void Komport::downloadKermit()
{
}

void Komport::downloadXModem()
{
}

void Komport::downloadYModem()
{
}

void Komport::downloadZModem()
{
}

/**
  * @brief use a file dialog to select the default upload path.
  */
void Komport::uploadPathSelect()
{
	settingsUi->uploadPath->setText(QFileDialog::getExistingDirectory(this,tr("Upload Path"),settingsUi->uploadPath->text()));
}

/**
  * @brief use a file dialog to select the default download path.
  */
void Komport::downloadPathSelect()
{
	settingsUi->downloadPath->setText(QFileDialog::getExistingDirectory(this,tr("Download Path"),settingsUi->downloadPath->text()));
}

/**
  * @brief Sleep for a given milliseconds.
  */
void Komport::msleep(int msec)
{
	QEventLoop loop;
	QTime timer;
	for(timer.start(); timer.elapsed() < msec;)
	{
		loop.processEvents();
	}
}



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
#ifndef KOMPORT_H
#define KOMPORT_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QDialog>
#include <QCloseEvent>
#include <QColor>

#include "cscreen.h"
#include "cserial.h"
#include "cemulation.h"
#include "cled.h"

#define KOMPORT_VERSION "V1.1.1"

#define DEFAULT_CH_DELAY 8			/** ascii upload default delay between characters in msec */
#define DEFAULT_LF_DELAY 25			/** ascii upload default delay beteeen line feeds characters in msec */
#define DEFAULT_CR_DELAY 25			/** ascii upload default delay between carriage return characters in msec */

#ifdef Q_OS_WIN32

#define DEFAULT_UPLOAD_PATH			""
#define DEFAULT_DOWNLOAD_PATH		""

#define DEFAULT_XMODEM_DOWNLOAD		"rx.exe -vv"
#define DEFAULT_XMODEM_UPLOAD		"sx.exe -vv"

#define DEFAULT_YMODEM_DOWNLOAD		"rb.exe -vv"
#define DEFAULT_YMODEM_UPLOAD		"sb.exe -vv"

#define DEFAULT_ZMODEM_DOWNLOAD		"rz.exe -vv -b -E"
#define DEFAULT_ZMODEM_UPLOAD		"sz.exe -vv -b"

#define DEFAULT_KERMIT_DOWNLOAD		"kermit.exe -i -l %l -b %"
#define DEFAULT_KERMIT_UPLOAD		"kermit.exe -i -l %l -b %b"

#else

#define DEFAULT_UPLOAD_PATH			""
#define DEFAULT_DOWNLOAD_PATH		""

#define DEFAULT_XMODEM_DOWNLOAD		"/usr/bin/rx -vv"
#define DEFAULT_XMODEM_UPLOAD		"/usr/bin/sx -vv"

#define DEFAULT_YMODEM_DOWNLOAD		"/usr/bin/rb -vv"
#define DEFAULT_YMODEM_UPLOAD		"/usr/bin/sb -vv"

#define DEFAULT_ZMODEM_DOWNLOAD		"/usr/bin/rz -vv -b -E"
#define DEFAULT_ZMODEM_UPLOAD		"/usr/bin/sz -vv -b"

#define DEFAULT_KERMIT_DOWNLOAD		"/usr/bin/kermit -i -l %l -b %"
#define DEFAULT_KERMIT_UPLOAD		"/usr/bin/kermit -i -l %l -b %b"

#endif // Q_OS_WIN32


namespace Ui
{
    class Komport;
	class SettingsDialog;
}

class Komport : public QMainWindow
{
    Q_OBJECT

	public:
		Komport(QWidget *parent = 0);
		virtual ~Komport();

		CSerial*			serial() {return mSerial;}
		CScreen*			screen() {return mScreen;}
		CEmulation*			emulation() {return mEmulation;}

	protected:
		void				keyPressEvent(QKeyEvent *);
		void				closeEvent(QCloseEvent *event);
		void				msleep(int msec);

	private slots:
		void				upload();
		void				uploadAscii();
		void				uploadKermit();
		void				uploadXModem();
		void				uploadYModem();
		void				uploadZModem();

		void				download();
		void				downloadAscii();
		void				downloadKermit();
		void				downloadXModem();
		void				downloadYModem();
		void				downloadZModem();

		void				about();
		void				editSettings();
		void				doCopy();
		void				doPaste();
		void				openBackgroundColorDialog();
		void				openForegroundColorDialog();
		void				settingsHelp();
		void				rxLedOn()				{mRxLED->on();}
		void				rxLedOff()				{mRxLED->off();}
		void				txLedOn()				{mTxLED->on(true);}
		void				txLedOff()				{mTxLED->off(true);}
		void				uploadPathSelect();
		void				downloadPathSelect();
		#ifdef DEBUG
		void				debug();
		#endif

	private:
		bool				openSerial();
		void				createActions();
		void				createMenus();
		void				createToolBars();
		void				createStatusBar();
		void				readSettings();
		void				writeSettings();
		QString				colorToHex(QColor);

		CSerial*			mSerial;
		CScreen*			mScreen;
		CEmulation*			mEmulation;
		Ui::Komport*		ui;
		Ui::SettingsDialog* settingsUi;
		QDialog				settingsDialog;

		QMenu*				fileMenu;
		QMenu*				uploadMenu;
		QMenu*				uploadXModemMenu;
		QMenu*				uploadYModemMenu;
		QMenu*				uploadZModemMenu;
		QMenu*				uploadKermitMenu;
		QMenu*				downloadMenu;
		QMenu*				downloadXModemMenu;
		QMenu*				downloadYModemMenu;
		QMenu*				downloadZModemMenu;
		QMenu*				downloadKermitMenu;
		QMenu*				editMenu;
		QMenu*				configMenu;
		QMenu*				helpMenu;

		QToolBar*			fileToolBar;
		QToolBar*			editToolBar;
		QToolBar*			configToolBar;

		QAction*			exitAct;
		QAction*			uploadAct;
		QAction*			uploadAsciiAct;
		QAction*			uploadKermitAct;
		QAction*			uploadXModemAct;
		QAction*			uploadYModemAct;
		QAction*			uploadZModemAct;
		QAction*			downloadAct;
		QAction*			downloadAsciiAct;
		QAction*			downloadKermitAct;
		QAction*			downloadXModemAct;
		QAction*			downloadYModemAct;
		QAction*			downloadZModemAct;
		QAction*			copyAct;
		QAction*			pasteAct;
		QAction*			settingsAct;
		QAction*			aboutAct;

		CLed*				mRxLED;
		CLed*				mTxLED;
};

#endif // KOMPORT_H

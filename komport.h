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

#include "cscreen.h"
#include "cserial.h"
#include "cemulation.h"


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

	private slots:
		void				about();
		void				editSettings();
		void				doCopy();
		void				doPaste();
		void				openBackgroundColorDialog();
		void				openForegroundColorDialog();
		void				settingsHelp();

	private:
		bool				openSerial();
		void				createActions();
		void				createMenus();
		void				createToolBars();
		void				createStatusBar();
		void				readSettings();
		void				writeSettings();

		CSerial*			mSerial;
		CScreen*			mScreen;
		CEmulation*			mEmulation;
		Ui::Komport*		ui;
		Ui::SettingsDialog* settingsUi;
		QDialog				settingsDialog;

		QMenu*				fileMenu;
		QMenu*				editMenu;
		QMenu*				configMenu;
		QMenu*				helpMenu;

		QToolBar*			fileToolBar;
		QToolBar*			editToolBar;
		QToolBar*			configToolBar;

		QAction*			exitAct;

		QAction*			copyAct;
		QAction*			pasteAct;

		QAction*			settingsAct;

		QAction*			aboutAct;

};

#endif // KOMPORT_H

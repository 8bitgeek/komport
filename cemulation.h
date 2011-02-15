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

#ifndef CEMULATION_H
#define CEMULATION_H

#include <QObject>
#include <QString>
#include <QByteArray>

#include "cscreen.h"
#include "cserial.h"

class CEmulation : public QObject
{
	Q_OBJECT
	public:

		typedef enum
		{
			ClearLineEOL,											/* cursor to EOL */
			ClearLineBOL,											/* BOL to cursor */
			ClearLineAOL,											/* all of line */
		} ClearLineMode;

		typedef enum
		{
			ClearScreenEOD,											/* cursor to EOD */
			ClearScreenBOD,											/* BOD to cursor */
			ClearScreenAOD,											/* all of display */
		} ClearScreenMode;

		CEmulation(CScreen* screen);
		~CEmulation();


		CScreen*			screen()				{return mScreen;}
		bool				visualBell()			{return mVisualBell;}
		bool				localEcho()				{return mLocalEcho;}

	protected:
		virtual void		doCursorTo(int col, int row);			/** cursor to absolute x,y */
		virtual void		doCursorUp();							/** cursor up one row */
		virtual void		doCursorDown();							/** cursor down one row. */
		virtual void		doCursorLeft();							/** cursor left one column  */
		virtual void		doCursorRight();						/** cursor right one column  */
		virtual void		doClearScreen(ClearScreenMode mode);	/** perform partial and full screen clear operations */

		virtual void		doClearEOL(ClearLineMode mode);			/** clear to EOL from cursor position */
		virtual void		doDeleteCharacters(int num);			/** delete characters in line */
		virtual void		doInsertLines(int num);					/** insert lines */

		virtual void		doRestoreCursor();						/** restore cursor */
		virtual void		doSaveCursor();							/** save cursor */

		virtual void		doVisualBell();							/** perform visual bell */
		virtual void		doBell();								/** ring bell or perform visual bell */

		
	signals:
		void				sendAsciiChar(const char ch);
		void				sendAsciiString(const char* s);

	public slots:
		virtual void		keyPressEvent(QKeyEvent* e)=0;			/** key press input. process and transmit the char. */
		virtual void		receiveChar(unsigned char _ch)=0;		/** received and process an incoming character */
		void				setVisualBell(bool b)	{mVisualBell=b;}
		void				setLocalEcho(bool b)	{mLocalEcho=b;}

	private:
		CScreen*			mScreen;								/** the screen */
		bool				mVisualBell;							/** do we do a visual bell? */
		bool				mLocalEcho;								/** do we do local echo? */
		QPoint				mSaveCursor;							/** save cursor position */

};

#endif



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


		inline CScreen*		screen()							{return mScreen;}
		inline bool			visualBell()						{return mVisualBell;}
		inline bool			localEcho()							{return mLocalEcho;}
		inline QPoint&		savedCursorPos()					{return mSaveCursorPos;}
		inline QPoint&		cursorPos()							{return screen()->cursorPos();}
		inline bool			autoWrap()							{return mAutoWrap;}
		inline bool			autoNewLine()						{return mAutoNewLine;}
		inline bool			autoInsert()						{return mAutoInsert;}
		inline bool			cursorOn()							{return mCursorOn;}
		inline bool			keyboardLock()						{return mKeyboardLock;}
		inline int			cols()								{return screen()->cols();}
		inline int			rows()								{return screen()->rows();}
		inline bool			jumpScroll()						{return mJumpScroll;}
		inline bool			reverseVideo()						{return mReverseVideo;}
		inline bool			relativeCoordinates()				{return mRelativeCoordinates;}

	protected:
		virtual void		doReset();								/** reset to initial state */
		virtual void		doCursorTo(int col, int row);			/** cursor to absolute x,y */
		virtual void		doCursorUp();							/** cursor up one row */
		virtual void		doCursorDown();							/** cursor down one row. */
		virtual void		doCursorLeft();							/** cursor left one column  */
		virtual void		doCursorRight();						/** cursor right one column  */
		virtual void		doClearScreen(ClearScreenMode mode);	/** perform partial and full screen clear operations */

		virtual void		doClearEOL(ClearLineMode mode);			/** clear to EOL from cursor position */
		virtual void		doDeleteCharacters(int num);			/** delete characters in line */
		virtual void		doInsertLines(int num);					/** insert lines */
		virtual void		doNewLine();							/** new line */
		virtual void		doReverseNewLine();						/** reverse new line */
		virtual void		doCarriageReturn();						/** carriage return */
		virtual void		doScrollUp();							/** scroll up */
		virtual void		doScrollDown();							/** scroll down */

		virtual void		doRestoreCursorPos();					/** restore cursor */
		virtual void		doSaveCursorPos();						/** save cursor */

		virtual void		doVisualBell();							/** perform visual bell */
		virtual void		doBell();								/** ring bell or perform visual bell */

		virtual void		doAdvanceCursor();						/** advance cursor and wrap if nessesary */
		virtual void		doChar(unsigned char ch);				/** write a character to the screen */
		
	signals:
		void				sendAsciiChar(const char ch);
		void				sendAsciiString(const char* s);

	public slots:

		virtual void		keyPressEvent(QKeyEvent* e)=0;			/** key press input. process and transmit the char. */
		virtual void		receiveChar(unsigned char _ch)=0;		/** received and process an incoming character */

		virtual void		setVisualBell(bool b)				{mVisualBell=b;}
		virtual void		setLocalEcho(bool b)				{mLocalEcho=b;}
		virtual void		setAutoWrap(bool b)					{mAutoWrap=b;}
		virtual void		setAutoNewLine(bool b)				{mAutoNewLine=b;}
		virtual void		setAutoInsert(bool b)				{mAutoInsert=b;}
		virtual void		setCursorOn(bool b)					{mCursorOn=b;}
		virtual void		setKeyboardLock(bool b)				{mKeyboardLock=b;}
		virtual void		setCols(int cols)					{screen()->setCols(cols);}
		virtual void		setRows(int rows)					{screen()->setRows(rows);}
		virtual void		setGrid(int cols,int rows);
		virtual void		setJumpScroll(bool b)				{mJumpScroll=b;}
		virtual void		setReverseVideo(bool b)				{mReverseVideo=b;}
		virtual void		setRelativeCoordinates(bool b)		{mRelativeCoordinates=b;}

	private:
		CScreen*			mScreen;								/** the screen */
		bool				mVisualBell;							/** do we do a visual bell? */
		bool				mLocalEcho;								/** do we do local echo? */
		QPoint				mSaveCursorPos;							/** save cursor position */
		bool				mAutoWrap;								/** automatic line wrap */
		bool				mAutoNewLine;							/** automatic new line on carriage return */
		bool				mAutoInsert;							/** are we in character insertion mode? */
		bool				mCursorOn;								/** is cursor visible? */
		bool				mKeyboardLock;							/** keyboard lock */
		bool				mJumpScroll;							/** jump scroll */
		bool				mReverseVideo;							/** screen reverse video */
		bool				mRelativeCoordinates;					/** use relative coords rather than absolute */

};

#endif



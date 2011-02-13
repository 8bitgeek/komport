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

#ifndef CCHARCELL_H
#define CCHARCELL_H

#include <QChar>
#include <QString>
#include <QColor>
#include <QObject>
#include <QRect>
#include <QWidget>
#include <QPainter>

#define DEFAULTCURSORSTYLE BlockInvert

class CScreen;
class CCellArray;
class CCharCell : public QObject
{
	Q_OBJECT
	public:

		typedef enum
		{
			Underline,
			BlockOutline,
			BlockInvert
		} CursorStyle;

		static const  unsigned int attrSelect    =   0x0001;   // selected.
		static const  unsigned int attrBlink     =   0x0002;   // blink.
		static const  unsigned int attrBold      =   0x0004;   // bold.
		static const  unsigned int attrReverse   =   0x0008;   // reverse.
		static const  unsigned int attrUnderline =   0x0010;   // underline.
		static const  unsigned int attrCursor    =   0x0020;   // cursor

		CCharCell(CCellArray* cellArray);
		CCharCell(const CCharCell & _other) : QObject() {copy((CCharCell*)(&_other));}
		virtual ~CCharCell();

		CCellArray*			container()				{return mCellArray;}
		CursorStyle			cursorStyle()			{return mCursorStyle;}
		inline bool			cursor()				{return ( mAttributes & attrCursor );}
		inline bool			blink()					{return ( mAttributes & attrBlink );}
		inline bool			select()				{return ( mAttributes & attrSelect );}
		inline bool			bold()					{return ( mAttributes & attrBold );}
		inline bool			reverse()				{return ( mAttributes & attrReverse );}
		inline bool			underline()				{return ( mAttributes & attrUnderline );}
		inline unsigned short attributes()			{return mAttributes;}
		inline QChar		character()				{return mCharacter;}
		inline QRect		rect()					{return mRect;}

		QColor				backgroundColor();
		QColor				foregroundColor();
		CScreen*			screen();

		void				setContainer(CCellArray* container) {mCellArray=container;}
		void				setCursor(bool _b,CursorStyle cs=DEFAULTCURSORSTYLE);
		void				setCursorStyle(CursorStyle cs);
		void				setBlink(bool _b);
		void				setSelect(bool _b);
		void				setBold(bool _b);
		void				setReverse(bool _b);
		void				setUnderline(bool _b);
		void				setAttributes(unsigned short _a);
		void				setCharacter(QChar _c);
		void				setForegroundColor(QColor _c);
		void				setBackgroundColor(QColor _c);
		void				setRect(QRect _r);

		void				clear();										/** reset properties to default values */
		void				copy(CCharCell* _other);						/** copy a cell */
		void				copy(CCharCell& _other);						/** copy a cell */
		CCharCell & operator=(const CCharCell & _other);					/** copy operator */

	public slots:
		void draw();
		void draw(QPainter& painter);

	private slots:
		void drawCursorBegin(QPainter& paint);
		void drawCursorEnd(QPainter& paint);

	protected:
		void timerEvent(QTimerEvent *e);

	private:
		CCellArray*		mCellArray;							/** the container */
		QRect			mRect;								/** the position rectangle */
		unsigned short	mAttributes;						/** character attributes */
		QChar			mCharacter;							/** character property */
		QColor			mForegroundColor;					/** forground color */
		QColor			mBackgroundColor;					/** background color */
		int				mCursorTimer;
		int				mBlinkTimer;
		bool			mCursorState;
		bool			mBlinkState;
		CursorStyle		mCursorStyle;
};

#endif


/**************************************************************************
*   Author <mike@pikeaero.com> Mike Sharkey                               *
*  copyright (C) 2010 by Pike Aerospace Research Corporation             *
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

#include "ccell.h"
#include "ccellarray.h"
#include "cscreen.h"

#include <QApplication>
#include <QPainter>
#include <QPalette>
#include <QFont>

#define _DEFAULT_CHAR_ ' '
#define _DEFAULT_FOREGROUND_   QApplication::palette().color(QPalette::Foreground)
#define _DEFAULT_BACKGROUND_   QApplication::palette().color(QPalette::Background)

CCell::CCell(CCellArray* cellArray)
: mCellArray(cellArray)
, mAttributes(0)
, mCharacter(_DEFAULT_CHAR_)
, mForegroundColor(_DEFAULT_FOREGROUND_)
, mBackgroundColor(_DEFAULT_BACKGROUND_)
, mCursorTimer(-1)
, mBlinkTimer(-1)
, mCursorState(false)
, mBlinkState(false)
, mCursorStyle(BlockInvert)
{
	setCharacter(QChar(_DEFAULT_CHAR_));
	if ( screen() != NULL )
	{
		mForegroundColor = screen()->defaultForegroundColor();
		mBackgroundColor = screen()->defaultBackgroundColor();
	}
}

CCell::CCell(const CCell & _other)
: QObject()
{
	copy((CCell*)(&_other));
}

CCell::~CCell()
{
}

CScreen* CCell::screen()
{
	return container()!=NULL?container()->screen():NULL;
}

void CCell::update()
{
	if (screen()!=NULL) screen()->update(rect());
}


void CCell::setCursorStyle(CursorStyle cs)
{
	mCursorStyle=cs;
	update();
}

void CCell::setSelect(bool b)
{
	b ? mAttributes |= attrSelect : mAttributes &= ~attrSelect;
	update();
}

void CCell::setBold(bool b)
{
	b ? mAttributes |= attrBold : mAttributes &= ~attrBold;
	update();
}

void CCell::setReverse(bool b)
{
	b ? mAttributes |= attrReverse : mAttributes &= ~attrReverse;
	update();
}

void CCell::setUnderline(bool b)
{
	b ? mAttributes |= attrUnderline : mAttributes &= ~attrUnderline ;
	update();
}

void CCell::setAttributes(unsigned short a)
{
	if ( mAttributes != a )
	{
		mAttributes = a;
		update();
	}
}

void CCell::setCharacter(QChar c)
{
	if ( mCharacter != c )
	{
		mCharacter = c;
		update();
	}
}

void CCell::setForegroundColor(QColor c)
{
	if ( mForegroundColor != c )
	{
		mForegroundColor = c;
		update();
	}
}

void CCell::setBackgroundColor(QColor c)
{
	if ( mBackgroundColor != c )
	{
		mBackgroundColor = c;
		update();
	}
}

void CCell::setRect(QRect r)
{
	if ( mRect != r )
	{
		mRect = r;
		update();
	}
}

/** reset properties to default values */
void CCell::clear()
{
	mAttributes=0;
	mCursorStyle=Underline;
	setCharacter(_DEFAULT_CHAR_);
	setForegroundColor(screen()!=NULL?screen()->defaultForegroundColor():_DEFAULT_FOREGROUND_);
	setBackgroundColor(screen()!=NULL?screen()->defaultBackgroundColor():_DEFAULT_BACKGROUND_);
	update();
}

/** copy operator */
CCell & CCell::operator=(const CCell & _other)
{
	if ( this != &_other )
	{
		copy((CCell*)(&_other));
	}
	return *this;
}

/** copy a cell */
void CCell::copy(CCell& other)
{
	copy(&other);
}

/** copy a cell */
void CCell::copy(CCell* other)
{
	if ( other != this )
	{
		setContainer(		other->container() );
		setCursorStyle(		other->cursorStyle() );
		setRect(			other->rect() );
		setAttributes(		other->attributes() );
		setCharacter(		other->character() );
		setForegroundColor(	other->foregroundColor() );
		setBackgroundColor(	other->backgroundColor() );
		setCursor(false);
	}
	update();
}

/**
 * @brief begin drawing the cursor - perform any setup prior to drawing the cell content
*/
void CCell::drawCursorBegin(QPainter& painter)
{
	painter.fillRect(rect(),backgroundColor());
	if ( cursor() )
	{
		switch(cursorStyle())
		{
			case Underline:
				break;
			case BlockOutline:
				break;
			case BlockInvert:
				if ( mCursorState )
				{
					painter.fillRect(rect(),foregroundColor());
					painter.setPen(backgroundColor());
				}
				break;
		}
	}
}

/**
 * @brief begin drawing the cursor - perform any work after drawing the cell content
*/
void CCell::drawCursorEnd(QPainter& painter)
{
	if ( cursor() )
	{
		switch(cursorStyle())
		{
			case Underline:
				if ( mCursorState )
				{
					painter.setPen(foregroundColor());
					painter.drawLine(rect().bottomLeft(),rect().bottomRight());
				}
				break;
			case BlockOutline:
				if ( mCursorState )
				{
					painter.setPen(foregroundColor());
					painter.drawRect(rect());
				}
				break;
			case BlockInvert:
				break;
		}
	}
}

/** draw a cell */
void CCell::draw(QPainter& painter)
{
	if (screen() != NULL)
	{
		QFont f = painter.font();
		f.setPixelSize(rect().height());
		f.setFamily("Monospace");
		painter.setFont(f);
		painter.setPen(foregroundColor());
		drawCursorBegin(painter);
		painter.drawText(rect(), Qt::AlignCenter, QString(mCharacter));
		drawCursorEnd(painter);
		if ( select() )
		{
			painter.fillRect(rect(),foregroundColor());
			painter.setPen(backgroundColor());
			painter.drawText(rect(), Qt::AlignCenter, QString(mCharacter));
		}
	}
}

/** draw a cell */
void CCell::draw()
{
	if (screen() != NULL)
	{
		QPainter painter(screen());
		draw(painter);
	}
}

/**
  * @brief set or clear the cursor assignment to this cell and set the cursor style
  */
void CCell::setCursor(bool b,CursorStyle cs)
{
	setCursorStyle(cs);
	if ( b )
	{
		mAttributes |= attrCursor;
		if ( mCursorTimer >= 0 )
			killTimer(mCursorTimer);
		mCursorTimer = startTimer(500);
	}
	else
	{
		mAttributes &= ~attrCursor;
		if ( mCursorTimer >= 0 )
			killTimer(mCursorTimer);
		mCursorTimer = -1;
	}
	update();
}

void CCell::setBlink(bool b)
{
	if ( b )
	{
		mAttributes |= attrBlink;
		if ( mBlinkTimer >= 0 )
			killTimer(mBlinkTimer);
		mBlinkTimer = startTimer(1000);
	}
	else
	{
		mAttributes &= ~attrBlink;
		if ( mBlinkTimer >= 0 )
			killTimer(mBlinkTimer);
		mBlinkTimer = -1;
	}
	update();
}

void CCell::timerEvent(QTimerEvent* e)
{
	if ( e->timerId() == mCursorTimer )
	{
		mCursorState = mCursorState ? false : true;
		update();
	}
	else if ( e->timerId() == mBlinkTimer)
	{
		mBlinkState = !mBlinkState;
		update();
	}
}



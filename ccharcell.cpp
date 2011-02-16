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

#include "ccharcell.h"
#include "ccellarray.h"
#include "cscreen.h"

#include <QApplication>
#include <QPainter>
#include <QPalette>
#include <QFont>

#define _DEFAULT_CHAR_ ' '
#define _DEFAULT_FOREGROUND_   QApplication::palette().color(QPalette::Foreground)
#define _DEFAULT_BACKGROUND_   QApplication::palette().color(QPalette::Background)

CCharCell::CCharCell(CCellArray* cellArray)
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

CCharCell::~CCharCell()
{
}

void CCharCell::setCursorStyle(CursorStyle cs)
{
	mCursorStyle=cs;
	if ( screen() != NULL ) screen()->update(rect());
}

void CCharCell::setSelect(bool b)
{
	b ? mAttributes |= attrSelect : mAttributes &= ~attrSelect;
	if ( screen() != NULL ) screen()->update(rect());
}

void CCharCell::setBold(bool b)
{
	b ? mAttributes |= attrBold : mAttributes &= ~attrBold;
	if ( screen() != NULL ) screen()->update(rect());
}

void CCharCell::setReverse(bool b)
{
	b ? mAttributes |= attrReverse : mAttributes &= ~attrReverse;
	if ( screen() != NULL ) screen()->update(rect());
}

void CCharCell::setUnderline(bool b)
{
	b ? mAttributes |= attrUnderline : mAttributes &= ~attrUnderline ;
	if ( screen() != NULL ) screen()->update(rect());
}

void CCharCell::setAttributes(unsigned short a)
{
	if ( mAttributes != a )
	{
		mAttributes = a;
		if ( screen() != NULL ) screen()->update(rect());
	}
}

void CCharCell::setCharacter(QChar c)
{
	if ( mCharacter != c )
	{
		mCharacter = c;
		if ( screen() != NULL ) screen()->update(rect());
	}
}

void CCharCell::setForegroundColor(QColor c)
{
	if ( mForegroundColor != c )
	{
		mForegroundColor = c;
		if ( screen() != NULL ) screen()->update(rect());
	}
}

void CCharCell::setBackgroundColor(QColor c)
{
	if ( mBackgroundColor != c )
	{
		mBackgroundColor = c;
		if ( screen() != NULL ) screen()->update(rect());
	}
}

QColor CCharCell::backgroundColor()
{
	return reverse() ? mForegroundColor : mBackgroundColor;
}

QColor CCharCell::foregroundColor()
{
	return reverse() ? mBackgroundColor : mForegroundColor;
}

void CCharCell::setRect(QRect r)
{
	if ( mRect != r )
	{
		mRect = r;
		screen()->update(rect());
	}
}

/** reset properties to default values */
void CCharCell::clear()
{
	mAttributes=0;
	mCursorStyle=Underline;
	setCharacter(_DEFAULT_CHAR_);
	setForegroundColor(screen()!=NULL?screen()->defaultForegroundColor():_DEFAULT_FOREGROUND_);
	setBackgroundColor(screen()!=NULL?screen()->defaultBackgroundColor():_DEFAULT_BACKGROUND_);
	screen()->update(rect());
}

/** copy operator */
CCharCell & CCharCell::operator=(const CCharCell & _other)
{
	if ( this != &_other )
	{
		copy((CCharCell*)(&_other));
	}
	return *this;
}

/** copy a cell */
void CCharCell::copy(CCharCell& other)
{
	copy(&other);
}

/** copy a cell */
void CCharCell::copy(CCharCell* other)
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
	if ( screen() != NULL )
	{
		screen()->update(rect());
	}
}

/**
 * @brief begin drawing the cursor - perform any setup prior to drawing the cell content
*/
void CCharCell::drawCursorBegin(QPainter& painter)
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
void CCharCell::drawCursorEnd(QPainter& painter)
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
void CCharCell::draw(QPainter& painter)
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
void CCharCell::draw()
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
void CCharCell::setCursor(bool b,CursorStyle cs)
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
	screen()->update(rect());
}

void CCharCell::setBlink(bool b)
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
	screen()->update(rect());
}

void CCharCell::timerEvent(QTimerEvent* e)
{
	if ( e->timerId() == mCursorTimer )
	{
		mCursorState = mCursorState ? false : true;
		screen()->update(rect());
	}
	else if ( e->timerId() == mBlinkTimer)
	{
		mBlinkState = !mBlinkState;
		screen()->update(rect());
	}
}

CScreen* CCharCell::screen()
{
	if ( container() != NULL )
	{
		return container()->screen();
	}
	return NULL;
}


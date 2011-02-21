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
#include "cscreen.h"
#include <QPainter>

#define inherited QWidget


CScreen::CScreen(QWidget *parent)
: inherited(parent)
, mCursor(0,0)
, mBackgroundColor(QColor(0,0,0))
, mForegroundColor(QColor(255,255,255))
, mBlink(false)
, mBold(false)
, mReverse(false)
, mUnderline(false)
{
	cells().setScreen(this);
}

CScreen::~CScreen()
{
}

void CScreen::resizeEvent(QResizeEvent* e)
{
	cells().setRect(QRect(0,0,e->size().width(),e->size().height()));
	inherited::resizeEvent(e);
	cells().sync();
}

void CScreen::paintEvent(QPaintEvent* e)
{
	QPainter painter(this);
	cells().draw(painter,e->rect());
}

void CScreen::mousePressEvent(QMouseEvent *e)
{
	if ( e->buttons() | Qt::LeftButton )
	{
		mSelectPt1 = e->pos();
	}
}

void CScreen::mouseMoveEvent(QMouseEvent *e)
{
	if ( e->buttons() | Qt::LeftButton )
	{
		mSelectPt2 = e->pos();
		QRect r = QRect(mSelectPt1,mSelectPt2).normalized();
		cells().selectCells(r);
		update();
	}
}

void CScreen::mouseReleaseEvent(QMouseEvent *e)
{
	if ( e->buttons() | Qt::LeftButton )
	{
		update();
	}
}

void CScreen::setDefaultBackgroundColor(QColor defaultBackgroundColor)
{
	QPalette p = palette();
	p.setColor(QPalette::Window,defaultBackgroundColor);
	setPalette(p);
	setAutoFillBackground(true);
	mDefaultBackgroundColor=defaultBackgroundColor;
}

void CScreen::setDefaultForegroundColor(QColor defaultForegroundColor)
{
	mDefaultForegroundColor=defaultForegroundColor;
}

void CScreen::setBackgroundColor(QColor backgroundColor)
{
	mBackgroundColor=backgroundColor;
}


void CScreen::setForegroundColor(QColor foregroundColor)
{
	mForegroundColor=foregroundColor;
}

/** Return the selected text as a string object */
QString CScreen::selectedText()
{
	QString text;
	for( int y=0; y < rows(); y++ )
	{
		for( int x=0; x < cols(); x++ )
		{
			if ( cell(x,y).select() )
			{
				text += cell(x,y).character();
			}
		}
		if ( text.length() )
		{
			text += '\n';
		}
	}
	cells().deselectCells();
	return text.trimmed();
}

void CScreen::setCursorPos(QPoint& pt)
{
	setCursorPos(pt.x(),pt.y());
}

void CScreen::setCursorPos(int col,int row)
{
	if ( cells().indexOf(col,row) < cells().count() )
	{
		CCharCell& oldCell = cell(mCursor.x(),mCursor.y());
		CCharCell& newCell = cell(col,row);
		oldCell.setCursor(false);
		newCell.setCursor(true);
		mCursor.setX(col);
		mCursor.setY(row);
	}
}

/** Clear from the current cursor position to the end of the line */
void CScreen::clearEOL()
{
	for( int n=cursorPos().x(); n < cols(); n++ )
	{
		cell(n,cursorPos().y()).clear();
	}
}

/** Clear from the current cursor position to the beginning of the line */
void CScreen::clearBOL()
{
	for( int n=cursorPos().x(); n >= 0; n-- )
	{
		cell(n,cursorPos().y()).clear();
	}
}

/** Clear from the current cursor position to the end of display */
void CScreen::clearEOD()
{
	clearEOL();
	for( int y=cursorPos().y()+1; y < rows(); y++ )
	{
		for( int x=0; x < cols(); x++ )
		{
			cell(x,y).clear();
		}
	}
}


/** Clear from the beginning of display to current cursor position */
void CScreen::clearBOD()
{
	for( int y=0; y < cursorPos().y(); y++ )
	{
		for( int x=0; x < cols(); x++ )
		{
			cell(x,y).clear();
		}
	}
	clearBOL();
}

/** Clear the entire screen */
void CScreen::clear()
{
	setCursorPos(0,0);
	clearEOD();
}

/** Delete n chars from cursor position */
void CScreen::delChars(int num)
{
	for( int n=0; n < num; n++)
	{
		for( int x=cursorPos().x(); x < cols()-1; x++ )
		{
			CCharCell& from = cell(x+1,cursorPos().y());
			cell(x,cursorPos().y()).copy(from);
		}
		cell(cols()-1,cursorPos().y()).clear();
	}
	cells().sync();
}

/** Insert n lines */
void CScreen::insLines(int num)
{
	for( int n=0; n < num; n++)
	{
		for( int y=rows()-1; y > cursorPos().y(); y--)
		{
			for( int x=0; x < cols(); x++ )
			{
				CCharCell& from = cell(x,y-1);
				cell(x,y).copy(from);
			}
		}
		for( int x=0; x < cols(); x++)
		{
			cell(x,cursorPos().y()).clear();
		}
	}
	cells().sync();
}

/** Put a character */
void CScreen::putchar(char c,int x, int y)
{
	if ( x < 0 ) x = cursorPos().x();
	if ( y < 0 ) y = cursorPos().y();
	cell(x,y).setCharacter(c);
	cell(x,y).setBackgroundColor(backgroundColor());
	cell(x,y).setForegroundColor(foregroundColor());
	cell(x,y).setReverse(this->reverse());
}

/** advance the cursor and scroll if we need to */
bool CScreen::advanceCursor()
{
	if ( cursorPos().x() <cols()-1 )
	{
		setCursorPos(cursorPos().x()+1,cursorPos().y());
		return true;
	}
	return false;
}

/** scroll characters up */
void CScreen::scrollUp()
{
	QPoint pos = cursorPos();
	cells().scrollGrid(CCellArray::ScrollUp,0,0,cols(),rows());
	setCursorPos(pos);
}

/** scroll characters down */
void CScreen::scrollDown()
{
	QPoint pos = cursorPos();
	cells().scrollGrid(CCellArray::ScrollDown,0,0,cols(),rows());
	setCursorPos(pos);
}



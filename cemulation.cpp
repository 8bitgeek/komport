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
#include "cemulation.h"
#include <QString>
#include <QApplication>

CEmulation::CEmulation(CScreen* screen)
: mScreen(screen)
, mVisualBell(true)
, mLocalEcho(false)
{
}

CEmulation::~CEmulation()
{
}

/** move cursor to x,y */
void CEmulation::doCursorTo(int col, int row)
{
	if ( col >= 0 && row >= 0 && col < screen()->cols() && row < screen()->rows() )
	{
		screen()->setCursorPos(col,row);
	}
}

/** cursor up */
void CEmulation::doCursorUp()
{
	QPoint pos = screen()->cursorPos();
	if ( pos.y() > 0 )
	{
		pos.setY( pos.y()-1 );
		screen()->setCursorPos(pos);
	}
}

/** cursor down */
void CEmulation::doCursorDown()
{
	QPoint pos = screen()->cursorPos();
	if ( pos.y() < screen()->rows() )
	{
		pos.setY( pos.y()+1 );
		screen()->setCursorPos(pos);
	}
}

/** cursor left */
void CEmulation::doCursorLeft()
{
	QPoint pos = screen()->cursorPos();
	if ( pos.x() > 0 )
	{
		screen()->setCursorPos(pos.x()-1,pos.y());
	}
}

/** cursor right */
void CEmulation::doCursorRight()
{
	QPoint pos = screen()->cursorPos();
	if ( pos.x() < screen()->cols()-1 )
	{
		screen()->setCursorPos(pos.x()+1,pos.y());
	}
}

void CEmulation::doClearEOL(ClearLineMode mode)
{
	switch(mode) {
		case ClearLineEOL:  // cursor to EOL
			screen()->clearEOL();
		break;
		case ClearLineBOL: // BOL to cursor
		{
			screen()->clearBOL();
		 }
		 break;
		case ClearLineAOL: // full line
		{
			QPoint save = screen()->cursorPos();
			screen()->setCursorPos(0,save.y());
			screen()->clearEOL();
			screen()->setCursorPos(save);
		}
		break;
	}
}

void CEmulation::doClearScreen(ClearScreenMode mode)
{
	switch(mode) {
	case ClearScreenEOD:  // cursor to EOD
		screen()->clearEOD();
		break;
	case ClearScreenBOD: // BOD to cursor
		screen()->clearBOD();
		break;
	case ClearScreenAOD: // full display
		screen()->clear();
		break;
	}
}


/** delete character(s) in line */
void CEmulation::doDeleteCharacters(int num)
{
	screen()->delChars(num);
}

/** insert lines */
void CEmulation::doInsertLines(int num)
{
	screen()->insLines(num);
}

/** save cursor */
void CEmulation::doSaveCursor()
{
	mSaveCursor = screen()->cursorPos();
}

/** restore cursor */
void CEmulation::doRestoreCursor()
{
	screen()->setCursorPos(mSaveCursor);
}

/** ring a visual bell */
void CEmulation::doVisualBell()
{
	for( int flash=0; flash<2; flash++ )
	{
		for( int y=0; y < screen()->rows(); y++ )
		{
			for (int x=0; x < screen()->cols();x++ )
			{
				CCharCell& c = screen()->cell(x,y);
				c.setReverse( !c.reverse() );
			}
		}
		screen()->repaint();
	}
}

/** ring bell or perform visual bell */
void CEmulation::doBell()
{
	if ( visualBell() )
	{
		doVisualBell();
	}
	else
	{
		QApplication::beep();
	}
}

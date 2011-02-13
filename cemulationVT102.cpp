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
#include "cemulationVT102.h"
#include <QString>

#define ASCII_BEL   0x07
#define ASCII_BS    0x08
#define ASCII_LF    0x0A
#define ASCII_CR    0x0D
#define ASCII_ESC   0x1B

#define inherited CEmulation

CEmulationVT102::CEmulationVT102(CScreen* screen)
: inherited(screen)
, mSawESC(false)
, mInCtlSequence(false)
, mInsertMode(false)
, mCursorOn(true)
{
}

CEmulationVT102::~CEmulationVT102()
{
}

/** do graphics attributes */
void CEmulationVT102::doGraphics()
{
	int index=0;
	int sep=0;
	if ( mCtlSequence.isEmpty() )
	mCtlSequence = "0";
	do {
		sep = mCtlSequence.indexOf( ';', index );
		if ( sep < 0 )
		  sep = mCtlSequence.length();
		QByteArray attrStr = mCtlSequence.mid( index, mCtlSequence.indexOf(';',index)-index );
		index = sep+1;
		if ( !attrStr.isEmpty() )
		{
			int attr = attrStr.toInt();
			switch(attr)
			{
				//    Text attributes
				case 0:   //    All attributes off
					{
					screen()->setBackgroundColor(screen()->backgroundColor());
					screen()->setForegroundColor(screen()->foregroundColor());
					screen()->setBlink(false);
					screen()->setBold(false);
					screen()->setReverse(false);
					screen()->setUnderline(false);
					}
					break;
				case 1:   //    Bold on
					screen()->setBold(true);
					break;
				case 4:   //    Underscore on
					screen()->setUnderline(true);
					break;
				case 5:   //    Blink on
					screen()->setBlink(true);
					break;
				case 7:   //    Reverse video on
					screen()->setReverse(true);
					break;
				case 8:   //    Concealed on
					break;

				//    Foreground colors
				case 30:  //    Black
					screen()->setForegroundColor(QColor(0,0,0));       break;
				case 31:  //    Red
					screen()->setForegroundColor(QColor(255,0,0));     break;
				case 32:  //    Green
					screen()->setForegroundColor(QColor(0,255,0));     break;
				case 33:  //    Yellow
					screen()->setForegroundColor(QColor(240,240,10));  break;
				case 34:  //    Blue
					screen()->setForegroundColor(QColor(0,0,255));     break;
				case 35:  //    Magenta
					screen()->setForegroundColor(QColor(215,15,230));  break;
				case 36:  //    Cyan
					screen()->setForegroundColor(QColor(10,240,230));  break;
				case 37:  //    White
				case 38:
				case 39:
					screen()->setForegroundColor(QColor(255,255,255)); break;

				//  Background colors
				case 40:  //    Black
					screen()->setBackgroundColor(QColor(0,0,0));       break;
				case 41:  //    Red
					screen()->setBackgroundColor(QColor(255,0,0));     break;
				case 42:  //    Green
					screen()->setBackgroundColor(QColor(0,255,0));     break;
				case 43:  //    Yellow
					screen()->setForegroundColor(QColor(240,240,10));  break;
				case 44:  //    Blue
					screen()->setBackgroundColor(QColor(0,0,255));     break;
				case 45:  //    Magenta
					screen()->setBackgroundColor(QColor(215,15,230));  break;
				case 46:  //    Cyan
					screen()->setBackgroundColor(QColor(10,240,230));  break;
				case 47:  //    White
				case 48:
				case 49:
					screen()->setBackgroundColor(QColor(255,255,255)); break;

				default:
					printf( "?attr? %d\n", attr);
					break;
			}
		}
	} while( sep < (unsigned int)mCtlSequence.length() );
}

/*
Reset and set modes
  Set Modes
	Esc  [ <c> ; ... ; <c> h
	033 133   073   073   150
  Reset Modes
	Esc  [ <c> ; ... ; <c> l
	033 133   073   073   154

  Where <c> is
	'2'= Lock keyboard (set); Unlock keyboard (reset)
	'4'= Insert mode (set); Replace mode (reset)
   '12'= Echo on (set); Echo off (reset)
   '20'= Return = CR+LF (set); Return = CR (reset)
   '?1'= Cursorkeys application (set); Cursorkeys normal (reset)
   '?2'= Ansi (set); VT52 (reset)
   '?3'= 132 char/row (set); 80 char/row (reset)
   '?4'= Jump scroll (set); Smooth scroll (reset)
   '?5'= Reverse screen (set); Normal screen (reset)
   '?6'= Sets relative coordinates (set); Sets absolute coordinates (reset)
   '?7'= Auto wrap (set); Auto wrap off (reset)
   '?8'= Auto repeat on (set); Auto repeat off (reset)
  '?18'= Send FF to printer after print screen (set); No char after PS (reset)
  '?19'= Print screen prints full screen (set); PS prints scroll region (reset)
  '?25'= Cursor on (set); Cursor off (reset)
*/

/** set terminal modes */
void CEmulationVT102::doSetModes()
{
	int index=0;
	int sep=0;
	if ( mCtlSequence.isEmpty() )
	mCtlSequence = "0";
	do {
		sep = mCtlSequence.indexOf( ';', index );
		if ( sep < 0 )
			sep = mCtlSequence.length();
		QByteArray attrStr = mCtlSequence.mid( index, mCtlSequence.indexOf(';',index)-index );
		index = sep+1;
		if ( !attrStr.isEmpty() )
		{
			int attr = attrStr.toInt();
			switch(attr)
			{
				//    Text attributes
				case 0:   //    huh?
					break;
				case 4:   //    insert mode
					mInsertMode=true;
					break;
				case 25:  // cursor on
					mCursorOn=true;
					emit cursorOn();
					break;

				default:
					printf( "?attr? %d\n", attr);
					break;
			}
		}
	} while( sep < (unsigned int)mCtlSequence.length() );
}

/** reset terminal modes */
void CEmulationVT102::doResetModes()
{
	int index=0;
	int sep=0;
	if ( mCtlSequence.isEmpty() )
		mCtlSequence = "0";
	do {
		sep = mCtlSequence.indexOf( ';', index );
		if ( sep < 0 )
		  sep = mCtlSequence.length();
		QByteArray attrStr = mCtlSequence.mid( index, mCtlSequence.indexOf(';',index)-index );
		index = sep+1;
		if ( !attrStr.isEmpty() )
		{
			int attr = attrStr.toInt();
			switch(attr)
			{
				//    Text attributes
				case 0:   // huh?
					break;
				case 4:   //    insert mode
					mInsertMode=false;
					break;
				case 25: // cursor off
					mCursorOn=false;
					emit cursorOff();
					break;
				default:
					printf( "?attr? %d\n", attr);
					break;
			}
		}
	} while( sep < (unsigned int)mCtlSequence.length() );
}

// set scroll region
void CEmulationVT102::doSetScrollRegion()
{
  printf( "emulation: setScrollRegion()\n" );
}

// received part of an escape sequence
void CEmulationVT102::sequence(char _ch)
{
	bool completed=(_ch>='a'&&_ch<='z')||(_ch>='A'&&_ch<='Z');

	if ( completed )
	{
		switch( _ch )
		{
			case 'H':   // cursor position
			case 'f':
				{
					int sep = mCtlSequence.indexOf( ';' );
					if ( sep >= 0 )
					{
						QByteArray rowStr = mCtlSequence.left( sep );
						++sep;
						QByteArray colStr = mCtlSequence.right( mCtlSequence.length()-sep );
						int row = rowStr.toInt()-1;
						int col = colStr.toInt()-1;
						doCursorTo(col,row);
					}
					else
					{
						doCursorTo(0,0);
					}
				}
			break;
			case 'A':   // cursor up
				doCursorUp();
			break;
			case 'B':   // cursor down
				doCursorDown();
			break;
			case 'C':   // cursor forward
				doCursorRight();
			break;
			case 'D':   // cursor backward
				doCursorLeft();
			break;
			case 'J':   // erase display
				{
					int attr = mCtlSequence.isEmpty() ? 0 : mCtlSequence.toInt();
					switch(attr) {
					case 0:  // cursor to EOD
						doClearScreen(ClearScreenEOD);
						break;
					case 1: // BOD to cursor
						doClearScreen(ClearScreenBOD);
						break;
					case 2: // full display
						doClearScreen(ClearScreenAOD);
						break;
					}
				}
				break;
			case 'h':    // set modes
				doSetModes();
			break;
			case 'K':   // erase line
				{
					int attr = mCtlSequence.isEmpty() ? 0 : mCtlSequence.toInt();
					switch(attr) {
						case 0:  // cursor to EOL
							doClearEOL(ClearLineEOL);
						break;
						case 1: // BOL to cursor
						{
							doClearEOL(ClearLineBOL);
						 }
						 break;
						case 2: // full line
						{
							doClearEOL(ClearLineBOL);
						}
						break;
					}
				}
				break;
			case 'L':    // insert line(s)
				{
					int num = mCtlSequence.isEmpty() ? 1 : mCtlSequence.toInt();
					doInsertLines(num);
				}
			break;
			case 'l':     // reset modes
				doResetModes();
			break;
			case 'm':   // graphics attributes
				doGraphics();
			break;
			case 'P':   // delete character(s)
				{
					int num = mCtlSequence.isEmpty() ? 1 : mCtlSequence.toInt();
					doDeleteCharacters(num);
				}
			break;
			case 'r':   // set scroll region
				doSetScrollRegion();
			break;
			case 's':   // save cursor position
				doSaveCursor();
			break;
			case 'u':   // restore cursor position
				doRestoreCursor();
			break;
			default:
				printf( "emulation: unknown '%c' in ESC[%s%c\n", _ch,  mCtlSequence.data()==NULL?"": mCtlSequence.data(),_ch);
			break;
		}
		mSawESC = false;
		mInCtlSequence = false;
		mCtlSequence.resize(0);
	}
	else
	{
		mCtlSequence += _ch;
	}
}

// received a char */
void CEmulationVT102::receiveChar(char _ch)
{
	// handle the terminal control sequence...
	if ( _ch == ASCII_ESC && !mSawESC && !mInCtlSequence )
	{
		mSawESC = true;
		return;
	}
	if ( _ch == '[' && mSawESC && !mInCtlSequence  )
	{
		mInCtlSequence=true;
		mCtlSequence.resize(0);
		return;
	}
	if ( mInCtlSequence )
	{
		sequence(_ch);
		return;
	}

	// handle standard dumb terminal codes and printable ASCII....
	switch(_ch)
	{
	case ASCII_BEL:
		{
		doBell();
		}
		break;
	case ASCII_BS:
		doCursorLeft();
		break;
	case ASCII_LF:
		{
			QPoint pos = screen()->cursorPos();
			if ( pos.y() >= screen()->rows()-1 )
			{
				screen()->scrollUp();
			}
			else
			{
				screen()->setCursorPos(pos.x(),pos.y()+1);
			}
		}
		break;
	case ASCII_CR:
		{
			QPoint pos = screen()->cursorPos();
			screen()->setCursorPos(0,pos.y());
		}
		break;
	default:
		if ( mInsertMode )
		{
			int y = screen()->cursorPos().y();
			for( int x=screen()->rows()-1; x > screen()->cursorPos().x(); x-- )
			{
				screen()->cell(x,y).copy( screen()->cell(x-1,y) );
			}
			screen()->cell( screen()->cursorPos() ).clear();
		}
		screen()->putchar(_ch,screen()->cursorPos());
		screen()->advanceCursor();
		break;
	}
}

/** simulated key press for pasting from clipboard, etc... */
void CEmulationVT102::keyPressEvent(QKeyEvent* e)
{
	switch( e->key() )
	{
		case Qt::Key_Insert:	emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[1~");  break;
		case Qt::Key_Delete:	emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[4~"); break;
		case Qt::Key_Home:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[2~"); break;
		case Qt::Key_End:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[5~"); break;
		case Qt::Key_PageUp:	emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[3~"); break;
		case Qt::Key_PageDown:	emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[6~"); break;
		case Qt::Key_Left:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[D"); break;
		case Qt::Key_Up:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[A"); break;
		case Qt::Key_Right:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[C"); break;
		case Qt::Key_Down :		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[B"); break;
		default:
		{
			emit sendAsciiString(e->text().toAscii().data());
			if ( localEcho() )
			{
				for ( int n=0; n < e->text().length(); n++ )
				{
					char c = e->text().toAscii().at(n);
					receiveChar(c);
				}
			}
			break;
		}
	}
}



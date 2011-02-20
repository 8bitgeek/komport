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

#define ASCII_ENQ   0x05
#define ASCII_NUL   0x00
#define ASCII_SO    0x0E
#define ASCII_SI    0x0F
#define ASCII_CSI   0x9B
#define ASCII_BEL   0x07
#define ASCII_BS    0x08
#define ASCII_LF    0x0A
#define ASCII_CR    0x0D
#define ASCII_ESC   0x1B

#define inherited CEmulation

CEmulationVT102::CEmulationVT102(CScreen* screen)
: inherited(screen)
, mApplicationCursorKeys(false)
, mOriginMode(false)
, mTopMargin(0)
, mBottomMargin(0)
{
	QObject::connect(this,SIGNAL(codeNotHandled()),this,SLOT(doCodeNotHandled()));
}

CEmulationVT102::~CEmulationVT102()
{
}

/** Parse out the attributes from a control string */
bool CEmulationVT102::attributes(QList<int>& attrs, QList<int>& extAttrs)
{
	QString num;
	for( int n=0; n < mControlCode.length(); n++ )
	{
		if ( mControlCode.at(n) == '?' )
		{
			++n;
			while(n < mControlCode.count() && isdigit(mControlCode.at(n)))
			{
				num = num + mControlCode.at(n);
				++n;
			}
			extAttrs.append( num.toInt() );
			num="";
		}
		else
		{
			while(n < mControlCode.count() && isdigit(mControlCode.at(n)))
			{
				num = num + mControlCode.at(n);
				++n;
			}
			attrs.append( num.toInt() );
			num="";
		}
	}
	return ( attrs.count() > 0 || extAttrs.count() > 0 );
}


/** reset to initial state */
void CEmulationVT102::doReset()
{
	/* FIXME - do something here */
	printf( "FIXME - doReset()\n" );
	inherited::doReset();
}

/** An escape code was not handled, let's have a look at it. */
void CEmulationVT102::doCodeNotHandled()
{
	putchar('<');
	if ( mControlCode.length() > 1 )
	{
		for( int n=0; n < mControlCode.length(); n++ )
		{
			putchar(mControlCode.data()[n]);
		}
		putchar(mChar);
	}
	else
	{
		putchar(mChar);
	}
	putchar('>');
	fflush(stdout);
}

/** position cursor */
void CEmulationVT102::doCursorTo(int col, int row)
{
	//if ( originMode() )
	//{
	//	row += topMargin();
	//	if ( row <= bottomMargin() )
	//	{
	//		inherited::doCursorTo(col,row);
	//	}
	//}
	//else
	//{
		inherited::doCursorTo(col,row);
	//}
}

/** cursor up one row */
void CEmulationVT102::doCursorUp()
{
	QList<int> attrs;
	QList<int> extAttrs;
	attributes(attrs,extAttrs);
	for( int y =  ( attrs.count() && attrs.at(0) > 0 ) ? attrs.at(0) : 1; y > 0; y-- )
	{
		if ( !originMode() || (originMode() && cursorPos().y() > topMargin() ) )
		{
			inherited::doCursorUp();
		}
	}
}

/** cursor down one row. */
void CEmulationVT102::doCursorDown()
{
	QList<int> attrs;
	QList<int> extAttrs;
	attributes(attrs,extAttrs);
	for( int y =  ( attrs.count() && attrs.at(0) > 0 ) ? attrs.at(0) : 1; y > 0; y-- )
	{
		if ( !originMode() || (originMode() && cursorPos().y() < bottomMargin() ) )
		{
			inherited::doCursorDown();
		}
	}
}

/** cursor left one column  */
void CEmulationVT102::doCursorLeft()
{
	QList<int> attrs;
	QList<int> extAttrs;
	attributes(attrs,extAttrs);
	for( int x =  ( attrs.count() && attrs.at(0) > 0 ) ? attrs.at(0) : 1; x > 0; x-- )
	{
		inherited::doCursorLeft();
	}
}

/** cursor right one column  */
void CEmulationVT102::doCursorRight()
{
	QList<int> attrs;
	QList<int> extAttrs;
	attributes(attrs,extAttrs);
	for( int x =  ( attrs.count() && attrs.at(0) > 0 ) ? attrs.at(0) : 1; x > 0; x-- )
	{
		inherited::doCursorRight();
	}
}

/** Set the top margin */
void CEmulationVT102::setTopMargin(int top)
{
	mTopMargin = top;
}

/** Set the bottom margin */
void CEmulationVT102::setBottomMargin(int bottom)
{
	mBottomMargin = bottom;
}

/** scroll up */
void CEmulationVT102::doScrollUp()
{
	if ( originMode() )
	{
		screen()->cells().scrollGrid(CCellArray::ScrollUp,0,topMargin(),cols(),(bottomMargin()-topMargin())+1);
	}
	else
	{
		inherited::doScrollUp();
	}
}

/** new line */
void CEmulationVT102::doNewLine()
{
	if ( originMode() )
	{
		QPoint pos = screen()->cursorPos();
		if ( pos.y() >= bottomMargin() )
		{
			doScrollUp();
		}
		else
		{
			inherited::doNewLine();
		}
	}
	else
	{
		inherited::doNewLine();
	}
}

void CEmulationVT102::setGrid(int cols,int rows)
{
	setTopMargin(0);
	setBottomMargin(rows);
	inherited::setGrid(cols,rows);
}

/** do report */
void CEmulationVT102::doReport()
{
	QList<int> attrs;
	QList<int> extAttrs;
	attributes(attrs,extAttrs);
	if ( attrs.count() )
	{
		switch(attrs.at(0))
		{
			case 5: /* Device Status Report */
				emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[3n"); /* OK */
				break;
			case 6: /* Cursor Position Report */
				{
					QString coords;
					coords.sprintf("[%d;%dR",cursorPos().y()+1,cursorPos().x()+1);
					emit sendAsciiChar(ASCII_ESC); emit sendAsciiString(coords.toAscii().data());
				}
				break;
			default:
				emit codeNotHandled();
				break;
		}
	}
	if ( extAttrs.count() )
	{
		switch(extAttrs.at(0))
		{
			case 15: /* Printer status report */
				emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[?10n"); /* OK */
				break;
			default:
				emit codeNotHandled();
				break;
		}
	}
}

/** do device attributes */
void CEmulationVT102::doDeviceAttributes()
{
	QList<int> attrs;
	QList<int> extAttrs;
	attributes(attrs,extAttrs);
	if ( !attrs.count() )
		attrs.append(0);
	switch(attrs.at(0))
	{
		case 0: /* Device Attributes (terminal ID) */
			emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[?6c"); /* VT102 */
			break;
		default:
			emit codeNotHandled();
			break;
	}
}

/** do graphics attributes */
void CEmulationVT102::doGraphics()
{
	QList<int> attrs;
	QList<int> extAttrs;
	attributes(attrs,extAttrs);
	if (attrs.count() == 0 ) attrs.append(0);
	for( int n=0; n < attrs.count(); n++ )
	{
		switch(attrs.at(n))
		{
			//    Text attributes
			case 0:   //    All attributes off
				{
					screen()->setBackgroundColor(screen()->defaultBackgroundColor());
					screen()->setForegroundColor(screen()->defaultForegroundColor());
					screen()->setBlink(false);
					screen()->setBold(false);
					screen()->setReverse(false);
					screen()->setUnderline(false);
				}
				break;
			case 1:   /* Bold on */
				screen()->setBold(true);
				break;
			case 4:   /* Underscore on */
				screen()->setUnderline(true);
				break;
			case 5:   /* Blink on */
				screen()->setBlink(true);
				break;
			case 7:   /* Reverse video on */
				screen()->setReverse(true);
				break;
			case 8:   /* Concealed on */
				break;

			/* Foreground colors */
			case 30:  /* Black */
				screen()->setForegroundColor(QColor(0,0,0));       break;
			case 31:  /* Red */
				screen()->setForegroundColor(QColor(255,0,0));     break;
			case 32:  /* Green */
				screen()->setForegroundColor(QColor(0,255,0));     break;
			case 33:  /* Yellow */
				screen()->setForegroundColor(QColor(240,240,10));  break;
			case 34:  /* Blue */
				screen()->setForegroundColor(QColor(0,0,255));     break;
			case 35:  /* Magenta */
				screen()->setForegroundColor(QColor(215,15,230));  break;
			case 36:  /* Cyan */
				screen()->setForegroundColor(QColor(10,240,230));  break;
			case 37:  /* White */
				screen()->setForegroundColor(QColor(255,255,255)); break;
			case 38:
			case 39:
				screen()->setForegroundColor(screen()->defaultForegroundColor());
				break;

			/* Background colors */
			case 40:  /* Black */
				screen()->setBackgroundColor(QColor(0,0,0));       break;
			case 41:  /* Red */
				screen()->setBackgroundColor(QColor(255,0,0));     break;
			case 42:  /* Green */
				screen()->setBackgroundColor(QColor(0,255,0));     break;
			case 43:  /* Yellow */
				screen()->setForegroundColor(QColor(240,240,10));  break;
			case 44:  /* Blue */
				screen()->setBackgroundColor(QColor(0,0,255));     break;
			case 45:  /* Magenta */
				screen()->setBackgroundColor(QColor(215,15,230));  break;
			case 46:  /* Cyan */
				screen()->setBackgroundColor(QColor(10,240,230));  break;
			case 47:  /* White */
				screen()->setBackgroundColor(QColor(255,255,255)); break;
			case 48:
			case 49:
				screen()->setBackgroundColor(screen()->defaultBackgroundColor());
				break;

			default:
				emit codeNotHandled();
				break;
		}
	}
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
	QList<int> attrs;
	QList<int> extAttrs;
	attributes(attrs,extAttrs);
	for( int n=0; n < attrs.count(); n++ )
	{
		switch(attrs.at(n))
		{
		case 2:			/* keyboard lock */
			setKeyboardLock(true);
			break;
		case 4:			/* insert mode */
			setAutoInsert(true);
			break;
		case 12:		/* set echo mode */
			setLocalEcho(true);
			break;
		case 20:		/* auto new line */
			setAutoNewLine(true);
			break;
		default:
			emit codeNotHandled();
			break;
		}
	}
	for( int n=0; n < extAttrs.count(); n++ )
	{
		switch(extAttrs.at(n))
		{
		case 1:		/* application cursor keys */
			setApplicationCursorKeys(true);
			break;
		case 3:		/* 132 columns */
			setCols(132);
			break;
		case 4:		/* jump scroll */
			setJumpScroll(true);
			break;
		case 5:		/* reverse video */
			setReverseVideo(true);
			break;
		case 6:		/* origin mode */
			setOriginMode(true);
			break;
		case 7:		/* auto wrap */
			setAutoWrap(true);
			break;
		case 25:	/* cursor on */
			setCursorOn(true);
			break;
		default:
			emit codeNotHandled();
			break;
		}
	}
}

/** reset terminal modes */
void CEmulationVT102::doResetModes()
{
	QList<int> attrs;
	QList<int> extAttrs;
	attributes(attrs,extAttrs);
	for( int n=0; n < attrs.count(); n++ )
	{
		switch(attrs.at(n))
		{
		case 2:			/* keyboard lock */
			setKeyboardLock(false);
			break;
		case 4:			/* insert mode */
			setAutoInsert(false);
			break;
		case 12:		/* set echo mode */
			setLocalEcho(false);
			break;
		case 20:		/* auto new line */
			setAutoNewLine(false);
			break;
		default:
			emit codeNotHandled();
			break;
		}
	}
	for( int n=0; n < extAttrs.count(); n++ )
	{
		switch(extAttrs.at(n))
		{
		case 1:			/* application cursor keys */
			setApplicationCursorKeys(false);
			break;
		case 3:   /* 80 columns */
			setCols(80);
			break;
		case 4:   /* jump scroll */
			setJumpScroll(false);
			break;
		case 5:   /* reverse video */
			setReverseVideo(false);
			break;
		case 6:   /* origin mode */
			setOriginMode(false);
			break;
		case 7:   /* auto wrap */
			setAutoWrap(false);
			break;
		case 25:  /* cursor on */
			setCursorOn(false);
			break;
		default:
			emit codeNotHandled();
			break;
		}
	}
}

/* set scroll region */
void CEmulationVT102::doSetScrollRegion()
{
	QList<int> attrs;
	QList<int> extAttrs;
	attributes(attrs,extAttrs);
	if ( attrs.count() == 2 && attrs.at(0) < attrs.at(1) )
	{
		setTopMargin(attrs.at(0)-1);
		setBottomMargin(attrs.at(1)-1);
	}
	else
		emit codeNotHandled();
}


/* do cursor position */
void CEmulationVT102::doCursorPosition()
{
	QList<int> attrs;
	QList<int> extAttrs;
	int row=0;
	int col=0;
	attributes(attrs,extAttrs);
	if ( attrs.count() == 2 )
	{
		row=attrs.at(0)-1;
		col=attrs.at(1)-1;
	}
	doCursorTo(col,row);
}

/* handle a CSI sequence */
void CEmulationVT102::doCSI(unsigned char ch)
{
	switch( (mChar=ch) )
	{
	case 'H':   /* cursor position */
	case 'f':
		doCursorPosition();
		break;
	case 'A':   /* cursor up */
		doCursorUp();
		break;
	case 'B':   /* cursor down */
		doCursorDown();
		break;
	case 'C':   /* cursor forward */
		doCursorRight();
		break;
	case 'D':   /* cursor backward */
		doCursorLeft();
		break;
	case 'J':   /* erase display */
		{
			int attr = mControlCode.isEmpty() ? 0 : mControlCode.toInt();
			switch(attr)
			{
			case 0:  /* cursor to EOD */
				doClearScreen(ClearScreenEOD);
				break;
			case 1: /* BOD to cursor */
				doClearScreen(ClearScreenBOD);
				break;
			case 2: /* full display */
				doClearScreen(ClearScreenAOD);
				break;
			}
		}
		break;
	case 'h':    /* set modes */
		doSetModes();
		break;
	case 'K':   /* erase line */
		{
			int attr = mControlCode.isEmpty() ? 0 : mControlCode.toInt();
			switch(attr)
			{
			case 0:  /* cursor to EOL */
				doClearEOL(ClearLineEOL);
				break;
			case 1: /* BOL to cursor */
				doClearEOL(ClearLineBOL);
				break;
			case 2: /* full line */
				doClearEOL(ClearLineAOL);
				break;
			}
		}
		break;
	case 'L':    /* insert line(s) */
		{
			int num = mControlCode.isEmpty() ? 1 : mControlCode.toInt();
			doInsertLines(num);
		}
		break;
	case 'c':   /* device attributes */
		doDeviceAttributes();
		break;
	case 'l':     /* reset modes */
		doResetModes();
		break;
	case 'm':   /* graphics attributes */
		doGraphics();
		break;
	case 'n':  /* reports */
		doReport();
		break;
	case 'P':   /* delete character(s) */
		{
			int num = mControlCode.isEmpty() ? 1 : mControlCode.toInt();
			doDeleteCharacters(num);
		}
		break;
	case 'r':   /* set scroll region */
		setOriginMode(true);
		doSetScrollRegion();
		doCursorTo(0,0);
		break;
	case 's':   /* save cursor position */
		doSaveCursorPos();
		break;
	case 'u':   /* restore cursor position */
		doRestoreCursorPos();
		break;
	default:
		emit codeNotHandled();
		break;
	}
}

/* process escape codes */
char CEmulationVT102::doLeadIn(unsigned char ch)
{
	if ( ch == ASCII_ESC && mControlCode.length() == 0 )
	{
		/* ESC char with no-leadin started */
		mControlCode.append(ch);
		return ASCII_NUL;
	}
	else if ( ch == ASCII_ESC && mControlCode.length() )
	{
		/* ESC char with leadin started */
		mControlCode.clear();
		return doLeadIn(ch);
	}
	else if ( ch == ASCII_CSI && mControlCode.length() == 0 )
	{
		/* CSI char with no leadin started */
		mControlCode.append(ASCII_ESC);
		mControlCode.append('[');
		return ASCII_NUL;
	}
	else if ( ch == ASCII_CSI && mControlCode.length() )
	{
		/* CSI char with leadin started */
		mControlCode.clear();
		return doLeadIn(ch);
	}
	else if ( mControlCode.length() == 1 && mControlCode.at(0) == ASCII_ESC )
	{
		/* ESC character seen so far */
		switch ((mChar=ch))
		{
			case '[':		/* This is a multi-character lead in sequence. */
			case ')':
			case '(':
				mControlCode.append(ch);
				return ASCII_NUL;
				break;
			case 'M':		/* Cursor up. */
				doCursorUp();
				break;
			case 'D':		/* Index */
				doNewLine();
				break;
			case 'E':		/* Next Line. */
				doCarriageReturn();
				doNewLine();
				break;
			case '7':		/* (DECSC) save state. */
				doSaveCursorPos();
				break;
			case '8':		/* (DECRS) restore saved state. */
				doRestoreCursorPos();
				break;
			case 'H':		/* FIXME (HTS) set tab stop at current column. */
				emit codeNotHandled();
				break;
			case 'g':		/* visual bell. */
				doVisualBell();
				break;
			case 'c':		/* reset terminal */
				doReset();
				break;
			case 'Z':		/* Identify Terminal */
				doDeviceAttributes();
				break;
			default:		/* did not understand escape code. */
				emit codeNotHandled();
				break;
		}
		mControlCode.clear();
		return ASCII_NUL;
	}
	else if ( mControlCode.length() >= 2 )
	{
		switch ( mControlCode.at(1) )
		{
		case '[':
			if ( mControlCode.at(1) == '[' )
			{
				if ( (ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z') )
				{
					mControlCode.remove(0,2);
					doCSI(ch);
					mControlCode.clear();
					return ASCII_NUL;
				}
				else
				{
					mControlCode.append(ch);
					if ( mControlCode.length()>25)
					{
						mControlCode.clear();
					}
				}
			}
			break;
		case '(':
		case ')':
			mControlCode.clear();
			break;
		default:
			mControlCode.clear();
			break;
		}
		return ASCII_NUL;
	}
	return ch;
}

/* received a char */
void CEmulationVT102::receiveChar(unsigned char ch)
{
	if ( ch < ' ' || ch > '~' )
		printf("$%02x",ch);
	else
		putchar(ch);
	fflush(stdout);
	switch( (ch = doLeadIn(ch)) )
	{
		case ASCII_ENQ:
		case ASCII_SO:
		case ASCII_SI:
		case ASCII_NUL:
			break;
		case ASCII_BEL:
			doBell();
			break;
		case ASCII_BS:
			doCursorLeft();
			break;
		case ASCII_LF:
			doNewLine();
			break;
		case ASCII_CR:
			doCarriageReturn();
			break;
		default:
			doChar(ch);
			break;
	}
	mChar='\0';
}

/** simulated key press for pasting from clipboard, etc... */
void CEmulationVT102::keyPressEvent(QKeyEvent* e)
{
	if ( !keyboardLock() )
	{
		if (applicationCursorKeys() )
		{
			switch( e->key() )
			{
				case Qt::Key_Insert:	emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[1~"); break;
				case Qt::Key_Delete:	emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[4~"); break;
				case Qt::Key_Home:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[2~"); break;
				case Qt::Key_End:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[5~"); break;
				case Qt::Key_PageUp:	emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[3~"); break;
				case Qt::Key_PageDown:	emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[6~"); break;
				case Qt::Key_Up:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("OA"); break;
				case Qt::Key_Down:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("OB"); break;
				case Qt::Key_Right:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("OC"); break;
				case Qt::Key_Left:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("OD"); break;
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
		else
		{
			switch( e->key() )
			{
				case Qt::Key_Insert:	emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[1~"); break;
				case Qt::Key_Delete:	emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[4~"); break;
				case Qt::Key_Home:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[2~"); break;
				case Qt::Key_End:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[5~"); break;
				case Qt::Key_PageUp:	emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[3~"); break;
				case Qt::Key_PageDown:	emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[6~"); break;
				case Qt::Key_Up:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[A"); break;
				case Qt::Key_Down:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[B"); break;
				case Qt::Key_Right:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[C"); break;
				case Qt::Key_Left:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[D"); break;
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
	}
}




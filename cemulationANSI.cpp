/**************************************************************************
*   Author <mike@8bitgeek.net> Mike Sharkey                               *
*   Copyright (C) 2020 by Pike Aerospace Research Corporation             *
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
#include "cemulationANSI.h"
#include <QString>

//#define DEBUG_RX 1

#define inherited CEmulation

CEmulationANSI::CEmulationANSI(CScreen* screen)
: inherited(screen)
, mApplicationCursorKeys(false)
, mOriginMode(false)
, mTopMargin(0)
, mBottomMargin(0)
{
	QObject::connect(this,SIGNAL(codeNotHandled()),this,SLOT(doCodeNotHandled()));
}

CEmulationANSI::~CEmulationANSI()
{
}

/** Parse out the attributes from a control string */
bool CEmulationANSI::attributes(QList<int>& attrs, QList<int>& extAttrs)
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
void CEmulationANSI::doReset()
{
	/* FIXME - do something here */
	printf( "FIXME - doReset()\n" );
	inherited::doReset();
}

/** An escape code was not handled, let's have a look at it. */
void CEmulationANSI::doCodeNotHandled()
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
void CEmulationANSI::doCursorTo(int col, int row)
{
	if ( col < 0 ) col = 0;
	if ( row < 0 ) row = 0;
	if ( col >= screen()->cols() ) col = screen()->cols()-1;
	if ( row >= screen()->rows() ) row = screen()->rows()-1;
	screen()->setCursorPos(col,row);
}

/** cursor up one row */
void CEmulationANSI::doCursorUp()
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
void CEmulationANSI::doCursorDown()
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
void CEmulationANSI::doCursorLeft()
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
void CEmulationANSI::doCursorRight()
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
void CEmulationANSI::setTopMargin(int top)
{
	mTopMargin = top;
}

/** Set the bottom margin */
void CEmulationANSI::setBottomMargin(int bottom)
{
	mBottomMargin = bottom;
}

/** scroll up */
void CEmulationANSI::doScrollUp()
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

/** scroll down */
void CEmulationANSI::doScrollDown()
{
	if ( originMode() )
	{
		screen()->cells().scrollGrid(CCellArray::ScrollDown,0,topMargin(),cols(),(bottomMargin()-topMargin())+1);
	}
	else
	{
		inherited::doScrollDown();
	}
}

/** new line */
void CEmulationANSI::doNewLine()
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

/** do reverse new line */
void CEmulationANSI::doReverseNewLine()
{
	if ( originMode() )
	{
		QPoint pos = screen()->cursorPos();
		if ( pos.y() <= topMargin() )
		{
			doScrollDown();
		}
		else
		{
			inherited::doReverseNewLine();
		}
	}
	else
	{
		inherited::doReverseNewLine();
	}
}

void CEmulationANSI::setGrid(int cols,int rows)
{
	setTopMargin(0);
	setBottomMargin(rows);
	inherited::setGrid(cols,rows);
}

/** do report */
void CEmulationANSI::doReport()
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
					coords.asprintf("[%d;%dR",cursorPos().y()+1,cursorPos().x()+1);
                    emit sendAsciiChar(ASCII_ESC); emit sendAsciiString(coords.toLatin1().data());
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
void CEmulationANSI::doDeviceAttributes()
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
void CEmulationANSI::doGraphics()
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
void CEmulationANSI::doSetModes()
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
void CEmulationANSI::doResetModes()
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
void CEmulationANSI::doSetScrollRegion()
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
void CEmulationANSI::doCursorPosition()
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
void CEmulationANSI::doCSI(unsigned char ch)
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
char CEmulationANSI::doLeadIn(unsigned char ch)
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
			case 'M':		/* Reverse Index (Cursor Up) */
				doReverseNewLine();
				break;
			case 'D':		/* Index (Cursor Down) */
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
void CEmulationANSI::receiveChar(unsigned char ch)
{
	#ifdef DEBUG_RX
		if ( ch < ' ' || ch > '~' )
			printf("$%02x",ch);
		else
			putchar(ch);
		fflush(stdout);
	#endif
	inherited::receiveChar((ch = doLeadIn(ch)));
	mChar='\0';
}

/** process key press... */
void CEmulationANSI::keyPressEvent(QKeyEvent* e)
{
	if ( keyboardLock() )
	{
		e->ignore();
	}
	else
	{
		e->accept();
		switch( e->key() )
		{
			case Qt::Key_Insert:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[2~"); break;
			case Qt::Key_Delete:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[3~"); break;
			case Qt::Key_PageUp:		emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[5~"); break;
			case Qt::Key_PageDown:	emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[6~"); break;
			case Qt::Key_F1:				emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("OP"); break;
			case Qt::Key_F2:				emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("OQ"); break;
			case Qt::Key_F3:				emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("OR"); break;
			case Qt::Key_F4:				emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("OS"); break;
			case Qt::Key_F5:				emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[15~"); break;
			case Qt::Key_F6:				emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[17~"); break;
			case Qt::Key_F7:				emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[18~"); break;
			case Qt::Key_F8:				emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[19~"); break;
			case Qt::Key_F9:				emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[20~"); break;
			case Qt::Key_F10:				emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[21~"); break;
			case Qt::Key_F11:				emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[23~"); break;
			case Qt::Key_F12:				emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[24~"); break;
			default:
				if (applicationCursorKeys() )
				{
					switch( e->key() )
					{
						case Qt::Key_Home:			emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("OH"); break;
						case Qt::Key_End:				emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("OF"); break;
						case Qt::Key_Up:				emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("OA"); break;
						case Qt::Key_Down:			emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("OB"); break;
						case Qt::Key_Right:			emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("OC"); break;
						case Qt::Key_Left:			emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("OD"); break;
						default:
							e->ignore();
							break;
					}
				}
				else
				{
					switch( e->key() )
					{
						case Qt::Key_Home:			emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[H"); break;
						case Qt::Key_End:				emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[F"); break;
						case Qt::Key_Up:				emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[A"); break;
						case Qt::Key_Down:			emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[B"); break;
						case Qt::Key_Right:			emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[C"); break;
						case Qt::Key_Left:			emit sendAsciiChar(ASCII_ESC); emit sendAsciiString("[D"); break;
						default:
							e->ignore();
							break;
					}
				}
			break;
		}
		/** It was not a recognized special function key */
		if ( !e->isAccepted() && e->text().length() )
		{
			//unsigned int k = e->key();
			QString text = e->text();
      emit sendAsciiString(text.toLatin1().data());
			if ( localEcho() )
			{
				for ( int n=0; n < text.length(); n++ )
				{
                    char c = text.toLatin1().at(n);
					receiveChar(c);
				}
			}
			e->accept();
		}
	}
}


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

#ifndef CEMULATION_VT102_H
#define CEMULATION_VT102_H

#include "cemulation.h"
#include <QList>
#include <QRect>

/**
Escape codes for vt102 terminal.

All numbers below are octal.<n> means numeric value,<c> means character string.
If <n> is missing it is 0 or in cursor movements 1.

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

Set scrolling region (n1=upper,n2=lower)
  Esc  [ <n1> ; <n2> r
  033 133    073    162


Cursor movement (<n>=how many chars or lines), cursor stop at margin.
  Up
	Esc  [ <n> A
	033 133   101
  Down
	Esc  [ <n> B
	033 133   102
  Right
	Esc  [ <n> C
	033 133   103
  Left
	Esc  [  n  D
	033 133   104
  Cursor position  (<n1>=y,<n2>=x, from top of screen or scroll region)
	   Esc  [ <n1> ; <n2> H
	   033 133    073    110
	Or Esc  [ <n1> ; <n2> f
	   033 133    073    146
  Index (cursor down with scroll up when at margin)
	Esc  D
	033 104
  Reverse index (cursor up with scroll down when at margin)
	Esc  M
	033 115
  Next line (CR+Index)
	Esc  E
	033 105
  Save cursor and attribute
	Esc  7
	033 067
  Restore cursor and attribute
	Esc  8
	033 070


Keybad character selection
  Application keypad mode
	Esc  =
	033 075
  Numeric keypad mode
	Esc  >
	033 076

  Keypadkeys codes generated
				  Numeric      Application                VT52 Application
	0             0 (060)      Esc O p (033 117 160)      Esc ? p (033 077 160)
	1             1 (061)      Esc O q (033 117 161)      Esc ? q (033 077 161)
	2             2 (062)      Esc O r (033 117 162)      Esc ? r (033 077 162)
	3             3 (063)      Esc O s (033 117 163)      Esc ? s (033 077 163)
	4             4 (064)      Esc O t (033 117 164)      Esc ? t (033 077 164)
	5             5 (065)      Esc O u (033 117 165)      Esc ? u (033 077 165)
	6             6 (066)      Esc O v (033 117 166)      Esc ? v (033 077 166)
	7             7 (067)      Esc O w (033 117 167)      Esc ? w (033 077 167)
	8             8 (070)      Esc O x (033 117 170)      Esc ? x (033 077 170)
	9             9 (071)      Esc O y (033 117 171)      Esc ? y (033 077 171)
	- (minus)     - (055)      Esc O m (033 117 155)      Esc ? m (033 077 155)
	, (comma)     , (054)      Esc O l (033 117 154)      Esc ? l (033 077 154)
	. (period)    . (056)      Esc O n (033 117 156)      Esc ? n (033 077 156)
	Enter         CR (015)*    Esc O M (033 117 115)      Esc ? M (033 077 115)
	PF1           Esc O P      Esc O P (033 117 120)      Esc P (033 120)
	PF2           Esc O Q      Esc O Q (033 117 121)      Esc Q (033 121)
	PF3           Esc O R      Esc O R (033 117 122)      Esc R (033 122)
	PF4           Esc O S      Esc O S (033 117 123)      Esc S (033 123)
  * Or CR+LF (015 012)

  Cursorkeys codes generated (changed by set and reset modes '?1')
		  normal         application
	Up    Esc  [   A     Esc  O   A
		  033 133 101    033 117 101
	Down  Esc  [   B     Esc  O   B
		  033 133 102    033 117 102
	Right Esc  [   C     Esc  O   C
		  033 133 103    033 117 103
	Left  Esc  [   D     Esc  O   D
		  033 133 104    033 117 104


Select character set
  UK as G0
	Esc  (   A
	033 050 101
  US as G0
	Esc  (   B
	033 050 102
  Special characters and line drawing character set as G0
	Esc  (   0
	033 050 060
  Alternate ROM as G0					// Not in vt100
	Esc  (   1
	033 050 061
  Alternate ROM special characters character set as G0	// Not in vt100
	Esc  (   2
	033 050 062

  UK as G1
	Esc  )   A
	033 051 101
  US as G1
	Esc  )   B
	033 051 102
  Special characters and line drawing character set as G1
	Esc  )   0
	033 051 060
  Alternate ROM as G1					// Not in vt100
	Esc  )   1
	033 051 061
  Alternate ROM special characters character set as G1	// Not in vt100
	Esc  )   2
	033 051 062

  Selects G2 for one character				// Not in vt100
	Esc  N
	033 115
  Selects G3 for one character				// Not in vt100
	Esc  O
	033 117


Set graphic rendition
  Esc  [ <n> ; <n> m
  033 133   073   156

  Where <n> is
   0 = Turn off attributes
   1 = Bold (Full)
   2 = Half				// Not in vt100
   4 = Underline
   5 = Blink
   7 = Reverse
  21 = Normal intensity
  22 = Normal intensity
  24 = Cancel underlined
  25 = Cancel blinking
  27 = Cancel reverse

Tab stops
  Set horizontal tab
	Esc  H
	033 110
  Clear horizontal tab
	   Esc  [   g
	   033 133 147
	Or Esc  [   0   g
	   033 133 060 147
  Clear all horizontal tabs
	Esc  [   3   g
	033 133 063 147


Line attributes
  Double-height
	Top half
	  Esc  #   3
	  033 043 063
	Bottom half
	  Esc  #   4
	  033 043 064
  Single-width, single-height
	Esc  #   5
	033 043 065
  Double-width
	Esc  #   6
	033 043 066


Erasing
  Erase in line
	End of line (including cursor position)
		 Esc  [   K
		 033 133 113
	  Or Esc  [   0   K
		 033 133 060 113
	Beginning of line (including cursor position)
	  Esc  [   1   K
	  033 133 061 113
	Complete line
	  Esc  [   2   K
	  033 133 062 113
  Erase in display
	End of screen (including cursor position)
		 Esc  [   J
		 033 133 112
	  Or Esc  [   0   J
		 033 133 060 112
	Beginning of screen (including cursor position)
	  Esc  [   1   J
	  033 133 061 112
	Complete display
	  Esc  [   2   J
	  033 133 062 112


Computer editing
  Delete characters (<n> characters right from cursor
	Esc  [ <n> P
	033 133   120
  Inser line (<n> lines)
	Esc  [ <n> L
	033 133   114
  Delete line (<n> lines)
	Esc  [ <n> M
	033 133   115


Printing
  Esc  [ <c> i
  033 133    151

  Where <c> is
	  ''= Same as '0'
	 '0'= Prints screen (full or scroll region)
	 '4'= Printer controller off
	 '5'= Printer controller on (Print all received chars to printer)
	'?1'= Print cursor line
	'?4'= Auto print off
	'?5'= Auto print on (Prints line to printer when you exit from it)


Reports
  Device status
	Esc  [ <c> n
	033 133   156

  Where <c> is
	  '0'=Response Ready, no malfunctions detected
	  '3'=Malfunction, error in self-test.
	  '5'=Status report request
	  '6'=Request cursor position.
	'?10'=Response to printer status request, All ok.
	'?11'=Response to printer status request, Printer is not ready.
	'?13'=Response to printer status request, No printer.
	'?15'=Status report request from printer

  Cursor position raport (Response to request cursor position)
	Esc  [ <n1> ; <n2> R
	033 133    073    122
  Request terminal to identify itself (esc Z may not be supported in future)
	Esc  [   c
	033 133 143
	Esc  [   0   c
	033 133 060 143
	Esc  Z
	033 132
  Response to terminal identify (VT102)
	Esc  [   ?   6   c
	033 133 077 066 143


Reset to initial state
  Esc  c
  033 143


Tests
  Invoke confidence test
	Esc  [   2   ; <n> y
	033 133 062 073   171

  Where <n> is
	 '1'= Power-up test
	 '2'= Data loopback test
	 '4'= EIA loopback test
	 '9'= Power-up tests (continuously)
	'10'= Data loopback tests (continuously)
	'12'= EIA loopback tests (continuously)
	'16'= Printer loopback test
	'24'= Printer loopback tests (continuously)


Screen adjustments
  Esc  #   8
  033 043 070


Keyboard indicator
  Led L1 off
	Esc  [   0   q
	033 133 060 181
  Led L1 on
	Esc  [   1   q
	033 133 061 181



VT52 sequences
  Ansi mode
	Esc  <
	033 074
  Cursor positioning
	Up    Esc  A
		  033 101
	Down  Esc  B
		  033 102
	Right Esc  C
		  033 103
	Left  Esc  D
		  033 104
	Home  Esc  H
		  033 110
	Direct cursor address
	  Esc  Y  <line+040> <columns+040>
	  033 131
	Reverse linefeed       Esc  I
						   033 111
	Erase to end of line   Esc  K
						   033 113
	Erase to end of screen Esc  J
						   033 112
	Auto print on          Esc  ^
						   033 136
	Auto print off         Esc
						   033 137
	Printer controller on  Esc  W
						   033 127
	Printer controller off Esc  X
						   033 130
	Print cursor line      Esc  V
						   033 135
	Print screen           Esc  ]
						   033 135
	Indentify request      Esc  Z
						   033 132
	Response to indetify   Esc  /   Z
	 request (VT52)        033 057 132
	Special charset (same  Esc  F
	 as line draw in VT102 033 106
	Normal char set        Esc  G
						   033 107


Control characters
  000 = Null (fill character)
  003 = ETX (Can be selected half-duplex turnaround char)
  004 = EOT (Can be turnaround or disconnect char, if turn, then DLE-EOT=disc.)
  005 = ENQ (Transmits answerback message)
  007 = BEL (Generates bell tone)
  010 = BS  (Moves cursor left)
  011 = HT  (Moves cursor to next tab)
  012 = LF  (Linefeed or New line operation)
  013 = VT  (Processed as LF)
  014 = FF  (Processed as LF, can be selected turnaround char)
  015 = CR  (Moves cursor to left margin, can be turnaround char)
  016 = SO  (Selects G1 charset)
  017 = SI  (Selects G0 charset)
  021 = DC1 (XON, causes terminal to continue transmit)
  023 = DC3 (XOFF, causes terminal to stop transmitting)
  030 = CAN (Cancels escape sequence)
  032 = SUB (Processed as CAN)
  033 = ESC (Processed as sequence indicator)


**/

/**

The default emulation is basic ANSI. Some of these methods may be overloaded in order to impliment other emulations.


Parameters used in ANSI escape sequences

Pn
	Numeric parameter. Specifies a decimal number.

Ps
	Selective parameter. Specifies a decimal number that you use to select
	a function. You can specify more than one function by separating the
	parameters with semicolons.

PL
	Line parameter. Specifies a decimal number that represents one of the
	lines on your display or on another device.

Pc
	Column parameter. Specifies a decimal number that represents one of the
	columns on your screen or on another device.

ESC[PL;PcH
	Cursor Position: Moves the cursor to the specified position
	(coordinates). If you do not specify a position, the cursor moves to the
	home position��the upper-left corner of the screen (line 0, column
	0). This escape sequence works the same way as the following Cursor
	Position escape sequence.

ESC[PL;Pcf
	Cursor Position: Works the same way as the preceding Cursor Position
	escape sequence.

ESC[PnA
	Cursor Up: Moves the cursor up by the specified number of lines without
	changing columns. If the cursor is already on the top line, ANSI.SYS
	ignores this sequence.

ESC[PnB
	Cursor Down: Moves the cursor down by the specified number of lines
	without changing columns. If the cursor is already on the bottom line,
	ANSI.SYS ignores this sequence.

ESC[PnC
	Cursor Forward: Moves the cursor forward by the specified number of
	columns without changing lines. If the cursor is already in the
	rightmost column, ANSI.SYS ignores this sequence.

ESC[PnD
	Cursor Backward: Moves the cursor back by the specified number of
	columns without changing lines. If the cursor is already in the leftmost
	column, ANSI.SYS ignores this sequence.

ESC[s
	Save Cursor Position: Saves the current cursor position. You can move
	the cursor to the saved cursor position by using the Restore Cursor
	Position sequence.

ESC[u
	Restore Cursor Position: Returns the cursor to the position stored
	by the Save Cursor Position sequence.

ESC[J
	Erase Display: Clears the screen and moves the cursor to the home
	position (line 0, column 0).

ESC[K
	Erase Line: Clears all characters from the cursor position to the
	end of the line (including the character at the cursor position).

ESC[Ps;...;Psm
	Set Graphics Mode: Calls the graphics functions specified by the
	following values. These specified functions remain active until the next
	occurrence of this escape sequence. Graphics mode changes the colors and
	attributes of text (such as bold and underline) displayed on the
	screen.

	Text attributes
	   0    All attributes off
	   1    Bold on
	   4    Underscore on
	   5    Blink on
	   7    Reverse video on
	   8    Concealed on

	Foreground colors
	   30    Black
	   31    Red
	   32    Green
	   33    Yellow
	   34    Blue
	   35    Magenta
	   36    Cyan
	   37    White

	Background colors
	   40    Black
	   41    Red
	   42    Green
	   43    Yellow
	   44    Blue
	   45    Magenta
	   46    Cyan
	   47    White

	Parameters 30 through 47 meet the ISO 6429 standard.

**/

class CEmulationVT102 : public CEmulation
{
	Q_OBJECT
	public:

		CEmulationVT102(CScreen* screen);
		~CEmulationVT102();

		bool				applicationCursorKeys()				{return mApplicationCursorKeys;}
		bool				originMode()						{return mOriginMode;}
		inline int			topMargin()							{return mTopMargin;}
		inline int			bottomMargin()						{return mBottomMargin;}

	protected:
		virtual void		doReset();								/** reset */
		virtual void		doReport();								/** report */
		virtual void		doDeviceAttributes();					/** device attributes */
		virtual void		doCursorTo(int col, int row);			/** cursor to absolute x,y */
		virtual void		doCursorUp();							/** cursor up one row */
		virtual void		doCursorDown();							/** cursor down one row. */
		virtual void		doCursorLeft();							/** cursor left one column  */
		virtual void		doCursorRight();						/** cursor right one column  */
		virtual void		doGraphics();							/** do graphics attributes bold, blink, color, etc... */
		virtual void		doResetModes();							/** reset terminal modes */
		virtual void		doSetModes();							/** set terminal modes */
		virtual void		doSetScrollRegion();					/** set scroll region */
		virtual void		doCursorPosition();						/** set the cursor position */
		virtual void		doScrollUp();							/** scroll screen/region up */
		virtual void		doScrollDown();							/** scroll screen/region down */
		virtual void		doNewLine();							/** new line/scroll up */
		virtual void		doReverseNewLine();						/** reverse new line/scroll down */

		virtual char		doLeadIn(unsigned char ch);				/** process the lead-in sequence */

	public slots:
		virtual void		keyPressEvent(QKeyEvent* e);			/** key press input. process and transmit the char. */
		virtual void		receiveChar(unsigned char ch);			/** received and process an incoming character */

	private slots:
		void				doCodeNotHandled();

	protected slots:
		virtual void		setApplicationCursorKeys(bool b)	{mApplicationCursorKeys=b;}
		virtual void		setOriginMode(bool b)				{mOriginMode=b;}
		virtual void		setTopMargin(int top);
		virtual void		setBottomMargin(int bottom);
		virtual void		setGrid(int cols,int rows);


	signals:
		void				codeNotHandled();						/** a code was not handled */
		void				cursorOff();							/** command cursor off */
		void				cursorOn();								/** command cursor on */

	private:
		bool				attributes(QList<int>& attrs,QList<int>& extEttrs);							/** obtain the attributes from an escape string */
		void				doCSI(unsigned char ch);				/** recognise and execute a CSI sequence */
		QByteArray			mControlCode;							/** lead in sequence */
		unsigned char		mChar;									/** the last character dispatched (for debugging) */
		bool				mApplicationCursorKeys;					/** application/normal cursor keys */
		bool				mOriginMode;							/** origin scroll region(set)/screen(reset) */
		int					mTopMargin;								/** the top margin */
		int					mBottomMargin;							/** the bottom margin */
};


#endif



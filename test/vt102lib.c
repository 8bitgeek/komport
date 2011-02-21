/******************************************************************************
* VT102 Test Suite Library                                                    *
* (c) 2011 Mike Sharkey <mike@pikeaero.com>                                   *
******************************************************************************/
#include "vt102lib.h"

void csi()
{
	putchar(ASCII_ESC);
	putchar('[');
	fflush(stdout);
}

/** Set Horisontal and Vertical Position */
void csiHVP(int row,int col)
{
	csi();
	if (row==0&&col==0)
		putchar('f');
	else
		printf("%d;%df",row,col);
	fflush(stdout);
}

/** Set Cursor Position */
void csiCUP(int row,int col)
{
	csi();
	if (row==0&&col==0)
		putchar('H');
	else
		printf("%d;%df",row,col);
	fflush(stdout);
}

/** Set top and bottom margins */
void csiDECSTBM(int top,int bottom)
{
	csi();
	printf("%d;%dr",top,bottom);
	fflush(stdout);
}

/** Set/Reset origin mode */
void csiDECOM(bool b)
{
	csi();
	printf("?6%c",b?'h':'l');
	fflush(stdout);
}

/** Set/Reset auto-wrap */
void csiDECAWM(bool b)
{
	csi();
	printf("?7%c",b?'h':'l');
	fflush(stdout);
}

/** Erase In Line */
void csiEL(int mode)
{
	csi();
	printf("%dK",mode);
	fflush(stdout);
}

/** Erase In Display */
void csiED(int mode)
{
	csi();
	printf("%dJ",mode);
	fflush(stdout);
}

/** Cursor Up */
void csiCUU(int n)
{
	csi();
	printf("%dA",n);
	fflush(stdout);
}

/** CursorDown */
void csiCUD(int n)
{
	csi();
	printf("%dB",n);
	fflush(stdout);
}

/** Cursor Right */
void csiCUF(int n)
{
	csi();
	printf("%dC",n);
	fflush(stdout);
}

/** Cursor Left */
void csiCUB(int n)
{
	csi();
	printf("%dD",n);
	fflush(stdout);
}












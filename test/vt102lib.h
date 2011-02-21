#ifndef _VT102LIB
#define _VT102LIB

#include <stdio.h>
#include <unistd.h>

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

#ifndef bool
 #define bool int
 #define true 1
 #define false 0
#endif

extern void csi();								/** Lead-in */
extern void csiHVP(int row,int col);			/** Set Horisontal and Vertical Position */
extern void csiCUP(int row,int col);			/** Set Cursor Position */
extern void csiDECSTBM(int top,int bottom);		/** Set top and bottom margins */
extern void csiDECOM(bool b);					/** Set/Reset origin mode */
extern void csiDECAWM(bool b);					/** Set/Reset auto-wrap */
extern void csiEL(int mode);					/** Erase In Line */
extern void csiED(int mode);					/** Erase In Display */
extern void csiCUU(int n);						/** Cursor Up */
extern void csiCUD(int n);						/** CursorDown */
extern void csiCUF(int n);						/** Cursor Right */
extern void csiCUB(int n);						/** Cursor Left */
#endif

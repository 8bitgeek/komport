#include <stdio.h>

#include "vt102lib.h"

/** clear screen test */
void clear()
{
	csiDECOM(false);		/* origin mode off*/
	csiED(2);				/* erase display */
	csiHVP(1,1);			/* home cursor */
	csiDECSTBM(1,25);		/* set top and bottom margins */
}

/** fill test */
void fill(char* name)
{
	int x,y;
	csiDECAWM(false);		/* turn off auto-wrap line */
	for(y=1;y<=25;y++)
	{
		for(x=1;x<=80;x++)
		{
			csiHVP(y,x);
			putchar('A'+y);
			fflush(stdout);
		}
	}
	csiHVP(1,1);
	printf("%s",name);
	fflush(stdout);
	printf(" ");
	fflush(stdout);
	csiHVP(1,1);
	csiDECOM(true);			/* origin mode on */
	usleep(1000*3000);
}

/** scroll region test */
void scrollareadown()
{
	int cycle;
	clear();
	fill("SCROLL-AREA TEST #1");
	csiDECSTBM(10,15);		/* set top and bottom margins */
	csiDECOM(true);			/* origin mode on */
	csiHVP(0,0);			/* home cursor */
	csiDECAWM(true);		/* turn on auto-wrap line */
	/* scroll the scroll region... */
	for(cycle=0;cycle<10;cycle++)
	{
		char n;
		for(n=' '; n < '~'; n++)
		{
			putchar(n);
			fflush(stdout);
			usleep(1000*15);
		}
	}
}

/** erase line test */
void eraselines()
{
	int cycles;
	for(cycles=0;cycles<1;cycles++)
	{
		int x,y;
		clear();
		fill("ERASE-LINE TEST #1");
		for(y=1,x=1+cycles;y<=25;y++)
		{
			csiHVP(y,x);
			csiEL(0);
			usleep(1000*200);
			x++;
		}
		clear();
		fill("ERASE-LINE TEST #2");
		for(y=1,x=1+cycles;y<=25;y++)
		{
			csiHVP(y,x);
			csiEL(1);
			usleep(1000*200);
			x++;
		}
		clear();
		fill("ERASE-LINE TEST #3");
		for(y=1,x=1+cycles;y<=25;y++)
		{
			csiHVP(y,x);
			csiEL(2);
			usleep(1000*200);
			x++;
		}
		clear();
		fill("ERASE-LINE TEST #4");
		for(y=1,x=80-cycles;y<=25;y++)
		{
			csiHVP(y,x);
			csiEL(0);
			usleep(1000*200);
			x--;
		}
		clear();
		fill("ERASE-LINE TEST #5");
		for(y=1,x=80-cycles;y<=25;y++)
		{
			csiHVP(y,x);
			csiEL(1);
			usleep(1000*200);
			x--;
		}
		clear();
		fill("ERASE-LINE TEST #5");
		for(y=1,x=80-cycles;y<=25;y++)
		{
			csiHVP(y,x);
			csiEL(2);
			usleep(1000*200);
			x--;
		}
	}
}

/** erase display test */
void erasedisplay()
{
	int cycles;
	for(cycles=0;cycles<1;cycles++)
	{
		int x,y;
		clear();
		for(y=1,x=1+cycles;y<=25;y+=5)
		{
			fill("ERASE-DISPLAY TEST #1");
			csiHVP(y,x);
			csiED(0);
			usleep(1000*1000);
			x++;
		}
		clear();
		for(y=1,x=1+cycles;y<=25;y+=5)
		{
			fill("ERASE-DISPLAY TEST #2");
			csiHVP(y,x);
			csiED(1);
			usleep(1000*1000);
			x++;
		}
		clear();
		for(y=1,x=1+cycles;y<=25;y+=5)
		{
			fill("ERASE-DISPLAY TEST #3");
			csiHVP(y,x);
			csiED(2);
			usleep(1000*1000);
			x++;
		}
	}
}

int main(int argc,char*argv[])
{
	while (true)
	{
		erasedisplay();
		eraselines();
		scrollareadown();
	}
}
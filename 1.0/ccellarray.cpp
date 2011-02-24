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

#include "ccellarray.h"
#include "ccharcell.h"
#include "cscreen.h"

#define inherited QObject

CCellArray::CCellArray()
: mScreen(NULL)
, mCols(0)
, mRows(0)
, mSyncBusy(false)
{
}

CCellArray::~CCellArray()
{
}

/**
 * Set the visual drawable object to which character cells will draw themselves.
 * @param drawable A pointer to a QPaintDevice
 */
void CCellArray::setScreen(CScreen* screen)
{
	mScreen = screen;
	for( int n=0; n < mCells.count(); n++ )
	{
		CCellArray& cell = (CCellArray&)mCells.at(n);
		cell.setScreen(mScreen);
	}
}

/**
 * Set the visual drawable rectangle.
 * @param r The rectangle to draw cells on the drawable object.
 */
void CCellArray::setRect(QRect r)
{
	if ( r.width() >  0 && r.height() > 0 )
	{
		mRect = r;
		if ( rows() > 0 && cols() > 0 )
		{
			int cellHeight = r.height()/rows();
			int cellWidth = r.width()/cols();
			for( int row=0; row < rows(); row++ )
			{
				for( int col=0; col < cols(); col++ )
				{
					int i = indexOf(col,row);
					QRect cellRect((col*cellWidth)+r.left(),(row*cellHeight)+r.top(),cellWidth,cellHeight);
					CCharCell& cell = (CCharCell&)mCells.at(i);
					cell.setRect(cellRect);
				}
			}
		}
	}
}

/**
 * Set the number of columns in the array.
 * @param cols The number of columns.
  */
void CCellArray::setCols(int cols)
{
	mCols=cols;
	sync();
	setRect(mRect); /* force re-calculate sizes */
}

/**
 * Set the number of rows in the array.
 * @param rows The number of rows
 */
void CCellArray::setRows(int rows)
{
	mRows=rows;
	sync();
	setRect(mRect); /* force re-calculate sizes */
}

/**
 * @param Synchronize the size of the character array with the number of rows and columns.
 */
void CCellArray::sync()
{
	if ( !mSyncBusy )
	{
		int nCells = rows()*cols();
		if ( nCells > 0 )
		{
			int diff = nCells - mCells.count();
			mSyncBusy=true;
			while (diff!=0)
			{
				if ( diff > 0 )
				{
					CCharCell cell(this);
					mCells.append(cell);
					--diff;
				}
				else
				{
					mCells.takeLast();
					++diff;
				}
			}
		}
		mSyncBusy=false;
	}
	setRect(mRect); /* recalc cell rects */
	screen()->update();
}

/**
 * @brief Draw the cells.
 * @param rect the paint rect
 */
void CCellArray::draw(QPainter& painter, const QRect& rect)
{
	for(int n=0; n < cells().count(); n++)
	{
		CCharCell& cell = (CCharCell&)cells().at(n);
		if ( cell.rect().intersects(rect))
		{
			cell.draw(painter);
		}
	}
}

/**
 * @brief Draw the cells.
 * @param rect the paint rect
 */
void CCellArray::draw(const QRect& rect)
{
	for(int n=0; n < cells().count(); n++)
	{
		CCharCell& cell = (CCharCell&)cells().at(n);
		if ( cell.rect().intersects(rect))
		{
			cell.draw();
		}
	}
}

/**
  * @brief Scroll a region.
  * @param mode The scroll mode.
  * @param left The left column of the scroll region.
  * @param top The top row of the scroll region.
  * @param width The width of the scroll region.
  * @param height The height of the scroll region.
  */
void CCellArray::scrollGrid(CCellArray::ScrollMode mode, int col, int row, int width, int height)
{
	if ( mode == ScrollUp )
	{
		/** copy region up... */
		for(int y=row; y < (row+height); y++)
		{
			for(int x=col; x < width; x++)
			{
				if ( isValidCell(x,y+1) && isValidCell(x,y) )
				{
					CCharCell& from = (CCharCell&)cell(x,y+1);
					CCharCell& to = (CCharCell&)cell(x,y);
					to = from;
				}
			}
		}
		/** new up the bottom row... */
		for(int x=col; x < width; x++)
		{
			CCharCell& c = (CCharCell&)cell(x,(row+height)-1);
			c.clear();
		}
	}
	else if ( mode == ScrollDown )
	{
		/** copy region down... */
		for(int y=(row+height)-1; y>row; y--)
		{
			for(int x=col; x < width; x++)
			{
				if ( isValidCell(x,y-1) && isValidCell(x,y) )
				{
					CCharCell& from = (CCharCell&)cell(x,y-1);
					CCharCell& to = (CCharCell&)cell(x,y);
					to = from;
				}
			}
		}
		/** new up the top row... */
		for(int x=col; x < width; x++)
		{
			CCharCell& c = (CCharCell&)cell(x,row);
			c.clear();
		}
	}
	sync();
}

/* Select cells in screen pixel coordinates rectangle */
void CCellArray::selectCells(QRect r)
{
	for( int y=0; y < rows(); y++ )
	{
		for( int x=0; x < cols(); x++ )
		{
			CCharCell& c = (CCharCell&)cell(x,y);
			if ( r.intersects(c.rect()) )
			{
				c.setSelect(true);
			}
			else
			{
				c.setSelect(false);
			}
			screen()->update(c.rect());
		}
	}
}

/* De-select all previously selected cells. */
void CCellArray::deselectCells()
{
	for( int y=0; y < rows(); y++ )
	{
		for( int x=0; x < cols(); x++ )
		{
			CCharCell& c = (CCharCell&)cell(x,y);
			if ( c.select() )
			{
				c.setSelect(false);
			}
		}
	}
	screen()->update();
}



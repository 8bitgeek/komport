/**************************************************************************
*   Author <mike@8bitgeek.net> Mike Sharkey                               *
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

#ifndef CCELLARRAY_H
#define CCELLARRAY_H

#include "ccell.h"

#include <QObject>
#include <QWidget>

#define CCells	QList<CCell>

class CScreen;
class CCellArray : public QObject
{
	Q_OBJECT
	public:

		typedef enum
		{
			ScrollUp,
			ScrollDown
		} ScrollMode;

		CCellArray();
		virtual ~CCellArray();

        inline CScreen*	screen()                            {return mScreen;}
		inline QRect&		rect()							{return mRect;}
		inline int			cols()							{return mCols;}
		inline int			rows()							{return mRows;}
		inline CCells		cells()							{return mCells;}
		inline const CCell& cell(int col,int row)			{return mCells.at(indexOf(col,row));}
		inline int			indexOf(int col,int row)		{return (row*cols())+col;}
		inline bool			isValidCell(int col,int row)	{return indexOf(col,row) < count();}
		inline int			count()							{return mCells.count();}
		void				selectCells(QRect r);
		void				deselectCells();

	public slots:
		void				setScreen(CScreen* screen);
		void				setRect(QRect r);
		void				setGrid(int cols,int rows);
		void				setCols(int cols);
		void				setRows(int rows);
		void				draw(QPainter& painter, const QRect& rect);
		void				draw(const QRect& rect);
		void				scrollGrid(CCellArray::ScrollMode mode, int x, int y, int width, int height);
		void				sync();

	protected slots:
		void				appendScrolled(CCell cell);	/* Append a cell to the scroll buffer */
		void				resetScrolled();			/* Reset the scroll buffer */
		void				trimScrolled();				/* Trim the scroll buffer */

	private:
		CScreen*			mScreen;					/* The screen associated with this cell array */
		QRect				mRect;
		int					mCols;						/* Number of Columns */
		int					mRows;						/* Number of Rows */
		CCells				mCells;						/* The screen cells */
		CCells				mScrollBuffer;				/* The scroll buffer */
		int					mScrollLimit;				/* The scroll back limit */
		bool				mSyncBusy;					/* Sychronizing is busy. */
};

#endif // CCELLARRAY_H

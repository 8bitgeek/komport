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

#ifndef CCELLARRAY_H
#define CCELLARRAY_H

#include "ccharcell.h"

#include <QObject>
#include <QWidget>

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

		CScreen*			screen()					{return mScreen;}
		QRect				rect()						{return mRect;}
		int					cols()						{return mCols;}
		int					rows()						{return mRows;}
		QList<CCharCell>	cells()						{return mCells;}
		const CCharCell&	cell(int col,int row);
		int					indexOf(int col,int row);
		int					count()						{return mCells.count();}
		void				selectCells(QRect r);
		void				deselectCells();

	public slots:
		void				setScreen(CScreen* screen);
		void				setRect(QRect r);
		void				setGrid(int cols,int rows)	{ setCols(cols); setRows(rows); }
		void				setCols(int cols);
		void				setRows(int rows);
		void				draw(QPainter& painter, const QRect& rect);
		void				draw(const QRect& rect);
		void				scrollGrid(CCellArray::ScrollMode mode, int x, int y, int width, int height);
		void				sync();

	private:
		CScreen*			mScreen;
		QRect				mRect;
		int					mCols;
		int					mRows;
		QList<CCharCell>	mCells;
		bool				mSyncBusy;
};

#endif // CCELLARRAY_H

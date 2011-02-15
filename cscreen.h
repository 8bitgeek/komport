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
#ifndef CSCREEN_H
#define CSCREEN_H

#include <QWidget>
#include <QRect>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QKeyEvent>
#include <QPoint>
#include <QColor>
#include <QMouseEvent>

#include "ccellarray.h"

class CScreen : public QWidget
{
	Q_OBJECT
	public:
		CScreen(QWidget *parent = 0);
		virtual ~CScreen();

		CCellArray&		cells() {return mCells;}
		CCharCell&		cell(int col,int row) {return (CCharCell&)cells().cell(col,row);}
		CCharCell&		cell(QPoint pt) {return cell(pt.x(),pt.y());}

		QPoint			cursorPos() {return mCursor;}

		int				cols() {return cells().cols();}
		int				rows() {return cells().rows();}

		QColor			defaultForegroundColor()					{return mDefaultForegroundColor;}
		QColor			defaultBackgroundColor()					{return mDefaultBackgroundColor;}
		QColor			foregroundColor();
		QColor			backgroundColor();

		QString			selectedText();

	public slots:

		void			setDefaultBackgroundColor(QColor defaultBackgroundColor);
		void			setDefaultForegroundColor(QColor defaultForegroundColor);
		void			setBackgroundColor(QColor backgroundColor);
		void			setForegroundColor(QColor foregroundColor);

		void			setBlink(bool b)							{mBlink=b;}
		void			setBold(bool b)								{mBold=b;}
		void			setReverse(bool b)							{mReverse=b;}
		void			setUnderline(bool b)						{mUnderline=b;}

		void			setGrid(int cols,int rows) {setCols(cols); setRows(rows);}
		void			setCols(int cols)	{cells().setCols(cols);}
		void			setRows(int rows)	{cells().setRows(rows);}
		void			setCursorPos(QPoint& pt);
		void			setCursorPos(int col,int row);
		void			scrollUp();

		void			clear();
		void			clearEOL();
		void			clearBOL();
		void			clearEOD();
		void			clearBOD();

		void			delChars(int num);
		void			insLines(int num);

		void			putchar(char c,int x=-1,int y=-1);
		void			putchar(char c,QPoint pt) {putchar(c,pt.x(),pt.y());}

		void			advanceCursor();

	protected:
		void			resizeEvent(QResizeEvent* e);
		void			paintEvent(QPaintEvent* e);
		void			mousePressEvent(QMouseEvent *e);
		void			mouseMoveEvent(QMouseEvent *e);
		void			mouseReleaseEvent(QMouseEvent *e);

	private:
		CCellArray		mCells;
		QPoint			mCursor;
		QColor			mDefaultBackgroundColor;
		QColor			mDefaultForegroundColor;
		QColor			mBackgroundColor;
		QColor			mForegroundColor;
		bool			mBlink;
		bool			mBold;
		bool			mReverse;
		bool			mUnderline;
		QPoint			mSelectPt1;
		QPoint			mSelectPt2;
};

#endif // CSCREEN_H

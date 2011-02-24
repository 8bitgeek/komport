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

		CCellArray&		cells()										{return mCells;}
		inline CCharCell& cell(int col,int row)						{return (CCharCell&)cells().cell(col,row);}
		inline CCharCell& cell(QPoint pt)							{return cell(pt.x(),pt.y());}

		inline QPoint&	cursorPos()									{return mCursor;}

		inline int		cols()										{return cells().cols();}
		inline int		rows()										{return cells().rows();}

		inline QColor&	defaultForegroundColor()					{return mDefaultForegroundColor;}
		inline QColor&	defaultBackgroundColor()					{return mDefaultBackgroundColor;}
		inline QColor&	foregroundColor()							{return mForegroundColor;}
		inline QColor&	backgroundColor()							{return mBackgroundColor;}

		inline bool		blink()										{return mBlink;}
		inline bool		bold()										{return mBold;}
		inline bool		reverse()									{return mReverse;}
		inline bool		underline()									{return mUnderline;}

		QString			selectedText();

	public slots:

		void			setDefaultBackgroundColor(QColor defaultBackgroundColor);
		void			setDefaultForegroundColor(QColor defaultForegroundColor);
		void			setBackgroundColor(QColor backgroundColor);
		void			setForegroundColor(QColor foregroundColor);

		inline void		setBlink(bool b)							{mBlink=b;}
		inline void		setBold(bool b)								{mBold=b;}
		inline void		setReverse(bool b)							{mReverse=b;}
		inline void		setUnderline(bool b)						{mUnderline=b;}

		inline void		setGrid(int cols,int rows)					{setCols(cols); setRows(rows);}
		inline void		setCols(int cols)							{cells().setCols(cols);}
		inline void		setRows(int rows)							{cells().setRows(rows);}
		void			setCursorPos(QPoint& pt);
		void			setCursorPos(int col,int row);
		void			scrollUp();
		void			scrollDown();

		void			clear();
		void			clearEOL();
		void			clearBOL();
		void			clearEOD();
		void			clearBOD();

		void			delChars(int num);
		void			insLines(int num);

		void			putchar(char c,int x=-1,int y=-1);
		inline void		putchar(char c,QPoint pt)					{putchar(c,pt.x(),pt.y());}

		bool			advanceCursor();

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

/**************************************************************************
*   Author <mike@8bitgeek.net> Mike Sharkey                               *
*   Copyright (C) 2011 by Pike Aerospace Research Corporation             *
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
#include "cled.h"

#include <QPainter>
#include <QEventLoop>

#define inherited QWidget

CLed::CLed(QWidget *parent)
: inherited(parent)
, mState(false)
{
	setMinimumWidth(8);
	setMinimumHeight(8);
}

CLed::~CLed()
{
}

void CLed::on(bool flush)
{
	mState = true;
	if (flush)
		_flush();
	else
		update();
}

void CLed::off(bool flush)
{
	mState = false;
	if (flush)
		_flush();
	else
		update();
}

void CLed::_flush()
{
	QEventLoop loop;
	repaint();
	loop.processEvents();
}

void CLed::paintEvent(QPaintEvent* e)
{
	QPainter painter(this);
	QPixmap pixmap(mState ? ":/images/ledgreen.png" : ":/images/ledoff.png");
	pixmap = pixmap.scaled(size(),Qt::KeepAspectRatio);
	painter.drawPixmap(0,0,pixmap.width(),pixmap.height(),pixmap);
}

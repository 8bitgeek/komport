/**************************************************************************
*   Author <mike@pikeaero.com> Mike Sharkey                               *
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
#ifndef CLED_H
#define CLED_H

#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>

class CLed : public QWidget
{
    Q_OBJECT
	public:
		CLed(QWidget *parent = 0);
		virtual ~CLed();

	public slots:
		void			on(bool flush=false);
		void			off(bool flush=false);

	protected:
		bool			mState;
		void			_flush();
		virtual	void	paintEvent(QPaintEvent* e);

};

#endif // CLED_H

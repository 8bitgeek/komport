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
#ifndef CFILETRANSFER_H
#define CFILETRANSFER_H

#include <QObject>
#include <QString>

class CFileTransfer : public QObject
{
	Q_OBJECT
	public:

		CFileTransfer(QObject *parent = 0);
		virtual ~CFileTransfer();

	public slots:
		virtual void			setFileName(QString fileName);
		virtual void			setDownloadPath(QString downloadPath);
		virtual void			setUploadPath(QString uploadPath);

	signals:

	private:
		QString					mFileName;
		QString					mDownloadPath;
		QString					mUploadPath;
};

#endif // CFILETRANSFER_H

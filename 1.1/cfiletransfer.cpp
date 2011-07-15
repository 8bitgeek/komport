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
#include "cfiletransfer.h"

CFileTransfer::CFileTransfer(QObject *parent) :
    QObject(parent)
{
}

CFileTransfer::~CFileTransfer()
{
}

QString CFileTransfer::fileName()
{
	return mFileName;
}

QString CFileTransfer::downloadPath()
{
	return mDownloadPath;
}

QString CFileTransfer::uploadPath()
{
	return mUploadPath;
}

QString CFileTransfer::command()
{
	return mCommand;
}

bool CFileTransfer::needsDialog()
{
	return mNeedsDialog;
}

void CFileTransfer::setFileName(QString fileName)
{
	mFileName = fileName;
}

void CFileTransfer::setDownloadPath(QString downloadPath)
{
	mDownloadPath = downloadPath;
}

void CFileTransfer::setUploadPath(QString uploadPath)
{
	mUploadPath = uploadPath;
}

void CFileTransfer::setCommand(QString command)
{
	mCommand = command;
}

void CFileTransfer::setNeedsDialog(bool needsDialog)
{
	mNeedsDialog=needsDialog;
}


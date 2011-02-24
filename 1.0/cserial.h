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
#ifndef CSERIAL_H
#define CSERIAL_H

#include <QObject>
#include <QByteArray>
#include <QSocketNotifier>

#ifdef Q_OS_UNIX
	#include <termios.h>
	#include <unistd.h>
#endif
#ifdef Q_OS_WIN32
	#include "Win32Serial.h"
	#include <QTimerEvent>
#endif

#include "cdevicelock.h"

/**
 * @brief Implements a serial data class. Currently is intened to implement RS232 style device interface
 * @brief In time though class augt to be used as the generic base class / interface for general serial devices
 * @brief and the RS232 type devices aught to be supported in a class like STSerialRS232 or some such.
 * @author Mike Sharkey <mike@pikeaero.com>
 */
class CSerial : public QObject
{
	Q_OBJECT
	public:
		CSerial(const QString &name);
		virtual ~CSerial();

		QString				name()			{return mName;}
	#ifdef Q_OS_WIN32
		HANDLE				handle()		{return mWin32Serial->handle();}
	#else
		int					handle()		{return mHandle;}
	#endif
		bool				open();
		void				close();
		bool				isOpen();
		void				setLineControl(int ispeed=2400, int dataBits=8, int stopBits=1, QString parity="NONE", QString flow="NONE" );
		int					write(const void* buf, int count);
		bool				getChar(char* ch, int msec=100);
		bool				emitChars() {return mEmitChars;}

	public slots:
		void				setEmitChars(bool b) {mEmitChars=b;}
		void				sendAsciiChar(const char c);
		void				sendAsciiString(const char* s);

	signals:
		void				statusMessage( void* sender, int level, QString msg);
		void				readyRead();
		void				rx(unsigned char c);

	private slots:
		void				readActivated(int handle);
		void				readTimeout();

	#ifdef Q_OS_WIN32
	protected:
		void				windowsEmitLastError();
		void				timerEvent(QTimerEvent* e);
	#endif

	private:
		QString				mName;
	#ifdef Q_OS_WIN32
		int					mTimer;
		CWin32Serial*		mWin32Serial;
	#else
		int					mHandle;
	#endif
		QSocketNotifier*	mSocketNotifier;
		bool				mReadTimeout;
		bool				mInGetChar;
		CDeviceLock         mDeviceLock;
		bool				mEmitChars;
};

#endif

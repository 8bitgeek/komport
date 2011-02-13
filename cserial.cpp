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
#include "cserial.h"
#include <fcntl.h>

#include <QTimer>
#include <QEventLoop>
#include <QFile>

#define inherited QObject

/** ***************************************************************************
* @brief Constructor
******************************************************************************/
CSerial::CSerial(const QString& name)
: inherited()
, mName(name)
#ifndef Q_OS_WIN32
, mHandle(-1)
#endif
, mSocketNotifier(NULL)
, mReadTimeout(false)
, mInGetChar(false)
, mDeviceLock(name)
, mEmitChars(true)
{
#ifdef Q_OS_WIN32
	mWin32Serial = new CWin32Serial();
	mTimer = startTimer(1000);
#endif
}

/** ***************************************************************************
* @brief Destructor
******************************************************************************/
CSerial::~CSerial()
{
	close();
	#ifdef Q_OS_WIN32
		delete mWin32Serial;
	#endif
	}

/** ***************************************************************************
* @brief Is the device open?
* @return true if device is open.
******************************************************************************/
bool CSerial::isOpen()
{
#ifdef Q_OS_WIN32
	return mWin32Serial->isOpen();
#else
	return handle() < 0 ? false : true;
#endif
}

/** ***************************************************************************
* @brief Open the serial device for communication.
* @return true on success, else false.
******************************************************************************/
bool CSerial::open()
{
	if (!mDeviceLock.tryLock())
	{
	#ifdef Q_OS_WIN32
		std::wstring str = name().toStdWString();
		if ( mWin32Serial->Open(str.data()) )
		{
			mDeviceLock.lock();
			setLineControl();
			return true;
		}
		return false;
	#else
		mHandle = ::open( name().toAscii().data(), O_RDWR | O_NOCTTY | O_NDELAY );
		if ( mHandle >= 0 )
		{
			mSocketNotifier = new QSocketNotifier(mHandle,QSocketNotifier::Read);
			QObject::connect(mSocketNotifier,SIGNAL(activated(int)),this,SLOT(readActivated(int)));
		}
		if ( mHandle >= 0 )
		{
			mDeviceLock.lock();
			setLineControl();
			return true;
		}
		return false;
	#endif
	}
	else
	{
		return false;
	}
}

/** ***************************************************************************
* @brief Close the serial device.
******************************************************************************/
void CSerial::close()
{
	if ( mSocketNotifier != NULL )
	{
		delete mSocketNotifier;
		mSocketNotifier = NULL;
	}
#ifdef Q_OS_WIN32
	mWin32Serial->Close();
	mDeviceLock.unlock();
#else
	if ( isOpen() )
	{
		::close( mHandle );
		mDeviceLock.unlock();
	}
	mHandle=(-1);
#endif
}

/** ***************************************************************************
* @brief receive this singal the data is available for reading.
******************************************************************************/
void CSerial::readActivated(int handle)
{
	if ( handle >=0 )
	{
		emit readyRead();
		if ( emitChars() )
		{
			char c;
			while ( getChar(&c) )
			{
				emit rx(c);
			}
		}
	}
}

/** ***************************************************************************
* @brief write bytes to the serial device.
* @param buf The bytes to write.
* @param count The number of bytes to write.
* @return Number of bytes written.
******************************************************************************/
int CSerial::write(const void* buf, int count)
{
#ifdef Q_OS_WIN32
	return mWin32Serial->SendData((const char*)buf,count);
#else
	return ::write( mHandle, buf, count);
#endif
}

/** ***************************************************************************
* @brief write an ascii character to output.
* @param c The byte to write.
******************************************************************************/
void CSerial::sendAsciiChar(const char c)
{
	if ( isOpen() )
	{
		write(&c,1);
	}
}

/** ***************************************************************************
* @brief write an ascii string to output.
* @param c The string to write.
******************************************************************************/
void CSerial::sendAsciiString(const char* s)
{
	if ( isOpen() )
	{
		write(s,::strlen(s));
	}
}

/** ***************************************************************************
* @brief Get a character from the serial device.
* @param ch A pointer to the returned char.
* @param msec number of milliseconds to wait bfore timing out.
* @return true of a character was read, else false.
******************************************************************************/
bool CSerial::getChar(char* ch,int msec)
{
	if ( !mInGetChar )
	{
		mInGetChar=true;
		int n;
		QEventLoop eventLoop;
		QTimer *timer = new QTimer(this);
		QObject::connect(timer, SIGNAL(timeout()), this, SLOT(readTimeout()));
		mReadTimeout=false;
		timer->start(msec);
	#ifdef Q_OS_WIN32
		while ( (n=mWin32Serial->ReadData(ch,1)) != 1 && !mReadTimeout )
		{
			eventLoop.processEvents();
		}
	#else
		while ( (n=read( mHandle, ch, 1)) != 1 && !mReadTimeout )
		{
			eventLoop.processEvents();
		}
	#endif
		delete timer;
		mInGetChar=false;
		return ( n == 1 ) ? true : false;
	}
	return false;
}

/** ***************************************************************************
* @brief This slot accepts the read timeout signal, and sets a flag
* @brief indiating a timeout has occured.
******************************************************************************/
void CSerial::readTimeout()
{
	mReadTimeout=true;
}

/** ***************************************************************************
* @brief Initialize the line control.
* @param speed Baud rate expressed as 0..230400.
* @param dataBits The number of data bits per word expressed as 5..8 as defined by termios.
* @param stopBits The number of stop bits 1..2
* @param parity Either "EVEN", "ODD", or "NONE",
* @param flow Either "XON/XOFF", "RTS/CTS", or "NONE"
******************************************************************************/
void CSerial::setLineControl(int ispeed, int dataBits, int stopBits, QString parity, QString flow )
{
#ifdef Q_OS_WIN32
	DCB dcbSerialParams = {0};
	dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
	if (::GetCommState(handle(), &dcbSerialParams))
	{
		dcbSerialParams.ByteSize=dataBits;
		switch( ispeed )
		{
		case 300: dcbSerialParams.BaudRate=CBR_300; break;
		case 1200: dcbSerialParams.BaudRate=CBR_1200; break;
		default:
		case 2400: dcbSerialParams.BaudRate=CBR_2400; break;
		case 4800: dcbSerialParams.BaudRate=CBR_4800; break;
		case 9600: dcbSerialParams.BaudRate=CBR_9600; break;
		case 19200: dcbSerialParams.BaudRate=CBR_19200; break;
		case 38400: dcbSerialParams.BaudRate=CBR_38400; break;
		case 57600: dcbSerialParams.BaudRate=CBR_57600; break;
		}
		switch( stopBits )
		{
		default:
		case 1: dcbSerialParams.StopBits=ONESTOPBIT;
		case 2: dcbSerialParams.StopBits=TWOSTOPBITS;
		}
		if ( parity == "EVEN" )
		{
			dcbSerialParams.Parity=EVENPARITY;
		}
		else if ( parity == "ODD" )
		{
			dcbSerialParams.Parity=ODDPARITY;
		}
		else if ( parity == "NONE" )
		{
			dcbSerialParams.Parity=NOPARITY;
		}

		if ( ::SetCommState(handle(),&dcbSerialParams) )
		{
			::EscapeCommFunction(handle(),SETDTR);
			::EscapeCommFunction(handle(),SETRTS);
		}
		else
		{
			windowsEmitLastError();
		}
	}
	else
	{
		windowsEmitLastError();
	}
#else
	int rc=0;
	speed_t speed;
	struct termios tc;
	rc = tcgetattr( handle(), &tc );
	if ( rc == 0 )
	{
		// speed...
		switch ( ispeed )
		{
		case 300: speed = B300; break;
		case 1200: speed = B1200; break;
		default:
		case 2400: speed = B2400; break;
		case 4800: speed = B4800; break;
		case 9600: speed = B9600; break;
		case 19200: speed = B19200; break;
		case 38400: speed = B38400; break;
		case 57600: speed = B57600; break;
		case 115200: speed = B115200; break;
		case 230400: speed = B230400; break;
		}
		cfsetispeed( &tc, speed );
		cfsetospeed( &tc, speed );
		// line control...
		tc.c_lflag &= ~ECHO;
		tc.c_lflag &= ~ICANON;
		// input control...
		tc.c_iflag &= ~ICRNL;
		tc.c_iflag &= ~INLCR;
		tc.c_iflag |= IGNBRK;
		// ouput control...
		tc.c_oflag &= ~ONLCR;
		tc.c_oflag &= ~OCRNL;
		// parity...
		if ( parity == "NONE" )
		{
			tc.c_iflag |= IGNPAR;
			tc.c_cflag &= ~INPCK;
		}
		else
		{
			tc.c_cflag |= PARENB;		// enable generation and checking on input/output (even parity default).
			if ( parity == "ODD" )		// odd parity?
			{
				tc.c_cflag |= PARODD;
			}
			else
			{
				tc.c_cflag &= ~PARODD;
			}
			tc.c_iflag |= INPCK;
		}
		// character size...
		tc.c_cflag &= ~CSIZE; // clear current character size
		switch ( dataBits )
		{
		case 5:		tc.c_cflag |= CS5; break;
		case 6:		tc.c_cflag |= CS6; break;
		case 7:		tc.c_cflag |= CS7; break;
		case 8:		tc.c_cflag |= CS8; break;
		default:	tc.c_cflag |= CS8; break;
		}
		// stop bits...
		if ( stopBits == 1 )
			tc.c_cflag &= ~CSTOPB; // 1
		else
			tc.c_cflag |= CSTOPB; // 1.5 or 2
		// flow control...
		if ( flow == "XON/XOFF" )
		{
			tc.c_cflag &= ~CRTSCTS;
			tc.c_iflag |= IXON;
			tc.c_iflag |= IXOFF;
		}
		else
		if ( flow == "RTS/CTS" )
		{
			tc.c_iflag &= ~IXON;
			tc.c_iflag &= ~IXOFF;
			tc.c_cflag |= CRTSCTS;
		}
		else
		{   // none
			tc.c_cflag &= ~CRTSCTS;
			tc.c_iflag &= ~IXON;
			tc.c_iflag &= ~IXOFF;
		}
		// enable the new settings...
		rc = tcsetattr( handle(), TCSANOW,  &tc );
	}
#endif
}

/** ***************************************************************************
* @brief
******************************************************************************/
#ifdef Q_OS_WIN32
void CSerial::windowsEmitLastError()
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		0, // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL
	);
	// Process any inserts in lpMsgBuf.
	// ...
	// Display the string.
	//MessageBox( NULL, (LPCTSTR)lpMsgBuf, L"Error", MB_OK | MB_ICONINFORMATION );
	emit statusMessage( this, 1, QString::fromWCharArray((LPTSTR)lpMsgBuf ) );
	// Free the buffer.
	LocalFree( lpMsgBuf );
}
#endif

/** ***************************************************************************
* @brief Handle a timer event.
******************************************************************************/
#ifdef Q_OS_WIN32
void CSerial::timerEvent(QTimerEvent* e)
{
	if ( mTimer == e->timerId() )
	{
		if ( mWin32Serial->ReadDataWaiting() )
		{
			emit readyRead();
			if ( emitChars() )
			{
				char c;
				while ( getChar(&c) )
				{
					emit rx(c);
				}
			}
		}
	}
}
#endif



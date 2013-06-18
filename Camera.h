/*
    This file is part of The Kromophone.
 
	The Kromophone is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The Kromophone is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Kromophone.  If not, see <http://www.gnu.org/licenses/>.
	
*/
#ifndef CAMERA_H
#define CAMERA_H

//#ifndef _WIN32
#include <QObject>
#include <QString>
#include "ColorSource.h"

class Camera : public ColorSource
{
	Q_OBJECT
public:
	explicit Camera(QObject *parent = 0);
	
	typedef enum {
		IO_METHOD_READ,
		IO_METHOD_MMAP,
		IO_METHOD_USERPTR,
	} io_method;
	
	//! Todo: Implement this
    const Color color() const { return Color(); };
signals:
	
public slots:
	
private:
	int xioctl (int fd, int request, void * arg);
	
	int width;
	int height;
	int fd;
	static io_method io;
	QString device;
};

//#endif // _132

#endif // CAMERA_H

#ifndef CAMERA_H
#define CAMERA_H

#ifndef _WIN32
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

#endif // _132

#endif // CAMERA_H

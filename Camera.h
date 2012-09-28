#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QString>

class Camera : public QObject
{
	Q_OBJECT
public:
	explicit Camera(QObject *parent = 0);
	
	typedef enum {
		IO_METHOD_READ,
		IO_METHOD_MMAP,
		IO_METHOD_USERPTR,
	} io_method;
	
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

#endif // CAMERA_H

#include "V4L2ImageSource.h"
#include "v4lcamera_raw.h"
#include "Settings.h"
#include <QDebug>
#include <QTimer>

extern "C" void process_image(void* data);

void yuvtorgb_pixel(unsigned int y, unsigned int u, unsigned int v, unsigned char* r, unsigned char* g, unsigned char* b) {
	int tmp;
	tmp = (298*(y-16) + 409*(v-128) + 128) >> 8;
	if (tmp >255)
		tmp=255;
	if (tmp<0)
		tmp=0;
	*r = tmp;
	tmp = (298*(y-16) - 100*(u-128)-208*(v-128) + 128) >> 8;
	if (tmp >255)
		tmp=255;
	if (tmp<0)
		tmp=0;
	*g = tmp;
	tmp = (298*(y-16) + 516*(u-128) + 128) >> 8;
	if (tmp >255)
		tmp=255;
	if (tmp<0)
		tmp=0;
	*b = tmp;
}

void yuyvtorgb(unsigned char* iyuv, unsigned char* rgb, int width, int height) {
	int i,n=0;
	unsigned char y0,u,y1,v,r,g,b;
	
	unsigned char* yuv = iyuv;
	for (i=0;i<(width*height);) {
		y0=yuv[0];
		u=yuv[1];
		y1=yuv[2];
		v=yuv[3];
		yuv+=4;
		yuvtorgb_pixel(y0,u,v,&rgb[n++],&rgb[n++],&rgb[n++]);
		yuvtorgb_pixel(y1,u,v,&rgb[n++],&rgb[n++],&rgb[n++]);
        i++;
	}
}

static QImage v4limage;

void process_image(void * d) {
#ifdef Q_OS_LINUX
    uchar* b = (uchar*) malloc(CAMERA_WIDTH * CAMERA_HEIGHT * 3 * 2);
    yuyvtorgb((unsigned char*) d, (unsigned char*) b, CAMERA_WIDTH, CAMERA_HEIGHT);
   
    v4limage = QImage(b, CAMERA_WIDTH, CAMERA_HEIGHT, QImage::Format_RGB888, [](void* v){
        free(v);
    }, (void*) b);
#endif
}
 
V4L2ImageSource::V4L2ImageSource()
{
    connect(&Settings::saturation(), &Setting::valueChanged, this, &V4L2ImageSource::onSaturationChanged);
    connect(&Settings::lockExposure(), &Setting::valueChanged, this, &V4L2ImageSource::onLockExposureChanged);
}

V4L2ImageSource::~V4L2ImageSource()
{
    stop();
}

void V4L2ImageSource::start()
{
#ifdef Q_OS_LINUX
    init_camera(Settings::v4lDevice().value().toString().toLocal8Bit());
    set_saturation(Settings::saturation().value().toInt());
    
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(getImage()));
    timer->setInterval(0);
    timer->start();
#endif
}

void V4L2ImageSource::stop()
{
#ifdef Q_OS_LINUX
    terminate_camera();
#endif
}

void V4L2ImageSource::getImage()
{
#ifdef Q_OS_LINUX
    camera_main_iteration();
    QImage newImage(v4limage);
    newImage.detach();
    emit update(newImage);
#endif
}

void V4L2ImageSource::onSaturationChanged(const QVariant& value)
{
#ifdef Q_OS_LINUX
    set_saturation(value.toInt());
#endif
}

void V4L2ImageSource::onLockExposureChanged(const QVariant& value)
{
#ifdef Q_OS_LINUX
    set_auto_exposure(value.toBool() ? 0 : 1);
#endif
}

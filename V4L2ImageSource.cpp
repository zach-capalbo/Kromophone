#include "V4L2ImageSource.h"
#include "v4lcamera_raw.h"
#include "Settings.h"
#include "Logger.h"
#include <QTimer>

extern "C" void process_image(void* data);

void yuvtorgb_pixel(unsigned int y, unsigned int u, unsigned int v, unsigned char* r, unsigned char* g, unsigned char* b, bool bgr) {
	int tmp;
    if (y < 16)
        y = 16;
    
    if (v < 128)
        v = 128;
    
    if (u < 128)
        u = 128;
    
	tmp = (298*(y-16) + 409*(v-128) + 128) >> 8;
	if (tmp >255)
		tmp=255;
	if (tmp<0)
		tmp=0;
	*(bgr ? b : r) = tmp;
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
	*(bgr ? r : b) = tmp;
}

void yuyvtorgb(unsigned char* iyuv, unsigned char* rgb, int width, int height, bool bgr) {
	int i,n=0;
	unsigned char y0,u,y1,v,r,g,b;
	
	unsigned char* yuv = iyuv;
	for (i=0;i<(width*height);) {
		y0=yuv[0];
		u=yuv[1];
		y1=yuv[2];
		v=yuv[3];
		yuv+=4;
		yuvtorgb_pixel(y0,u,v,&rgb[n++],&rgb[n++],&rgb[n++], bgr);
		yuvtorgb_pixel(y1,u,v,&rgb[n++],&rgb[n++],&rgb[n++], bgr);
        i++;
	}
}

void yuyvtorgb_new(unsigned char* yuyv_image, unsigned char* rgb_image, int width, int height) {
    int y;
    int cr;
    int cb;
    
    double r;
    double g;
    double b;
    
    for (int i = 0, j = 0; i < width * height * 3; i+=6, j+=4) {
        //first pixel
        y = yuyv_image[j];
        cb = yuyv_image[j+1];
        cr = yuyv_image[j+3];
    
        r = y + (1.4065 * (cr - 128));
        g = y - (0.3455 * (cb - 128)) - (0.7169 * (cr - 128));
        b = y + (1.7790 * (cb - 128));
    
        //This prevents colour distortions in your rgb image
        if (r < 0) r = 0;
        else if (r > 255) r = 255;
        if (g < 0) g = 0;
        else if (g > 255) g = 255;
        if (b < 0) b = 0;
        else if (b > 255) b = 255;
    
        rgb_image[i] = (unsigned char)r;
        rgb_image[+1] = (unsigned char)g;
        rgb_image[i+2] = (unsigned char)b;
    
        //second pixel
        y = yuyv_image[j+2];
        cb = yuyv_image[j+1];
        cr = yuyv_image[j+3];
    
        r = y + (1.4065 * (cr - 128));
        g = y - (0.3455 * (cb - 128)) - (0.7169 * (cr - 128));
        b = y + (1.7790 * (cb - 128));
    
        if (r < 0) r = 0;
        else if (r > 255) r = 255;
        if (g < 0) g = 0;
        else if (g > 255) g = 255;
        if (b < 0) b = 0;
        else if (b > 255) b = 255;
    
        rgb_image[i+3] = (unsigned char)r;
        rgb_image[+4] = (unsigned char)g;
        rgb_image[i+5] = (unsigned char)b;
    }
}

static QImage v4limage;

void process_image(void * d) {
#ifdef Q_OS_LINUX
    uchar* b = (uchar*) malloc(CAMERA_WIDTH * CAMERA_HEIGHT * 3 * 2);
    yuyvtorgb((unsigned char*) d, (unsigned char*) b, CAMERA_WIDTH, CAMERA_HEIGHT, Settings::bgr().value().toBool());
   
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

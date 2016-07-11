#ifndef STATICIMAGECOLORSOURCE_H
#define STATICIMAGECOLORSOURCE_H

#include "ImageColorSource.h"

class StaticImageColorSource : public ImageColorSource
{
	Q_OBJECT
public:
	StaticImageColorSource();
	
	const Color color();
	
	QWidget* widget() { return displayWidget; }
	
public slots:
	void updateImage(const QImage& newImage);
    void updateColor();
    void setMouse(QPoint pos);
    
protected:
	bool eventFilter(QObject *, QEvent *);
	
signals:
	void colorChanged(Color color);
	
private:
	QWidget* displayWidget;
	QLabel* imageLabel;
	QImage image;
};


#endif // STATICIMAGECOLORSOURCE_H

#ifndef IMAGESOURCEWIDGET_H
#define IMAGESOURCEWIDGET_H

#include <QWidget>

namespace Ui {
class ImageSourceWidget;
}

class ImageSourceWidget : public QWidget
{
	Q_OBJECT
	
public:
	explicit ImageSourceWidget(QWidget *parent = 0);
	~ImageSourceWidget();
	
private:
	Ui::ImageSourceWidget *ui;
};

#endif // IMAGESOURCEWIDGET_H

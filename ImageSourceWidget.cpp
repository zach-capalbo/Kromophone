#include "ImageSourceWidget.h"
#include "ui_ImageSourceWidget.h"

ImageSourceWidget::ImageSourceWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ImageSourceWidget)
{
	ui->setupUi(this);
	setMouseTracking(true);
}

ImageSourceWidget::~ImageSourceWidget()
{
	delete ui;
}

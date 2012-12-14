#include "ColorPreviewWidget.h"

ColorPreviewWidget::ColorPreviewWidget(QWidget *parent) :
	QWidget(parent)
{
	resize(48,48);
}

void ColorPreviewWidget::setColor(const Color &color)
{
	QString stylesheet = QString("background: rgb(%1,%2,%3)")
			.arg((int)(color.Red*255)).arg((int)(color.Green*255)).arg((int)(color.Blue*255));
	this->setStyleSheet(stylesheet);
}

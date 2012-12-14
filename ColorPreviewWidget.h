#ifndef COLORPREVIEWWIDGET_H
#define COLORPREVIEWWIDGET_H

#include <QWidget>
#include <Color.h>

class ColorPreviewWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ColorPreviewWidget(QWidget *parent = 0);
	
signals:
	
public slots:
	void setColor(const Color& color);
};

#endif // COLORPREVIEWWIDGET_H

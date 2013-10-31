#ifndef DROIDWIDGET_H
#define DROIDWIDGET_H

#include <QWidget>

namespace Ui {
class DroidWidget;
}

class DroidWidget : public QWidget
{
	Q_OBJECT
	
public:
	explicit DroidWidget(QWidget *parent = 0);
	~DroidWidget();
	
private:
	Ui::DroidWidget *ui;
};

#endif // DROIDWIDGET_H

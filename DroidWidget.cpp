#include "DroidWidget.h"
#include "ui_DroidWidget.h"

DroidWidget::DroidWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DroidWidget)
{
	ui->setupUi(this);
}

DroidWidget::~DroidWidget()
{
	delete ui;
}

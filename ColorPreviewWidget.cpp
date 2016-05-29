/*
    This file is part of The Kromophone.
    Copyright (C) 2014 Zachary Capalbo
 
	The Kromophone is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The Kromophone is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Kromophone.  If not, see <http://www.gnu.org/licenses/>.
	
*/
#include "ColorPreviewWidget.h"
#include <QDebug>

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

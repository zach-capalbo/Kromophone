/*
    This file is part of The Kromophone.
 
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

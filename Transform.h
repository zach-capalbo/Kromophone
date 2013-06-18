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
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QObject>
#include <stdlib.h>
#include "Sound.h"
#include "Color.h"

#include <QPointF>
/**
*/
class Transform : public QObject {

	Q_OBJECT

public:

    Transform();

private:


signals:

	void SoundGenerated(Sound P);
	
	void SoundsGenerated(SoundList sounds);

public slots:

	virtual void ReceiveColor(Color P);
	
	void setSweep(bool enabled, const QPointF& sweepPct);
	
protected:
	
	QPointF sweep;
	
	bool sweepEnabled;

};

class HSLMode : public Transform
{
	Q_OBJECT
	
public:
	
	HSLMode();
	
signals:
	
public slots:
	
	virtual void ReceiveColor(Color P);
};

class RGBMode : public Transform
{
	Q_OBJECT
	
public:
	
	RGBMode();
	
signals:
	
public slots:
	
	virtual void ReceiveColor(Color P);
};

class RGBYWMode : public RGBMode
{
	Q_OBJECT
	
public:
	
	RGBYWMode();
	
public slots:
	
	virtual void ReceiveColor(Color P);
};

#endif

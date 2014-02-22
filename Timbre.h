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
#ifndef TIMBRE_H
#define TIMBRE_H

#include <qmath.h>
#include <QHash>
#include <QVector>

class Timbre
{
public:
	void initialize(unsigned int frequency, unsigned int sampleRate);
	bool initialized() { return !sampleBuffer.isEmpty(); }
	qreal getSample(unsigned int sampleIndex);
	
protected:
	virtual qreal generateTone(float angleInRadians)=0;
	
private:
	void fillFloatBuffer(QVector<qreal>& buffer, unsigned int toneFrequency, unsigned int sampleRate);
	QVector<qreal> sampleBuffer;
};

class Trumpet : public Timbre
{
public:
	virtual qreal generateTone(float angleInRadians);
	
	static Trumpet timbre;
};

class SinTimbre : public Timbre
{
public:
	virtual qreal generateTone(float angleInRadians);
	
	static SinTimbre timbre;
};

class OrganTimbre : public Timbre
{
public:
	virtual qreal generateTone(float angleInRadians);
	
	static OrganTimbre timbre;
};

class UkuleleTimbre : public Timbre
{
public:
	qreal generateTone(float angleInRadians);
	
	static UkuleleTimbre timbre;
};

#endif // TIMBRE_H

#ifndef TIMBRE_H
#define TIMBRE_H

#include <qmath.h>

class Timbre
{
public:
	virtual qreal generateTone(float angleInRadians)=0;
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

#endif // TIMBRE_H

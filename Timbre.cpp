#include "Timbre.h"

Trumpet Trumpet::timbre;

qreal Timbre::getTone(float angleInRadians)
{
	generateTone(angleInRadians);
//	int cacheIndex = angleInRadians * 10000.0f;
//	if (!toneCache.contains(cacheIndex))
//	{
//		toneCache[cacheIndex] = generateTone(angleInRadians);
//	}
	
//	return toneCache[cacheIndex];
}

qreal Trumpet::generateTone(float phase)
{
	phase *= 10;
	return 0.2 * ( 0.66f*sin(phase*0.05f) + 0.54f*sin(phase*0.1f) + 0.6f*sin(phase*0.15f) + 0.82f*sin(phase*0.2f) + 0.83f*sin(phase*0.25f) + 0.9f*sin(phase*0.3f) + 0.83f*sin(phase*0.35f) + 0.71f*sin(phase*0.4f) + 0.48f*sin(phase*0.45f) + 0.3f*sin(phase*0.5f) + 0.21f*sin(phase*0.55f) + 0.22f*sin(phase*0.6f) + 0.15f*sin(phase*0.65f) + 0.1f*sin(phase*0.7f) );
	//return 0.31f*sin(phase*0.55f) + 0.32f*sin(phase*0.6f) + 0.22f*sin(phase*0.65f) + 0.14f*sin(phase*0.7f);
}

SinTimbre SinTimbre::timbre;

qreal SinTimbre::generateTone(float phase)
{
	return qSin(phase);
}

OrganTimbre OrganTimbre::timbre;

qreal OrganTimbre::generateTone(float phase)
{
	phase *= 10;
	return 0.2 * (0.001831f*sin(phase*0.100000f) + 0.117470f*sin(phase*0.200000f) + 0.606061f*sin(phase*0.300000f) + 0.667617f*sin(phase*0.400000f) + 0.323250f*sin(phase*0.500000f) + 5.296854f*sin(phase*0.600000f) + 0.323250f*sin(phase*0.700000f) + 0.667617f*sin(phase*0.800000f) + 0.606061f*sin(phase*0.900000f) + 0.117470f*sin(phase*1.000000f));
}

UkuleleTimbre UkuleleTimbre::timbre;

qreal UkuleleTimbre::generateTone(float phase)
{
	phase *= 10;
	return 0.4 * (0.914102564102564f*sin(0.0406f*phase) +1.0f*sin(0.0518f*phase) +0.624358974358974f*sin(0.0636f*phase) +0.683333333333333f*sin(0.1038f*phase) +0.638461538461538f*sin(0.1554f*phase) +0.4846153846153);
}

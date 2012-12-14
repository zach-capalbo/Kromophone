#include "Timbre.h"

Trumpet Trumpet::timbre;

qreal Trumpet::generateTone(float phase)
{
	phase *= 3;
	//return 0.66f*sin(phase*0.05f) + 0.54f*sin(phase*0.1f) + 0.6f*sin(phase*0.15f) + 0.82f*sin(phase*0.2f) + 0.83f*sin(phase*0.25f) + 0.9f*sin(phase*0.3f) + 0.83f*sin(phase*0.35f) + 0.71f*sin(phase*0.4f) + 0.48f*sin(phase*0.45f) + 0.3f*sin(phase*0.5f) + 0.21f*sin(phase*0.55f) + 0.22f*sin(phase*0.6f) + 0.15f*sin(phase*0.65f) + 0.1f*sin(phase*0.7f);
	return 0.31f*sin(phase*0.55f) + 0.32f*sin(phase*0.6f) + 0.22f*sin(phase*0.65f) + 0.14f*sin(phase*0.7f);
}

SinTimbre SinTimbre::timbre;

qreal SinTimbre::generateTone(float phase)
{
	return qSin(phase);
}

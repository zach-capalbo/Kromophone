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
#include "Timbre.h"

void Timbre::initialize(unsigned int frequency, unsigned int sampleRate)
{
	fillFloatBuffer(sampleBuffer, frequency, sampleRate);
}

qreal Timbre::getSample(unsigned int sampleIndex)
{
	Q_ASSERT(!sampleBuffer.isEmpty());
	return sampleBuffer.at(sampleIndex % sampleBuffer.size());
}

qreal Trumpet::generateTone(float phase)
{
	// Make sure we're in range for dimensionless phase.
	Q_ASSERT(phase <= 1.0f && phase >= 0.0f);
	
	phase *= 2.0f * M_PI * 20.0f;
	return 0.13605 * ( 0.66f*sin(phase*0.05f) + 0.54f*sin(phase*0.1f) + 0.6f*sin(phase*0.15f) + 0.82f*sin(phase*0.2f) + 0.83f*sin(phase*0.25f) + 0.9f*sin(phase*0.3f) + 0.83f*sin(phase*0.35f) + 0.71f*sin(phase*0.4f) + 0.48f*sin(phase*0.45f) + 0.3f*sin(phase*0.5f) + 0.21f*sin(phase*0.55f) + 0.22f*sin(phase*0.6f) + 0.15f*sin(phase*0.65f) + 0.1f*sin(phase*0.7f) );
}

qreal SinTimbre::generateTone(float phase)
{
	Q_ASSERT(phase <= 1.0f && phase >= 0.0f);
	phase *= 2.0f * M_PI;
	return qSin(phase);
}

qreal OrganTimbre::generateTone(float phase)
{
	Q_ASSERT(phase <= 1.0f && phase >= 0.0f);
	phase *= 2.0f * M_PI * 10.0f;
	return 0.11458 * (0.001831f*sin(phase*0.100000f) + 0.117470f*sin(phase*0.200000f) + 0.606061f*sin(phase*0.300000f) + 0.667617f*sin(phase*0.400000f) + 0.323250f*sin(phase*0.500000f) + 5.296854f*sin(phase*0.600000f) + 0.323250f*sin(phase*0.700000f) + 0.667617f*sin(phase*0.800000f) + 0.606061f*sin(phase*0.900000f) + 0.117470f*sin(phase*1.000000f));
}

qreal UkuleleTimbre::generateTone(float phase)
{
	Q_ASSERT(phase <= 1.0f && phase >= 0.0f);
	phase *= 24.631;
	return 0.11458 * (0.914102564102564f*sin(0.0406f*phase) +1.0f*sin(0.0518f*phase) +0.624358974358974f*sin(0.0636f*phase) +0.683333333333333f*sin(0.1038f*phase) +0.638461538461538f*sin(0.1554f*phase) +0.4846153846153);
}

void Timbre::fillFloatBuffer(QVector<qreal>& buffer, unsigned int toneFrequency, unsigned int sampleRate)
{
	int numberOfPoints = sampleRate / toneFrequency;
	buffer.resize(numberOfPoints);
	
	for (unsigned int i = 0; i < numberOfPoints; i++)
	{
		buffer[i] = generateTone((float) i / (float) (numberOfPoints));
	}
}

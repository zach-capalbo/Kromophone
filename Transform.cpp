#include "Transform.h"

Transform::Transform() : sweepEnabled(false)
{}

void Transform::setSweep(bool enabled, const QPointF &sweepPct)
{
	sweepEnabled = enabled;
	
	sweep = sweepPct;
}

void Transform::ReceiveColor(Color P) {
	Sound newSound;
	
	//Testing purposes
	newSound.pitch = P.Red;
	newSound.pan = P.Green;
	newSound.volume = P.Blue;
	newSound.timbre = NULL;
	//
	emit SoundGenerated(newSound);
}

HSLMode::HSLMode() : Transform()
{
	
}

void HSLMode::ReceiveColor(Color P)
{
	Sound newSound;
	
	float hue, saturation, luminosity;
	
	P.hsl(hue, saturation, luminosity);
	
	newSound.pitch = 1.0 - hue;
	
	newSound.pan = saturation;
	
	newSound.volume = luminosity;
	
	newSound.timbre = &SinTimbre::timbre; //&Trumpet::timbre;
	
	emit SoundGenerated(newSound);
}

RGBMode::RGBMode() : Transform()
{
	
}

void RGBMode::ReceiveColor(Color P)
{
	SoundList l;
	
	l.resize(3);
	
	l[0].pitch = 5.0f;
	l[0].pan = 1.0f;
	l[0].timbre = &Trumpet::timbre;
	l[0].volume = P.Red * 0.8;
	
	l[1].pitch = 3.0f;
	l[1].pan = 0.0f;
	l[1].timbre = &UkuleleTimbre::timbre;
	l[1].volume = P.Green;
	
	l[2].pitch = 1.0f;
	l[2].pan = 0.5f;
	l[2].timbre = &Trumpet::timbre;
	l[2].volume = P.Blue;
	
	emit SoundsGenerated(l);
}

RGBYWMode::RGBYWMode() : RGBMode()
{
	
}

void RGBYWMode::ReceiveColor(Color P)
{
	SoundList l;
	
	float saturation = P.saturation();
	
	float yellow = qMin( P.Red, P.Green ) - saturation;
	
	l.resize(5);
	
	l[0].pitch = 5.0f;
	l[0].pan = 1.0f;
	l[0].timbre = &Trumpet::timbre;
	l[0].volume = P.Red - yellow - saturation;
	
	l[1].pitch = 3.0f;
	l[1].pan = 0.0f;
	l[1].timbre = &OrganTimbre::timbre;
	l[1].volume = P.Green - yellow - saturation;
	
	l[2].pitch = 1.0f;
	l[2].pan = 0.5f;
	l[2].timbre = &Trumpet::timbre;
	l[2].volume = P.Blue - saturation;
	
	l[3].pitch = 4.0f;
	l[3].pan = 0.8f;
	l[3].timbre = &Trumpet::timbre;
	l[3].volume = yellow;
	
	l[4].pitch = 2.0f;
	l[4].pan = 1.0f;
	l[4].timbre = &SinTimbre::timbre;
	l[4].volume = saturation;
	
//	for (int i = 0; i < l.size(); i++)
//	{
//		if (i != 1)
//		{
//			l[i].volume = 0;
//		}
//	}
	
	if (sweepEnabled)
	{
		for (int i = 0; i < l.size(); i++)
		{
			l[i].pan = 1.0f - sweep.x();
		}
	}
	
	emit SoundsGenerated(l);
}

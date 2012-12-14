#include "Transform.h"

Transform::Transform()
{}

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

HSLMode::HSLMode()
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
	
	newSound.timbre = &Trumpet::timbre;
	
	emit SoundGenerated(newSound);
}

RGBMode::RGBMode()
{
	
}

void RGBMode::ReceiveColor(Color P)
{
	SoundList l;
	
	l.resize(3);
	
	l[0].pitch = 1.0f;
	l[0].pan = 1.0f;
	l[0].timbre = &Trumpet::timbre;
	l[0].volume = P.Red;
	
	l[1].pitch = 0.5f;
	l[1].pan = 0.0f;
	l[1].timbre = &SinTimbre::timbre;
	l[1].volume = P.Green;
	
	l[2].pitch = 0.0f;
	l[2].pan = 0.5f;
	l[2].timbre = &Trumpet::timbre;
	l[2].volume = P.Blue;
	
	emit SoundsGenerated(l);
}

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

#include "SoundOut.h"
#include "Sound.h"
#include <iostream>
using namespace std;

SoundOut::SoundOut()
{
}

void SoundOut::PlaySound(const Sound& InputSound)
{
    cout << "pitch: " << InputSound.pitch << endl;
    cout << "pan: " << InputSound.pan << endl;
    cout << "volume: " << InputSound.volume << endl;
}

void SoundOut::PlaySounds(const SoundList& InputSounds)
{
	foreach(Sound s, InputSounds)
	{
		PlaySound(s);
	}
}

#include "SoundOut.h"
#include "Sound.h"
#include <iostream>
using namespace std;

SoundOut::SoundOut()
{
}

void SoundOut::PlaySound(Sound InputSound)
{
    cout << "pitch: " << InputSound.pitch << endl;
    cout << "pan: " << InputSound.pan << endl;
    cout << "volume: " << InputSound.volume << endl;
}

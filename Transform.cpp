#include "Transform.h"

void Transform::fromJon(Color P) {
	Sound newSound;
	// NOTE: THIS IS BULLSHIT
	newSound.pitch = P.Red;
	newSound.pan = P.Green;
	newSound.volume = P.Blue;
	newSound.timbre = NULL;
	//
	emit toNathan(newSound);
}
#include "music.h"
#include <iostream>



music::music(bool sound)
{
	backgroundMusic.openFromFile("music.ogg");
	if (!backgroundMusic.openFromFile("music.ogg"))
	{
		std::cout << "Error opening background music file" << std::endl;
	}
	playing = sound;
	backgroundMusic.setLoop(true);
	backgroundMusic.setPosition(0, 0, 0); // change its 3D position
	backgroundMusic.setVolume(50);
	if (playing) play();
}

void music::switcher() {
	if (playing) {
		//Switch to off
		playing = false;
		stop();
	}
	else {
		//Switch to on
		playing = true;
		play();
	}
}

void music::play() {
	backgroundMusic.play();
}

void music::stop() {
	backgroundMusic.stop();
}
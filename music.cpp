#include "music.h"
#include <iostream>



music::music(bool sounds, int element)
{
	elementtype = element;
	if (elementtype == 1)
	{
		if (!soundBuffer.loadFromFile("music.ogg"))
		{
			std::cout << "Error loading background music file" << std::endl;
		}
		playing = sounds;
		sound.setBuffer(soundBuffer);
		sound.setLoop(true);
		sound.setVolume(50);
		if (playing) play();
	}
	else if (elementtype == 2)
	{
		boxMusic.openFromFile("slide.ogg");
		if (!boxMusic.openFromFile("slide.ogg"))
		{
			std::cout << "Error opening slide music file" << std::endl;
		}
		playing = sounds;
		boxMusic.setLoop(false);
		boxMusic.setPosition(0, 0, 0); // change its 3D position
		boxMusic.setVolume(50);
	}
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
	if (elementtype == 1 && playing)
		sound.play();
	else if (elementtype == 2 && playing)
		boxMusic.play();
}

void music::stop() {
	if (elementtype == 1)
		sound.stop();
	else if (elementtype == 2)
		boxMusic.stop();
}
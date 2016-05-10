/*
	John Ayad, 900150853
	Monica Fahmy, 900142228
	Youssef Ibrahim, 900142576
	All Rights Reserved.

	CS110 - Spring 2016 - Dr. Howaida Ismail
	Sokoban
*/
#include <iostream>
#include "music.h"

music::music(bool sounds, int element)
{
	elementtype = element;
	if (elementtype == 1)
	{
		if (!bmusic.openFromFile("music.ogg"))
		{
			std::cout << "Error loading background music file" << std::endl;
		}
		playing = sounds;
		bmusic.setLoop(true);
		bmusic.setPosition(0, 0, 0); // change its 3D position
		bmusic.setVolume(50);
		if (playing) play();
	}
	else if (elementtype == 2)
	{
		if (!soundBuffer.loadFromFile("slide.ogg"))
		{
			std::cout << "Error opening slide music file" << std::endl;
		}
		playing = sounds;
		sound.setBuffer(soundBuffer);
		sound.setLoop(false);
		sound.setPosition(0, 0, 0); // change its 3D position
		sound.setVolume(50);
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
		if (elementtype == 1)
			play();
	}
}

void music::play() {
	if (elementtype == 1 && playing)
		bmusic.play();
	else if (elementtype == 2 && playing)
		sound.play();
}

void music::stop() {
	if (elementtype == 1)
		bmusic.stop();
	else if (elementtype == 2)
		sound.stop();
}
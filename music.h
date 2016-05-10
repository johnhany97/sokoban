/*
	John Ayad, 900150853
	Monica Fahmy, 900142228
	Youssef Ibrahim, 900142576
	All Rights Reserved.

	CS110 - Spring 2016 - Dr. Howaida Ismail
	Sokoban
*/
#ifndef MUSIC_H
#define MUSIC_H
#include <SFML\Audio.hpp>
using namespace sf;
class music
{
private:
	bool playing;
	Music bmusic;
	SoundBuffer soundBuffer;
	Sound sound;
	int elementtype;
public:
	music(bool, int);
	void switcher();
	void play();
	void stop();
};

#endif
#ifndef MUSIC_H
#define MUSIC_H
#include <SFML\Audio.hpp>
using namespace sf;
class music
{
private:
	bool playing;
	Music backgroundMusic, boxMusic;
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
#ifndef MUSIC_H
#define MUSIC_H
#include <SFML\Audio.hpp>
using namespace sf;
class music
{
private:
	bool playing;
	Music backgroundMusic;
public:
	music(bool);
	void switcher();
	void play();
	void stop();
};

#endif
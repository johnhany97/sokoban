#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
class player
{
public:
	player();
	void setPosition(int, int);
	//Vector2 getPosition();
	int getXPosition();
	int getYPosition();

private:
	sf::Sprite pl;
	sf::Texture plTexture;
	int xLocation, yLocation;
};

#endif

/*sfml-audio-d.lib
sfml-graphics-d.lib
sfml-network-d.lib
sfml-system-d.lib
sfml-window-d.lib*/
#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
class player
{
public:
	player();
	void setPosition(int, int);
	sf::Vector2f getPosition();
	int getXPosition();
	int getYPosition();
	void draw(sf::RenderWindow&);

private:
	sf::Sprite pl;
	sf::Texture plTexture;
	int xLocation, yLocation;
};

#endif
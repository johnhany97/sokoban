#ifndef WALL_H
#define WALL_H
#include <SFML/Graphics.hpp>

class wall
{
public:
	wall();
	void setPosition(int, int);
	sf::Vector2f getPosition();
	int getXPosition();
	int getYPosition();
	void draw(sf::RenderWindow&);

private:
	sf::Sprite wl;
	sf::Texture wlTexture;
	int xLocation, yLocation;
};


#endif WALL_H


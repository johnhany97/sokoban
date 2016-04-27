#include "player.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

player::player()
{
	plTexture.loadFromFile("player.png");
	if (!plTexture.loadFromFile("player.png"))
	{
		std::cout << "Failed to load player spritesheet!" << std::endl;
	}
	pl.setTexture(plTexture);
	xLocation = 0;
	yLocation = 0;
	pl.setPosition(xLocation, yLocation);
}
void player::setPosition(int x, int y) {
	pl.setPosition(x, y);
}

Vector2f player::getPosition() {
	return pl.getPosition();
}

int player::getXPosition() {
	return xLocation;
}

int player::getYPosition() {
	return yLocation;
}
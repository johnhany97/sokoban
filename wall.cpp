#include "wall.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;



wall::wall()
{
	wlTexture.loadFromFile(" ");
	if (!wlTexture.loadFromFile(" "))
	{
		std::cout << "Failed to load box spritesheet!" << std::endl;
	}
	wl.setTexture(wlTexture);
	xLocation = 0;
	yLocation = 0;
	wl.setPosition(xLocation, yLocation);
}

void wall::setPosition(int x, int y) {
	wl.setPosition(x, y);
}

sf::Vector2f wall::getPosition() {
	return wl.getPosition();
}

int wall::getXPosition() {
	return xLocation;
}

int wall::getYPosition() {
	return yLocation;
}

void wall::draw(sf::RenderWindow& window) {
	window.draw(wl);
}


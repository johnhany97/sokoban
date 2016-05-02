#include "cell.h"
#include <string>
#include <iostream>

cell::cell()
{
	xLoc = 0; yLoc = 0;
	onGoal = false;
}

cell::kind cell::getType() {
	return type;
}

void cell::initialize() {
	switch (type) {
	case 0: //Empty tile (floor)
		clTexture.loadFromFile("floor.png");
		if (!clTexture.loadFromFile("floor.png"))
		{
			std::cout << "Failed to load floor spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture);
		xLoc = 0;
		yLoc = 0;
		break;
	case 1: //Wall
		clTexture.loadFromFile("wall.png");
		if (!clTexture.loadFromFile("wall.png"))
		{
			std::cout << "Failed to load wall spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture);
		xLoc = 0;
		yLoc = 0;
		break;
	case 2: //Goal
		clTexture.loadFromFile("goal.png");
		if (!clTexture.loadFromFile("goal.png"))
		{
			std::cout << "Failed to load goal spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture);
		xLoc = 0;
		yLoc = 0;
		break;
	case 3: //Box
		clTexture.loadFromFile("box.png");
		if (!clTexture.loadFromFile("box.png"))
		{
			std::cout << "Failed to load box spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture);
		xLoc = 0;
		yLoc = 0;
		onGoal = false;
		break;
	case 4: //Player
		clTexture.loadFromFile("player.png");
		if (!clTexture.loadFromFile("player.png"))
		{
			std::cout << "Failed to load player spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture);
		xLoc = 0;
		yLoc = 0;
		break;
	case 5: //S P A C E
		clTexture.loadFromFile("space.png");
		if (!clTexture.loadFromFile("space.png"))
		{
			std::cout << "Failed to load space spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture);
		xLoc = 0;
		yLoc = 0;
		break;
	}
}

void cell::setType(int t) {
	switch (t) {
	case 0: //Empty
		type = empty;
		break;
	case 1: //Wall
		type = wall;
		break;
	case 2: //Goal
		type = goal;
		break;
	case 3: //Box
		type = box;
		break;
	case 4: //Player
		type = player;
		break;
	default: //S P A C E
		type = space;
		break;
	}
}

void cell::setPosition(int k, int z) {
	cl.setPosition(k, z);
	xLoc = k;
	yLoc = z;
}

sf::Vector2f cell::getPosition() {
	return cl.getPosition();
}

void cell::goalReach() {
	if (type == box) {
		onGoal = true;
	}
}

bool cell::goalReached() {
	return onGoal;
}

int cell::getXPosition() {
	return xLoc;
}

int cell::getYPosition() {
	return yLoc;
}

void cell::draw(sf::RenderWindow& window) {
	window.draw(cl);
}

void cell::switcher() {
	if (type == box) {
		if (onGoal) {
			onGoal = false;
			clTexture.loadFromFile("box.png");
			if (!clTexture.loadFromFile("box.png"))
			{
				std::cout << "Failed to load box spritesheet!" << std::endl;
			}
			cl.setTexture(clTexture);
		}
		else {
			onGoal = true;
			clTexture.loadFromFile("box_win.png");
			if (!clTexture.loadFromFile("box_win.png")) {
				std::cout << "Failed to load winning box spritesheet!" << std::endl;
			}
			cl.setTexture(clTexture);
		}
	}
}
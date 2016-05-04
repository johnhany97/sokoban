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
		clTexture.loadFromFile("sprites/floor.png");
		if (!clTexture.loadFromFile("sprites/floor.png"))
		{
			std::cout << "Failed to load floor spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture);
		//xLoc = 0;
		//yLoc = 0;
		break;
	case 1: //Wall
		clTexture.loadFromFile("sprites/wall.png");
		if (!clTexture.loadFromFile("sprites/wall.png"))
		{
			std::cout << "Failed to load wall spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture);
		//xLoc = 0;
		//yLoc = 0;
		break;
	case 2: //Goal
		clTexture.loadFromFile("sprites/goal.png");
		if (!clTexture.loadFromFile("sprites/goal.png"))
		{
			std::cout << "Failed to load goal spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture);
		//xLoc = 0;
		//yLoc = 0;
		break;
	case 3: //Box
		clTexture.loadFromFile("sprites/box.png");
		if (!clTexture.loadFromFile("sprites/box.png"))
		{
			std::cout << "Failed to load box spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture, true);
		//xLoc = 0;
		//yLoc = 0;
		onGoal = false;
		break;
	case 4: //Player
		clTexture.loadFromFile("sprites/player.png");
		if (!clTexture.loadFromFile("sprites/player.png"))
		{
			std::cout << "Failed to load player spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture, true);
		//xLoc = 0;
		//yLoc = 0;
		break;
	case 5: //S P A C E
		clTexture.loadFromFile("sprites/space.png");
		if (!clTexture.loadFromFile("sprites/space.png"))
		{
			std::cout << "Failed to load space spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture);
		//xLoc = 0;
		//yLoc = 0;
		break;
	case 6: //Winning Box
		clTexture.loadFromFile("sprites/box_win.png");
		if (!clTexture.loadFromFile("sprites/box_win.png"))
		{
			std::cout << "Failed to load space spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture, true);
		//xLoc = 0;
		//yLoc = 0;
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
	case 6: //Box on goal
		type = box_win;
		break;
	default: //S P A C E
		type = space;
		break;
	}
}

void cell::setPosition(int k, int z) {
	cl.setPosition(k, z);
	xLoc = z;
	yLoc = k;
}

sf::Vector2f cell::getPosition() {
	return cl.getPosition();
}

void cell::goalReach(int swap) {
	if ((type == box || type == box_win) && swap == 1) {
		onGoal = true;
		switcher(1);
	}
	else if ((type == box || type == box_win) && swap == 0) {
		onGoal = false;
		switcher(0);
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
	clTexture.setSmooth(true);
	window.draw(cl);
}

void cell::switcher(int win) {
	if (type == box && win == 0) {
		onGoal = false;
		clTexture.loadFromFile("sprites/box.png");
		if (!clTexture.loadFromFile("sprites/box.png"))
		{
			std::cout << "Failed to load box spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture);
	}
	else if (type == box && win == 1) {
		onGoal = true;
		clTexture.loadFromFile("sprites/box_win.png");
		if (!clTexture.loadFromFile("sprites/box_win.png")) {
			std::cout << "Failed to load winning box spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture);
	}
}
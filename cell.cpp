/*
	John Ayad, 900150853
	Monica Fahmy, 900142228
	Youssef Ibrahim, 900142576
	All Rights Reserved.

	CS110 - Spring 2016 - Dr. Howaida Ismail
	Sokoban
*/
#include "cell.h"
#include <string>
#include <iostream>

cell::cell()
{
	xLoc = 0; yLoc = 0;
	onGoal = false;
	moving = false;
	animationcounter = 0;
	currentDir = 1;
}

cell::kind cell::getType() {
	return type;
}

void cell::initialize() {
	switch (type) {
	case 0: //Empty tile (floor)
		clTexture.loadFromFile("sprites/floor.jpg");
		if (!clTexture.loadFromFile("sprites/floor.jpg"))
		{
			std::cout << "Failed to load floor spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture, true);
		break;
	case 1: //Wall
		clTexture.loadFromFile("sprites/Wall.jpg");
		if (!clTexture.loadFromFile("sprites/Wall.jpg"))
		{
			std::cout << "Failed to load wall spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture, true);
		break;
	case 2: //Goal
		clTexture.loadFromFile("sprites/Goal.png");
		if (!clTexture.loadFromFile("sprites/Goal.png"))
		{
			std::cout << "Failed to load goal spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture, true);
		break;
	case 3: //Box
		clTexture.loadFromFile("sprites/box.png");
		if (!clTexture.loadFromFile("sprites/box.png"))
		{
			std::cout << "Failed to load box spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture, true);
		onGoal = false;
		break;
	case 4: //Player
		clTexture.loadFromFile("sprites/player2.png");
		if (!clTexture.loadFromFile("sprites/player2.png"))
		{
			std::cout << "Failed to load player spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture, true);
		cl.setTextureRect(sf::IntRect(32, 0, 32, 32)); //x loc, y loc, width, length
		cl.setScale(50 / 32.0, 50 / 32.0);
		break;
	case 5: //S P A C E
		clTexture.loadFromFile("sprites/space.png");
		if (!clTexture.loadFromFile("sprites/space.png"))
		{
			std::cout << "Failed to load space spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture, true);
		break;
	case 6: //Winning Box
		clTexture.loadFromFile("sprites/box_win.png");
		if (!clTexture.loadFromFile("sprites/box_win.png"))
		{
			std::cout << "Failed to load space spritesheet!" << std::endl;
		}
		cl.setTexture(clTexture, true);
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
	return cl.getPosition().x;
}

int cell::getYPosition() {
	return cl.getPosition().y;
}

void cell::draw(sf::RenderWindow& window) {
	//clTexture.setSmooth(true);
	window.draw(cl);
}

void cell::switcher(int win) {
	if (type == box && win == 0) {
		onGoal = false;
		sf::Image temp;
		temp.loadFromFile("sprites/box.png");
		if (!temp.loadFromFile("sprites/box.png"))
		{
			std::cout << "Failed to load box spritesheet!" << std::endl;
		}
		clTexture.update(temp);
	}
	else if (type == box && win == 1) {
		onGoal = true;
		sf::Image temp;
		temp.loadFromFile("sprites/box_win.png");
		if (!temp.loadFromFile("sprites/box_win.png"))
		{
			std::cout << "Failed to load box win spritesheet!" << std::endl;
		}
		clTexture.update(temp);
	}
}

bool cell::move(int dir) {
	if (!moving) {
		//Set current direction to dir
		currentDir = dir;
		//Set moving to true
		moving = true;
		//Reset animation counter to zero
		animationcounter = 0;
		return true;
	}
	return false;
}

void cell::update() {

	if (moving && animationcounter < 12.5 && type == 4)
	{
		switch (currentDir) {
		case 0: //up
			cl.move(0, -4);
			if ((animationcounter / 2) % 2 == 0) {
				cl.setTextureRect(sf::IntRect(0, 96, 32, 32));
			}
			else cl.setTextureRect(sf::IntRect(64, 96, 32, 32));
			break;
		case 1: //Down
			cl.move(0, 4);
			if ((animationcounter / 2) % 2 == 0) {
				cl.setTextureRect(sf::IntRect(0, 0, 32, 32));
			}
			else cl.setTextureRect(sf::IntRect(64, 0, 32, 32));
			break;
		case 2: //Left
			cl.move(-4, 0);
			if ((animationcounter / 2) % 2 == 0) {
				cl.setTextureRect(sf::IntRect(0, 32, 32, 32));
			}
			else cl.setTextureRect(sf::IntRect(64, 32, 32, 32));
			break;
		case 3: //Right
			cl.move(4, 0);
			if ((animationcounter / 2) % 2 == 0) {
				cl.setTextureRect(sf::IntRect(0, 64, 32, 32));
			}
			else cl.setTextureRect(sf::IntRect(64, 64, 32, 32));
			break;
		}
		cl.setScale(50.0 / 32, 50 / 32.0);
		animationcounter++;
	}
	else if(animationcounter >= 12.5)
	{
		moving = false;
		animationcounter = 0;
		needToSwap = true;
	}

}

bool cell::doesNeedToSwap()
{
	return needToSwap;
}
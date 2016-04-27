#include "box.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;

box::box()
{
	bxTexture.loadFromFile("box.png");
	if (!bxTexture.loadFromFile("box.png"))
	{
		std::cout << "Failed to load box spritesheet!" << std::endl;
	}
	bx.setTexture(bxTexture);
	xLocation = 0;
	yLocation = 0;
	idealLocX = 0;
	idealLocY = 0;
	bx.setPosition(xLocation, yLocation); 
	onGoal = false;
}
void box::setPosition(int x, int y) {
	bx.setPosition(x, y);
}

Vector2f box::getPosition() {
	return bx.getPosition();
}

void box::setIdealLoc(int x, int y){
	idealLocX = x;
	idealLocY = y;
}

void box::goalReach(){
	onGoal = true;
}

bool box::goalReached(){
	return onGoal;
}

int box::getXPosition() {
	return xLocation;
}

int box::getYPosition() {
	return yLocation;
}

void box::move(int dir){
	/*
		0 for up
		1 for down
		2 for left
		3 for right
	*/
	switch (dir){
	case 0: //Up
		yLocation--;
		bx.move(0, -50);
		break;
	case 1: //Down
		yLocation++;
		bx.move(0, 50);
		break;
	case 2: //Left
		xLocation--;
		bx.move(-50, 0);
		break;
	case 3: //Right
		xLocation++;
		bx.move(50, 0);
		break;
	}
}


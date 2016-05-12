/*
	John Ayad, 900150853
	Monica Fahmy, 900142228
	Youssef Ibrahim, 900142576
	All Rights Reserved.

	CS110 - Spring 2016 - Dr. Howaida Ismail
	Sokoban
*/
#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>

class level
{
private:
	std::vector<int> arr;
	int x;
	int y;
	int size;
	bool initalized = false;
	int push;
public:
	level();
	void initialize(int);
	int getContent(int, int);
	void print();
	int getPush();
	void empty();
};
#endif LEVEL_H


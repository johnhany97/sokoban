#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics.hpp>
#include "cell.h"
#include <vector>

class level
{
private:
	std::vector<int> arr;
	int x;
	int y;
	int size;
public:
	level();
	level(int, int);
	void initialize(int);
	int getContent(int, int);
	void print();
};
#endif LEVEL_H


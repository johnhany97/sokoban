#include "level.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

level::level() {
	size = 0;
	push = 0;
	x = 17;
	y = 17;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			arr.push_back(-1);
			size++;
		}
	}
}

level::level(int k, int z)
{
	size = 0;
	push = 0;
	x = k;
	y = z;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			arr.push_back(-1);
			size++;
		}
	}
}

void level::initialize(int levelNo) {
	int i = 0, j = 0;
	ifstream ip;
	ip.open("levels/" + to_string(levelNo) + ".txt");
	int t;
	ip >> t;
	push = t;
	char x;
	ip.get(x);
	for (int i = 0; i < x && !ip.eof(); i++) {
		for (int j = 0; j < y && !ip.eof(); j++) {
			switch (x) {
			case '#': //Wall
				arr[i*y + j] = 1;
				break;
			case '$': //Box
				arr[i*y + j] = 3;
				break;
			case '.': //Goal
				arr[i*y + j] = 2;
				break;
			case '@': //Player
				arr[i*y + j] = 4;
				break;
			case '?': //Box on goal
				arr[i*y + j] = 5;
				break;
			case '+': //Player on goal
				arr[i*y + j] = 6;
				break;
			case ' ': //Empty
				arr[i*y + j] = 0;
				break;
			}
			ip.get(x);
			if (x == '\n') ip.get(x);
		}
	}
	initalized = true;
	ip.close();
}

void level::setSize(int k, int z)
{ //NEEDS UPDATE
	if (!initalized) {
		x = k;
		y = z;
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < y; j++) {
				arr.push_back(-1);
				size++;
			}
		}
	}
}

int level::getX() const
{
	return x;
}

int level::getY() const
{
	return y;
}

int level::getContent(int i, int j) {
	return arr[i*y + j];
}

void level::print() {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			cout << setw(2);
			cout << arr[i*y + j] << " ";
		}
		cout << endl;
	}
}

int level::getPush() {
	return push;
}

void level::empty() {
	for (int i = 0; i < x; i++) {
		for (int j =0; j < y; j++) {
			arr.pop_back();
		}
	}
}
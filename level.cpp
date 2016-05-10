/*
	John Ayad, 900150853
	Monica Fahmy, 900142228
	Youssef Ibrahim, 900142576
	All Rights Reserved.

	CS110 - Spring 2016 - Dr. Howaida Ismail
	Sokoban
*/
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
	size = x * y;
	for (int i = 0; i < size; i++) {
		arr.push_back(-1);
	}
}

level::level(int k, int z)
{
	push = 0;
	x = k;
	y = z;
	size = k* z;
	for (int i = 0; i < size; i++) {
		arr.push_back(-1);
	}
}

void level::initialize(int levelNo) {
	int i = 0, j = 0;
	ifstream ip;
	ip.open("levels/" + to_string(levelNo) + ".txt");
	int t;
	ip >> t;
	push = t;
	char z;
	ip.get(z);
	if (z == '\n')
		ip.get(z);
	for (int i = 0; i < x; i++) {
		if (z == '\n')
			ip.get(z);
		for (int j = 0; j < y; j++) {
			switch (z) {
			case '#': //Wall
				arr.at(i * y + j) = 1;
				break;
			case '$': //Box
				arr.at(i * y + j) = 3;
				break;
			case '.': //Goal
				arr.at(i * y + j) = 2;
				break;
			case '@': //Player
				arr.at(i * y + j) = 4;
				break;
			case '?': //Box on goal
				arr.at(i * y + j) = 5;
				break;
			case '+': //Player on goal
				arr.at(i * y + j) = 6;
				break;
			case ' ': //Empty
				arr.at(i * y + j) = 0;
				break;
			}
			ip.get(z);
			if (z == '\n')
				ip.get(z);
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
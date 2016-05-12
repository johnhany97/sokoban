/*
	John Ayad, 900150853
	Monica Fahmy, 900142228
	Youssef Ibrahim, 900142576
	All Rights Reserved.

	CS110 - Spring 2016 - Dr. Howaida Ismail
	Sokoban
*/
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "level.h"

using namespace std;

level::level() {
	push = 0;
	x = 17; //Default Size
	y = 17; //Default Size
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			arr.push_back(-1);
		}
	}
	size = arr.size();
}

void level::initialize(int levelNo) {
	int i = 0, j = 0;
	ifstream ip;
	ip.open("levels/" + to_string(levelNo) + ".txt");
	if (ip.fail()) {
		cerr << "Error opening level # " << levelNo << ". Check if file is corrupted\n";
	}
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

int level::getContent(int i, int j) {
	return arr[i * y + j];
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
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			arr.push_back(-1);
		}
	}
	size = arr.size();
}
#include "level.h"
#include <fstream>
#include <iostream>

using namespace std;

level::level(int k, int z)
{
	size = 0;
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
	char x;
	ip.get(x);
	for (int i = 0; i < x && !ip.eof(); i++) {
		for (int j = 0; j < y && !ip.eof(); j++) {
			switch (x) {
			case '#': //Wall
				arr[i*y+j] = 1;
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
			case ' ': //Empty
				arr[i*y+j] = 0;
				break;
			}
			ip.get(x);
		}
	}
}

int level::getContent(int i, int j) {
	return arr[i*y + j];
}

void level::print() {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			cout << arr[i*y + j] << " ";
		}
		cout << endl;
	}
}

/*
	John Ayad, 900150853
	Monica Fahmy, 900142228
	Youssef Ibrahim, 900142576
	All Rights Reserved.

	CS110 - Spring 2016 - Dr. Howaida Ismail
	Sokoban
*/
#include "game.h"

using namespace std;
using namespace sf;

//Prototypes

//Functions
int main() {
	cerr.rdbuf(0);

	game sokoban;
	sokoban.gameLoop();

	system("pause");
	return 0;
}


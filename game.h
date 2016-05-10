/*
	John Ayad, 900150853
	Monica Fahmy, 900142228
	Youssef Ibrahim, 900142576
	All Rights Reserved.

	CS110 - Spring 2016 - Dr. Howaida Ismail
	Sokoban
*/
#ifndef GAME_H
#define GAME_H
#include "level.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
class game
{
private:
	RenderWindow *window;
	Clock win_clock;
	bool win_pic = true;
	Image icon;
public:
	game();
	void render();
	void gameLoop();
	void initialize();
	void levelChooser();
	void levelInitalize(level&, int);
	bool valideMove(int);
	bool NextIsBox(int);
	void boxer();
	bool gameWin();
	void textAligner(Text&);
	bool mousePress(int spriteNo);
	void undo();
	~game();
};
#endif


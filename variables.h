/*
	John Ayad, 900150853
	Monica Fahmy, 900142228
	Youssef Ibrahim, 900142576
	All Rights Reserved.

	CS110 - Spring 2016 - Dr. Howaida Ismail
	Sokoban
*/
#ifndef VARIABLES_H
#define VARIABLES_H

#include <SFML/Graphics.hpp>
#include <string>
#include "cell.h"
#include "mainmenu.h"
#include "music.h"
#include "settingsmenu.h"

#define SCRWIDTH 950
#define SCRHEIGHT 1000

using namespace std;
using namespace sf;

/*
	Main Menu
*/
mainmenu mmenu;
bool sound = true;

/*
	Settings Menu
*/
settingsmenu smenu;
bool infinityModeToggle = false, showTutorial = false;

/*
	Direction Arrays
		Up | Down | Left | Right
*/
const int Dy[4] = { -1, 1, 0, 0 };
const int Dx[4] = { 0, 0, -1, 1 };

/*
	Number of levels available in the game
*/
const int range = 105;

/*
	Master Switch
		0 Main menu (default)
		1 Game
		2 Settings
		3 Level Chooser
*/
int status = 0;

/*
	Limit for user-input in Level Chooser
*/
const int rangeChars = 5;

/*
	Maps used in game to create the scene
*/
cell map1A[17][17], map1B[17][17];

/*
	Level Chooser Variables
*/
bool warning = false;
int counter = 0, levelN;
string s = "";
Text levelChoose, levelIP, levelWarning;

/*
	Game Variables
*/
bool gameFinished = false, gameover, levelWon = false, nextWasBox;
int direction = -1, playerLocX, playerLocY, pushLeft;
string cheatCode = "";
cell player;
Font mainFont, counterFont;
music bgMusic(sound, 1);
music bxMusic(sound, 2);
RectangleShape gameBG;
Sprite gameWinSplash, gameWinNext, gameWinHome, undoButton, homeButton, restartButton;
Texture gameWinSplashTexture, gameWinNextTexture, gameWinHomeTexture, undoButtonTexture, homeButtonTexture, restartButtonTexture;
Text counterText;

#endif


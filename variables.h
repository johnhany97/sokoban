#ifndef VARIABLES_H
#define VARIABLES_H
#define SCRWIDTH 950
#define SCRHEIGHT 1000
#define CELLSIZE 50
#include "cell.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

//Directions Arrays
// UP , DOWN , LEFT , RIGHT
const int Dy[4] = { -1, 1, 0, 0 };
const const int Dx[4] = { 0, 0, -1, 1 };

const int range = 21; //Number of levels we have

//MasterSwitch
int status = 0; //0 for mainmenu, 1 for game, 2 for settings, 3 for level chooser

const int rangeChars = 5; //Number of characters a user is allowed to enter

cell map1A[17][17], map1B[17][17];

//LevelChooser
Text levelChoose, levelIP, levelWarning;
bool warning = false;
string s = "";
int counter = 0;

//Game
Text gameWinText;
RectangleShape gameBG;
Texture gameWinSplashTexture;
Sprite gameWinSplash;
int playerLocX, playerLocY;
bool flag = false, levelWon = false;

#endif


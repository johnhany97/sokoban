/*
	John Ayad, 900150853
	Monica Fahmy, 900142228
	Youssef Ibrahim, 900142576
	All Rights Reserved.

	CS110 - Spring 2016 - Dr. Howaida Ismail
	Sokoban
*/
#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H
#include <SFML/Graphics.hpp>
using namespace sf;

class settingsmenu
{
private:
	Font mainFont;
	RectangleShape settingsBG;
	Sprite settingsTitle, modeButton, tutorialButton, homeButton;
	Texture settingsTitleTexture, modeButtonTexture, tutorialButtonTexture, homeButtonTexture;

public:
	settingsmenu();
	void draw(RenderWindow&);
	bool mousePress(int, RenderWindow&);
	void modePressed(bool&);
	void tutorialPressed(bool&);
};
#endif
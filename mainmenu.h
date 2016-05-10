/*
	John Ayad, 900150853
	Monica Fahmy, 900142228
	Youssef Ibrahim, 900142576
	All Rights Reserved.

	CS110 - Spring 2016 - Dr. Howaida Ismail
	Sokoban
*/
#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>

using namespace sf;
class mainmenu
{
private:
	Sprite playButton, settingsButton, volumeButton, mainTitle;
	RectangleShape mainBG;
	Texture playButtonTexture, settingsButtonTexture, volumeButtonTexture, mainTitleTexture;
public:
	mainmenu();
	void draw(RenderWindow&);
	bool mousePress(int, RenderWindow&);
	void volumePressed(bool&);
};
#endif
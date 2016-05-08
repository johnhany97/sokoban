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
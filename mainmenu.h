#ifndef MAINMENU_H
#define MAINMENU_H
#include <SFML/Graphics.hpp>
using namespace sf;
class mainmenu
{
private:
	Text mainTitle;
	Sprite playButton, settingsButton, volumeButton;
	RectangleShape mainBG;
	Texture playButtonTexture, settingsButtonTexture, volumeButtonTexture;
	Font mainFont;
public:
	mainmenu();
	void draw(RenderWindow&);
	bool mousePress(int, RenderWindow&);
	void volumePressed(bool&);
};
#endif
#ifndef MAINMENU_H
#define MAINMENU_H
#include <SFML/Graphics.hpp>
using namespace sf;
class mainmenu
{
private:
	Text mainTitle, mainPlay, mainSettings;
	Sprite playButton, settingsButton, volumeButton;
	Texture playButtonTexture, settingsButtonTexture, volumeButtonTexture;
	Font mainFont;
public:
	mainmenu();
	void draw(RenderWindow&);
	bool mousePress(int, RenderWindow&);
	void volumePressed(bool&);
};
#endif
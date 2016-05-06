#ifndef MAINMENU_H
#define MAINMENU_H
#include <SFML/Graphics.hpp>
using namespace sf;
class mainmenu
{
private:
	Text mainTitle, mainPlay, mainSettings;
	Font mainFont;
public:
	mainmenu();
	void draw(RenderWindow&);
};
#endif
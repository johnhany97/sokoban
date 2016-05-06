#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H
#include <SFML/Graphics.hpp>
using namespace sf;

class settingsmenu
{
private:
	Text settingsTitle, settingsStatus, settingsBack;
	Font mainFont;
public:
	settingsmenu();
	void draw(RenderWindow&);
};
#endif
#include "settingsmenu.h"
using namespace sf;

settingsmenu::settingsmenu()
{
	//Load Default Font
	mainFont.loadFromFile("Grinched.ttf");

	//Settings Title
	settingsTitle.setFont(mainFont);
	settingsTitle.setString("Settings");
	settingsTitle.setCharacterSize(80);
	settingsTitle.setColor(Color::Magenta);
	settingsTitle.setPosition(Vector2f(370, 100));

	//Settings Status **TEMPORARY**
	settingsStatus.setFont(mainFont);
	settingsStatus.setString("NoThInG to SeE hEre :P");
	settingsStatus.setCharacterSize(80);
	settingsStatus.setColor(Color::White);
	settingsStatus.setPosition(Vector2f(180, 450));

	//Settings Back Button
	settingsBack.setFont(mainFont);
	settingsBack.setString("Press B to go back to Main Menu");
	settingsBack.setCharacterSize(50);
	settingsBack.setColor(Color::White);
	settingsBack.setPosition(Vector2f(220, 700));
}

void settingsmenu::draw(RenderWindow& window) {
	window.draw(settingsTitle);
	window.draw(settingsStatus);
	window.draw(settingsBack);
}
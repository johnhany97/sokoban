#include "mainmenu.h"
using namespace sf;

mainmenu::mainmenu()
{
	//Load Default Font
	mainFont.loadFromFile("Grinched.ttf");

	//Title
	mainTitle.setFont(mainFont);
	mainTitle.setString("Sokoban");
	mainTitle.setCharacterSize(200);
	mainTitle.setColor(Color::Blue);
	mainTitle.setPosition(Vector2f(230, 100));

	//Play Button
	mainPlay.setFont(mainFont);
	mainPlay.setString("Play (P)");
	mainPlay.setCharacterSize(80);
	mainPlay.setColor(Color::White);
	mainPlay.setPosition(Vector2f(380, 500));

	//Settings Button
	mainSettings.setFont(mainFont);
	mainSettings.setString("Settings (S)");
	mainSettings.setCharacterSize(80);
	mainSettings.setColor(Color::White);
	mainSettings.setPosition(Vector2f(330, 700));
}

void mainmenu::draw(RenderWindow& window) {
	window.draw(mainTitle);
	window.draw(mainPlay);
	window.draw(mainSettings);
}
/*
	John Ayad, 900150853
	Monica Fahmy, 900142228
	Youssef Ibrahim, 900142576
	All Rights Reserved.

	CS110 - Spring 2016 - Dr. Howaida Ismail
	Sokoban
*/
#include <iostream>
#include "cell.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

//Global Definitions
#define SCRWIDTH 950
#define SCRHEIGHT 950
#define CELLSIZE 50

//Global Variables
RenderWindow window(VideoMode(SCRWIDTH, SCRHEIGHT), "Sokoban - Hackarz Version"); //SFML Window
cell A[15][15];
Font mainFont;
//MainMenu
Text mainTitle, mainPlay, mainSettings;
//SettingsMenu
Text settingsTitle, settingsStatus, settingsBack;
int status = 0; //0 for mainmenu, 1 for game, 2 for settings

//Prototypes
void initialize();
void mainMenu();
void settingsMenu();

//Functions
int main() {
	mainMenu();
	settingsMenu();
	initialize();
	while (window.isOpen()){
		Event event;
		while (window.pollEvent(event)) {
			switch (status) {
			case 0: //MainMenu
				if (Keyboard::isKeyPressed(Keyboard::P)) {
					status = 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::S)) {
					status = 2;
				}
				break;
			case 1: //Game
				break;
			case 2: //Settings
				if (Keyboard::isKeyPressed(Keyboard::B)) {
					status = 0;
					//mainMenu();
				}
				break;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed)
				window.close();
		}
		window.clear();
		switch (status) {
		case 0: //MainMenu
			window.draw(mainTitle);
			window.draw(mainPlay);
			window.draw(mainSettings);
			break;
		case 1: //Game
			break;
		case 2: //Settings
			window.draw(settingsTitle);
			window.draw(settingsStatus);
			window.draw(settingsBack);
			break;
		}
		window.display();
		window.setFramerateLimit(30);
	}

	system("pause");
	return 0;
}

void initialize() {
	/*
		Function to initialize everything
	*/
	
}

void mainMenu() {
	//Load MainFont
	mainFont.loadFromFile("Grinched.ttf");

	//Title
	mainTitle.setFont(mainFont);
	mainTitle.setString("Sokoban");
	mainTitle.setCharacterSize(200);
	mainTitle.setColor(sf::Color::Blue);
	mainTitle.setPosition(sf::Vector2f(230, 100));

	//Play Button
	mainPlay.setFont(mainFont);
	mainPlay.setString("Play (P)");
	mainPlay.setCharacterSize(80);
	mainPlay.setColor(sf::Color::White);
	mainPlay.setPosition(sf::Vector2f(380, 500));

	//Settings Button
	mainSettings.setFont(mainFont);
	mainSettings.setString("Settings (S)");
	mainSettings.setCharacterSize(80);
	mainSettings.setColor(sf::Color::White);
	mainSettings.setPosition(sf::Vector2f(330, 700));
}

void settingsMenu() {
	//Load MainFont
	mainFont.loadFromFile("Grinched.ttf");

	//Settings Title
	settingsTitle.setFont(mainFont);
	settingsTitle.setString("Settings");
	settingsTitle.setCharacterSize(80);
	settingsTitle.setColor(sf::Color::Magenta);
	settingsTitle.setPosition(sf::Vector2f(370, 100));

	//Settings Status **TEMPORARY**
	settingsStatus.setFont(mainFont);
	settingsStatus.setString("NoThInG to SeE hEre :P");
	settingsStatus.setCharacterSize(80);
	settingsStatus.setColor(sf::Color::White);
	settingsStatus.setPosition(sf::Vector2f(180, 450));

	//Settings Back Button
	settingsBack.setFont(mainFont);
	settingsBack.setString("Press B to go back to Main Menu");
	settingsBack.setCharacterSize(50);
	settingsBack.setColor(sf::Color::White);
	settingsBack.setPosition(sf::Vector2f(220, 700));
}
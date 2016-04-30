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
#include "level.h"
#include <SFML/Graphics.hpp>
#include <string>

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
//Game
RectangleShape gameBG;
//LevelChooser
Text levelChoose, levelIP, levelWarning;
bool warning = false;
string s = "";
//MasterSwitch
int status = 0; //0 for mainmenu, 1 for game, 2 for settings, 3 for level chooser
int range = 0; //Number of levels we have

//Prototypes
void initialize();
void mainMenu();
void settingsMenu();
void levelChooser();
void textAligner(Text&);

//Functions
int main() {
	mainMenu();
	settingsMenu();
	initialize();
	levelChooser();
	while (window.isOpen()){
		Event event;
		while (window.pollEvent(event)) {
			switch (status) {
			case 0: //MainMenu
				if (Keyboard::isKeyPressed(Keyboard::P)) {
					status = 3;
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
				}
				break;
			case 3: //LevelChooser
				if (event.type == sf::Event::TextEntered) {
					if (Keyboard::isKeyPressed(Keyboard::BackSpace) && s.length() != 0) {
						s.pop_back();
						levelIP.setString(s);
						textAligner(levelIP);
					}
					else if (event.text.unicode < 58 && event.text.unicode > 47) {
						s.push_back((char)event.text.unicode);
						levelIP.setString(s);
						textAligner(levelIP);
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Return)) {
					int level = stoi(s);
					if (level <= range && level > 0) {
						//Level Input is within range
						status = 1;
						//Initialize Level
					}
					else { //Level Input out of range
						warning = true;
					}
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
			window.draw(gameBG);
			break;
		case 2: //Settings
			window.draw(settingsTitle);
			window.draw(settingsStatus);
			window.draw(settingsBack);
			break;
		case 3: //LevelChooser
			window.draw(levelChoose);
			window.draw(levelIP);
			if (warning)
				window.draw(levelWarning);
			break;
		}
		window.display();
		window.setFramerateLimit(30);
	}

	system("pause");
	return 0;
}

void initialize() {
	//Game background
	Color background(7, 118, 118);
	gameBG.setFillColor(background);
	gameBG.setPosition(0, 0);
	gameBG.setSize(Vector2f(SCRWIDTH, SCRHEIGHT));

	//Level
}

void levelChooser() {
	//Load MainFont
	mainFont.loadFromFile("Grinched.ttf");

	//ChooseLevel Text
	levelChoose.setFont(mainFont);
	levelChoose.setString("Enter Level:");
	levelChoose.setCharacterSize(200);
	levelChoose.setColor(Color::Blue);
	levelChoose.setPosition(Vector2f(90, 100));

	//LevelInput
	levelIP.setFont(mainFont);
	levelIP.setString("");
	levelIP.setCharacterSize(60);
	levelIP.setColor(Color::White);
	textAligner(levelIP);

	//Warning
	levelWarning.setFont(mainFont);
	levelWarning.setString("Entered Level is Incorrect");
	levelWarning.setCharacterSize(50);
	levelWarning.setColor(Color::Red);
	levelWarning.setPosition(Vector2f(260, 600));
}

void mainMenu() {
	//Load MainFont
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

void settingsMenu() {
	//Load MainFont
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

void textAligner(Text& text) {
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(Vector2f(SCRWIDTH / 2.0f, SCRHEIGHT / 2.0f));
}
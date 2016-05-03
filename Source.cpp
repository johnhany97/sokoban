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
cell map1A[15][15], map1B[15][15], map2[20][20];
Font mainFont;
//MainMenu
Text mainTitle, mainPlay, mainSettings;
//SettingsMenu
Text settingsTitle, settingsStatus, settingsBack;
//Game
RectangleShape gameBG;
int playerLocX, playerLocY;
//LevelChooser
Text levelChoose, levelIP, levelWarning;
bool warning = false;
string s = "";
int counter = 0;
//MasterSwitch
int status = 0; //0 for mainmenu, 1 for game, 2 for settings, 3 for level chooser
int range = 10; //Number of levels we have
int rangeChars = 5; //Number of characters a user is allowed to enter

//Prototypes
void initialize();
void mainMenu();
void settingsMenu();
void levelChooser();
void textAligner(Text&);
void levelInitalize(level&, int);
bool valideMove(int);
bool NextIsBox(int);
void boxer();

//Directions Arrays
// UP , DOWN , LEFT , RIGHT
int Dy[] = { -1, 1, 0, 0 };
int Dx[] = { 0, 0, -1, 1 };

//Functions
int main() {
	Image icon;
	icon.loadFromFile("HackarzIcon.png");
	window.setIcon(50, 50, icon.getPixelsPtr());
	mainMenu();
	settingsMenu();
	initialize();
	levelChooser();
	window.setKeyRepeatEnabled(false);
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
			case 1: //Game //TODO: ASSUMING WE ONLY HAVE ONE MAP FOR NOW WHICH IS map1 //DOESN'T WORK
				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					if (valideMove(3))
					{
						if (NextIsBox(3)) {
							swap(map1B[playerLocY][playerLocX + 1], map1B[playerLocY][playerLocX + 2]);
						}
						swap(map1B[playerLocY][playerLocX], map1B[playerLocY][playerLocX + 1]);
						playerLocX++;
					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left)) {
					if (valideMove(2))
					{
						if (NextIsBox(2)) {
							swap(map1B[playerLocY][playerLocX - 1], map1B[playerLocY][playerLocX - 2]);
						}
						swap(map1B[playerLocY][playerLocX], map1B[playerLocY][playerLocX - 1]);
						playerLocX--;
					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::Up)) {
					if (valideMove(0))
					{
						if (NextIsBox(0)) {
							swap(map1B[playerLocY - 1][playerLocX], map1B[playerLocY - 2][playerLocX]);
						}
						swap(map1B[playerLocY][playerLocX], map1B[playerLocY - 1][playerLocX]);
						playerLocY--;
					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down)) {
					if (valideMove(1))
					{
						if (NextIsBox(1)) {
							swap(map1B[playerLocY + 1][playerLocX], map1B[playerLocY + 2][playerLocX]);
						}
						swap(map1B[playerLocY][playerLocX], map1B[playerLocY + 1][playerLocX]);
						playerLocY++;
					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::X)) {
					for (int i = 0; i < 15; i++) {
						for (int j = 0; j < 15; j++) {
							cout << map1A[i][j].getType() << " ";
						}cout << endl;
					}
					cout << endl;
					for (int i = 0; i < 15; i++) {
						for (int j = 0; j < 15; j++) {
							cout << map1B[i][j].getType() << " ";
						}cout << endl;
					}
				}
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
						counter--;
						if (counter <= rangeChars)
							warning = false;
					}
					else if (event.text.unicode < 58 && event.text.unicode > 47 && counter <= rangeChars) {
						s.push_back((char)event.text.unicode);
						levelIP.setString(s);
						textAligner(levelIP);
						counter++;
					}
					else if (counter > rangeChars)
						warning = true;
				}
				if (Keyboard::isKeyPressed(Keyboard::Return)) {
					int levelN = stoi(s);
					if (levelN <= range && levelN > 0) {
						//Level Input is within range
						status = 1;
						//Initialize Level
						level currentLevel;
						levelInitalize(currentLevel, levelN);
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
			boxer();
			//TEMP: Only draw Map1
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 15; j++) {
					map1A[i][j].draw(window);
				}
			}
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 15; j++) {
					map1B[i][j].draw(window);
				}
			}
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

void levelInitalize(level& currentLevel, int N) {
	if (N <= 20) //Assuming here that our first 20 levels are only 15 x 15 
	{
		currentLevel.setSize(15, 15);
		currentLevel.initialize(N);
		int initialX = 50, initialY = 100;
		for (int i = 0; i < 15; i++) {
			initialX = 50;
			for (int j = 0; j < 15; j++) {
				switch (currentLevel.getContent(i, j))
				{
				case 0: //Empty
					map1A[i][j].setType(0);
					map1A[i][j].initialize();
					map1A[i][j].setPosition(initialX, initialY);
					map1B[i][j].setType(5);
					map1B[i][j].initialize();
					map1B[i][j].setPosition(initialX, initialY);
					break;
				case 1: //Wall
					map1A[i][j].setType(1);
					map1A[i][j].initialize();
					map1A[i][j].setPosition(initialX, initialY);
					map1B[i][j].setType(5);
					map1B[i][j].initialize();
					map1B[i][j].setPosition(initialX, initialY);
					break;
				case 2: //Goal
					map1A[i][j].setType(2);
					map1A[i][j].initialize();
					map1A[i][j].setPosition(initialX, initialY);
					map1B[i][j].setType(5);
					map1B[i][j].initialize();
					map1B[i][j].setPosition(initialX, initialY);
					break;
				case 3: //Box
					map1A[i][j].setType(0);
					map1A[i][j].initialize();
					map1A[i][j].setPosition(initialX, initialY);
					map1B[i][j].setType(3);
					map1B[i][j].initialize();
					map1B[i][j].setPosition(initialX, initialY);
					break;
				case 4: //Player
					map1A[i][j].setType(0);
					map1A[i][j].initialize();
					map1A[i][j].setPosition(initialX, initialY);
					map1B[i][j].setType(4);
					map1B[i][j].initialize();
					map1B[i][j].setPosition(initialX, initialY);
					playerLocX = j;
					playerLocY = i;
					break;
				case 5: //Box on Goal
					map1A[i][j].setType(2);
					map1A[i][j].initialize();
					map1A[i][j].setPosition(initialX, initialY);
					map1B[i][j].setType(6);
					map1B[i][j].initialize();
					map1B[i][j].setPosition(initialX, initialY);
					break;
				case 6: //Player on Goal
					map1A[i][j].setType(2);
					map1A[i][j].initialize();
					map1A[i][j].setPosition(initialX, initialY);
					map1B[i][j].setType(4);
					map1B[i][j].initialize();
					map1B[i][j].setPosition(initialX, initialY);
					playerLocX = j;
					playerLocY = i;
					break;
				default: //S P A C E
					map1B[i][j].setType(5);
					map1B[i][j].initialize();
					map1B[i][j].setPosition(initialX, initialY);
				}
				initialX += 50;
			}
			initialY += 50;
			initialX = 50;
		}
	}
}

bool valideMove(int direction)
{
	int x1 = playerLocX + Dx[direction]; //one in x
	int y1 = playerLocY + Dy[direction]; // one in y
	int x2 = playerLocX + (2 * Dx[direction]); // 2 in X
	int y2 = playerLocY + (2 * Dy[direction]);  // 2 in y

	if ((map1A[y1][x1].getType() == 1) || //Next is wall
		(map1B[y1][x1].getType() == 3 && map1B[y2][x2].getType() == 6) || //Next and afternext, box
		(map1B[y1][x1].getType() == 6 && map1B[y2][x2].getType() == 6) || //Next and afternext, box
		(map1B[y1][x1].getType() == 6 && map1B[y2][x2].getType() == 3) || //Next and afternext, box
		(map1B[y1][x1].getType() == 3 && map1B[y2][x2].getType() == 3) || //Next and afternext, box
		(map1B[y1][x1].getType() == 3 && map1A[y2][x2].getType() == 1) || //Next is box, afternext is wall
		(map1B[y1][x1].getType() == 6 && map1A[y2][x2].getType() == 1))   //Next is box, afternext is wall
		return false;
	return true;
}

bool NextIsBox(int direction)
{
	int x1 = playerLocX + Dx[direction]; //one in x
	int y1 = playerLocY + Dy[direction]; //one in y

	return (map1B[y1][x1].getType() == 3 || map1B[y1][x1].getType() == 6);
}

void boxer() {
	//MAP 1 ONLY SO FAR
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (map1A[i][j].getType() == 2 && map1B[i][j].getType() == 3) {
				map1B[i][j].setType(6);
				map1B[i][j].initialize();
				map1B[i][j].setPosition((j*50)+50, (i*50)+100);
			}
			if (map1A[i][j].getType() != 2 && map1B[i][j].getType() == 6) {
				map1B[i][j].setType(3);
				map1B[i][j].initialize();
				map1B[i][j].setPosition((j * 50) + 50, (i * 50) + 100);
			}
		}
	}
}
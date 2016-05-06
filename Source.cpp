/*
	John Ayad, 900150853
	Monica Fahmy, 900142228
	Youssef Ibrahim, 900142576
	All Rights Reserved.

	CS110 - Spring 2016 - Dr. Howaida Ismail
	Sokoban
*/
#include <iostream>
#include "variables.h"
#include "cell.h"
#include "level.h"
#include "mainmenu.h"
#include "settingsmenu.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

//Global Variables
RenderWindow window(VideoMode(SCRWIDTH, SCRHEIGHT), "Sokoban - Hackarz Version"); //SFML Window
Font mainFont;
mainmenu mmenu;
settingsmenu smenu;

//Prototypes
void initialize();
void levelChooser();
void levelInitalize(level&, int);
bool valideMove(int);
bool NextIsBox(int);
void boxer();
bool gameWin();
void textAligner(Text&);

//Functions
int main() {
	Image icon;
	icon.loadFromFile("HackarzIcon.png");
	window.setIcon(50, 50, icon.getPixelsPtr());
	initialize();
	levelChooser();
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(30);
	while (window.isOpen()){
		Event event;
		while (window.pollEvent(event)) {
			switch (status) {
			case 0: //MainMenu
				if (Keyboard::isKeyPressed(Keyboard::P) || mmenu.mousePress(0, window)) {
					status = 3;
				}
				if (Keyboard::isKeyPressed(Keyboard::S) || mmenu.mousePress(1, window)) {
					status = 2;
				}
				if (Keyboard::isKeyPressed(Keyboard::V) || mmenu.mousePress(2, window)) {
					mmenu.volumePressed(sound);
				}
				break;
			case 1: //Game
				if (!levelWon) {
					if (Keyboard::isKeyPressed(Keyboard::Right)) {
						if (valideMove(3))
						{
							if (NextIsBox(3)) {
								swap(map1B[playerLocY][playerLocX + 1], map1B[playerLocY][playerLocX + 2]);
								map1B[playerLocY][playerLocX + 1].setType(5);
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
								map1B[playerLocY][playerLocX - 1].setType(5);
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
								map1B[playerLocY - 1][playerLocX].setType(5);
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
								map1B[playerLocY + 1][playerLocX].setType(5);
							}
							swap(map1B[playerLocY][playerLocX], map1B[playerLocY + 1][playerLocX]);
							playerLocY++;
						}
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
					else if (counter > rangeChars || counter == 0)
						warning = true;
				}
				if (Keyboard::isKeyPressed(Keyboard::Return) && counter > 0) {
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
			mmenu.draw(window);
			break;
		case 1: //Game
			window.draw(gameBG);
			boxer();
			//TEMP: Only draw Map1
			for (int i = 0; i < 17; i++) {
				for (int j = 0; j < 17; j++) {
					map1A[i][j].draw(window);
				}
			}
			for (int i = 0; i < 17; i++) {
				for (int j = 0; j < 17; j++) {
					map1B[i][j].draw(window);
				}
			}
			if (gameWin()) {
				window.draw(gameWinSplash);
				levelWon = true;
			}
			break;
		case 2: //Settings
			smenu.draw(window);
			break;
		case 3: //LevelChooser
			window.draw(levelChoose);
			window.draw(levelIP);
			if (warning)
				window.draw(levelWarning);
			break;
		}
		window.display();
	}
	system("pause");
	return 0;
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

void initialize() {
	//Game background
	Color background(7, 118, 118);
	gameBG.setFillColor(background);
	gameBG.setPosition(0, 0);
	gameBG.setSize(Vector2f(SCRWIDTH, SCRHEIGHT));

	//Load MainFont
	mainFont.loadFromFile("Grinched.ttf");

	//Game Won
	gameWinText.setFont(mainFont);
	gameWinText.setString("YOU WON!!");
	gameWinText.setCharacterSize(50);
	gameWinText.setColor(Color::White);
	gameWinText.setPosition(Vector2f((SCRHEIGHT/2) - 100, 0));

	//Game Won Sprite
	gameWinSplashTexture.loadFromFile("images/win.jpg");
	if (!gameWinSplashTexture.loadFromFile("images/win.jpg"))
	{
		std::cout << "Failed to load win splash spritesheet!" << std::endl;
	}
	gameWinSplash.setTexture(gameWinSplashTexture);
	gameWinSplash.setPosition(Vector2f(0, 0));
}

void levelInitalize(level& currentLevel, int N) {
	currentLevel.setSize(17, 17);
	currentLevel.initialize(N);
	int initialX = 0, initialY = 100;
	for (int i = 0; i < 17; i++) {
		initialX = 50;
		for (int j = 0; j < 17; j++) {
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
		initialX = 0;
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
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 17; j++) {
			if (map1A[i][j].getType() == 2 && map1B[i][j].getType() == 3) {
				map1B[i][j].switcher(1);
				map1B[i][j].setType(6);
			}
			else if (map1A[i][j].getType() != 2 && map1B[i][j].getType() == 6) {
				map1B[i][j].setType(3);
				map1B[i][j].switcher(0);
			}
		}
	}
}

bool gameWin() {
	bool flag1 = true;
	//TODO MAP1 SO FAR
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 17; j++) {
			if (map1B[i][j].getType() == 3)
				flag1 = false;
		}
	}
	return flag1;
}

void textAligner(Text& text) {
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(Vector2f(SCRWIDTH / 2.0f, SCRHEIGHT / 2.0f));
}
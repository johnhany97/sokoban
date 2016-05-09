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
bool mousePress(int);

//Functions
int main() {
	Image icon;
	icon.loadFromFile("HackarzIcon.png");
	window.setIcon(50, 50, icon.getPixelsPtr());
	initialize();
	levelChooser();
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(30);

	Clock win_clock;
	bool win_pic = true;
	while (window.isOpen()){
		Event event;
		while (window.pollEvent(event)) {
			switch (status) {
			case 0: //MainMenu
				if (mmenu.mousePress(0, window)) { //Play button pressed
					status = 3;
				}
				if (mmenu.mousePress(1, window)) { //Settings button pressed
					status = 2;
				}
				if (mmenu.mousePress(2, window)) { //Volume button pressed
					mmenu.volumePressed(sound);
				}
				break;
			case 1: //Game
				if (!levelWon) {
					if (Keyboard::isKeyPressed(Keyboard::Right)) {
						if (valideMove(3))
						{
							if (player.move(3)) {
								if (NextIsBox(3)) {
									swap(map1B[playerLocY][playerLocX + 1], map1B[playerLocY][playerLocX + 2]);
									map1B[playerLocY][playerLocX + 1].setType(5);
									pushLeft--;
								}
								//swap(map1B[playerLocY][playerLocX], map1B[playerLocY][playerLocX + 1]);

								playerLocX++;
							}
						}
						//map1B[playerLocY][playerLocX].playerDir(1);
					}
					else if (Keyboard::isKeyPressed(Keyboard::Left)) {
						if (valideMove(2))
						{
							if(player.move(2)){
								if (NextIsBox(2)) {
									swap(map1B[playerLocY][playerLocX - 1], map1B[playerLocY][playerLocX - 2]);
									map1B[playerLocY][playerLocX - 1].setType(5);
									pushLeft--;
								}

								//swap(map1B[playerLocY][playerLocX], map1B[playerLocY][playerLocX - 1]);
								playerLocX--;
							}
						}
						//map1B[playerLocY][playerLocX].playerDir(0);
					}
					else if (Keyboard::isKeyPressed(Keyboard::Up)) {
						if (valideMove(0))
						{
							if (player.move(0)) {
								if (NextIsBox(0)) {
									swap(map1B[playerLocY - 1][playerLocX], map1B[playerLocY - 2][playerLocX]);
									map1B[playerLocY - 1][playerLocX].setType(5);
									pushLeft--;
								}
								playerLocY--;
							}
							
							//swap(map1B[playerLocY][playerLocX], map1B[playerLocY - 1][playerLocX]);
							
						}
						//map1B[playerLocY][playerLocX].playerDir(2);
					}
					else if (Keyboard::isKeyPressed(Keyboard::Down)) {
						if (valideMove(1))
						{
							if (player.move(1)) {
								if (NextIsBox(1)) {
									swap(map1B[playerLocY + 1][playerLocX], map1B[playerLocY + 2][playerLocX]);
									map1B[playerLocY + 1][playerLocX].setType(5);
									pushLeft--;
								}
								//swap(map1B[playerLocY][playerLocX], map1B[playerLocY + 1][playerLocX]);
								playerLocY++;
							}
						}
						//map1B[playerLocY][playerLocX].playerDir(3);
					}
					else if (Keyboard::isKeyPressed(Keyboard::X)) {
						for (int i = 0; i < 17; i++) {
							for (int j = 0; j < 17; j++) {
								cout << map1B[i][j].getType() << " ";
							}cout << endl;
						}
						cout << endl << endl << endl;
					}
					else if (mousePress(2)) { //Restart button
						//Initialize Level
						level currentLevel;
						levelInitalize(currentLevel, levelN);
					}
					else if (mousePress(3)) { //Home button
						status = 0;
						s = "";
						counter = 0;
						warning = false;
						flag = false;
						levelWon = false;
						gameFinished = false;
						gameWinHome.setPosition(Vector2f(70, 810));
						//Clear maps
						for (int i = 0; i < 17; i++) {
							for (int j = 0; j < 17; j++) {
								map1A[i][j].setType(6);
								map1B[i][j].setType(6);
							}
						}
						levelIP.setString("");
					}
					else if (mousePress(4)) { //Undo button
						cout << "Hi, I will undo what you just did in the future :)" << endl;
					}
				}
				else if (mousePress(0)) { //Next Button
					levelN++;
					if (levelN > range) gameFinished = true;
					if (levelN <= range) {
						levelWon = false;
						flag = false;
						//Initialize Level
						for (int i = 0; i < 17; i++) {
							for (int j = 0; j < 17; j++) {
								map1A[i][j].setType(5);
								map1A[i][j].initialize();
								map1B[i][j].setType(5);
								map1B[i][j].initialize();
							}
						}
						level currentLevel;
						levelInitalize(currentLevel, levelN);
					} else { //Level out of range
						//We should announce that he finished the game
						gameFinished = true;
						Image temp;
						temp.loadFromFile("images/game_finished.png");
						gameWinSplashTexture.update(temp);
					}
				}
				else if (mousePress(1)) { //Home Button
					status = 0;
					s = "";
					counter = 0;
					warning = false;
					flag = false;
					levelWon = false;
					gameFinished = false;
					gameWinHome.setPosition(Vector2f(70, 810));
					//Clear maps
					for (int i = 0; i < 17; i++) {
						for (int j = 0; j < 17; j++) {
							map1A[i][j].setType(6);
							map1B[i][j].setType(6);
							map1A[i][j].initialize();
							map1B[i][j].initialize();
						}
					}
					levelIP.setString("");
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
					levelN = stoi(s);
					if (levelN <= range && levelN > 0) {
						//Level Input is within range
						status = 1;
						//Initialize Level
						for (int i = 0; i < 17; i++) {
							for (int j = 0; j < 17; j++) {
								map1A[i][j].setType(5);
								map1A[i][j].initialize();
								map1B[i][j].setType(5);
								map1B[i][j].initialize();
							}
						}
						level currentLevel;
						levelInitalize(currentLevel, levelN);
					}
					else { //Level Input out of range
						warning = true;
						gameWinHome.setPosition(Vector2f(332, 810));
					}
				}
				break;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed)
				window.close();
		}
		if (win_clock.getElapsedTime().asSeconds() > 0.3f && !gameFinished) {
			if (win_pic) {
				Image img;
				img.loadFromFile("images/game_win_2.png");
				gameWinSplashTexture.update(img);
				win_pic = false;
				win_clock.restart();
			}
			else {
				Image img;
				img.loadFromFile("images/game_win.png");
				gameWinSplashTexture.update(img);
				win_pic = true;
				win_clock.restart();
			}
		}
		player.update();


		window.clear();
		switch (status) {
		case 0: //MainMenu
			mmenu.draw(window);
			break;
		case 1: //Game
			window.draw(gameBG);
			boxer();
			for (int i = 0; i < 17; i++) {
				for (int j = 0; j < 17; j++) {
					map1A[i][j].draw(window);
				}
			}
			player.draw(window);
			for (int i = 0; i < 17; i++) {
				for (int j = 0; j < 17; j++) {
						map1B[i][j].draw(window);
				}
			}

			window.draw(undoButton);
			window.draw(restartButton);
			window.draw(homeButton);
			if (gameFinished) {
				window.draw(gameWinSplash);
				window.draw(gameWinHome);
				levelWon = true;
			}
			else if (gameWin() && !gameFinished) {
				window.draw(gameWinSplash);
				window.draw(gameWinHome);
				window.draw(gameWinNext);
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
	mainFont.loadFromFile("arcade.ttf");

	//ChooseLevel Text
	levelChoose.setFont(mainFont);
	levelChoose.setString("Enter  Level");
	levelChoose.setCharacterSize(120);
	levelChoose.setColor(Color::Blue);
	levelChoose.setPosition(Vector2f(130, 100));

	//LevelInput
	levelIP.setFont(mainFont);
	levelIP.setString("");
	levelIP.setCharacterSize(60);
	levelIP.setColor(Color::White);
	textAligner(levelIP);

	//Warning
	levelWarning.setFont(mainFont);
	levelWarning.setString("Entered  Level is Incorrect");
	levelWarning.setCharacterSize(50);
	levelWarning.setColor(Color::Red);
	levelWarning.setPosition(Vector2f(140, 600));
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
	gameWinText.setPosition(Vector2f((SCRHEIGHT / 2) - 100, 0));


	//Game Won Sprite
	gameWinSplashTexture.loadFromFile("images/game_win.png");
	if (!gameWinSplashTexture.loadFromFile("images/game_win.png"))
	{
		std::cout << "Failed to load win splash spritesheet!" << std::endl;
	}
	gameWinSplash.setTexture(gameWinSplashTexture);
	gameWinSplash.setPosition(Vector2f(0, 0));

	//Next button
	gameWinNextTexture.loadFromFile("images/next_button.png");
	if (!gameWinNextTexture.loadFromFile("images/next_button.png"))
	{
		std::cout << "Failed to load next button spritesheet!" << std::endl;
	}
	gameWinNext.setTexture(gameWinNextTexture);
	gameWinNext.setPosition(Vector2f(590, 810));

	//Home button
	gameWinHomeTexture.loadFromFile("images/home_button.png");
	if (!gameWinHomeTexture.loadFromFile("images/home_button.png"))
	{
		std::cout << "Failed to load home button spritesheet!" << std::endl;
	}
	gameWinHome.setTexture(gameWinHomeTexture);
	gameWinHome.setPosition(Vector2f(70, 810));

	//undo Button (in game)
	undoButtonTexture.loadFromFile("sprites/undo.png");
	if (!undoButtonTexture.loadFromFile("sprites/undo.png"))
	{
		std::cout << "Failed to load undo button spritesheet!" << std::endl;
	}
	undoButton.setTexture(undoButtonTexture);
	undoButton.setPosition(Vector2f(1, 937));

	//home Button (in game)
	homeButtonTexture.loadFromFile("sprites/home.png");
	if (!homeButtonTexture.loadFromFile("sprites/home.png"))
	{
		std::cout << "Failed to load home button spritesheet!" << std::endl;
	}
	homeButton.setTexture(homeButtonTexture);
	homeButton.setPosition(Vector2f(445, 937));

	//restart Button (in game)
	restartButtonTexture.loadFromFile("sprites/restart.png");
	if (!restartButtonTexture.loadFromFile("sprites/restart.png"))
	{
		std::cout << "Failed to load restart button spritesheet!" << std::endl;
	}
	restartButton.setTexture(restartButtonTexture);
	restartButton.setPosition(Vector2f(888, 937));

}

void levelInitalize(level& currentLevel, int N) {
	currentLevel.setSize(17, 17);
	currentLevel.empty();
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
				map1B[i][j].setType(5);
				map1B[i][j].initialize();
				map1B[i][j].setPosition(initialX, initialY);
				player.setType(4);
				player.initialize();
				player.setPosition(initialX, initialY);
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
				map1B[i][j].setType(5);
				map1B[i][j].initialize();
				map1B[i][j].setPosition(initialX, initialY);
				player.setType(4);
				player.initialize();
				player.setPosition(initialX, initialY);
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
	pushLeft = currentLevel.getPush();
	currentLevel.print();
	cout << endl;
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

bool mousePress(int spriteNo) {
	int mouseX = Mouse::getPosition().x;
	int mouseY = Mouse::getPosition().y;

	Vector2i windowPosition = window.getPosition();

	switch (spriteNo) {
	case 0: //Next Button
		if (mouseX > gameWinNext.getPosition().x + windowPosition.x && mouseX < (gameWinNext.getPosition().x + gameWinNext.getGlobalBounds().width + windowPosition.x)
			&& mouseY > gameWinNext.getPosition().y + windowPosition.y + 30 && mouseY < (gameWinNext.getPosition().y + gameWinNext.getGlobalBounds().height + windowPosition.y + 30)) {
			if (Mouse::isButtonPressed(Mouse::Left))
				return true;
			return false;
		}
		break;
	case 1: //Home Button
		if (mouseX > gameWinHome.getPosition().x + windowPosition.x && mouseX < (gameWinHome.getPosition().x + gameWinHome.getGlobalBounds().width + windowPosition.x)
			&& mouseY > gameWinHome.getPosition().y + windowPosition.y + 30 && mouseY < (gameWinHome.getPosition().y + gameWinHome.getGlobalBounds().height + windowPosition.y + 30)) {
			if (Mouse::isButtonPressed(Mouse::Left))
				return true;
			return false;
		}
		break;
	case 2: //In game restart button
		if (mouseX > restartButton.getPosition().x + windowPosition.x && mouseX < (restartButton.getPosition().x + restartButton.getGlobalBounds().width + windowPosition.x)
			&& mouseY > restartButton.getPosition().y + windowPosition.y + 70 && mouseY < (restartButton.getPosition().y + restartButton.getGlobalBounds().height + windowPosition.y + 70)) {
			if (Mouse::isButtonPressed(Mouse::Left))
				return true;
			return false;
		}
		break;
	case 3: //In game Home button
		if (mouseX > homeButton.getPosition().x + windowPosition.x && mouseX < (homeButton.getPosition().x + homeButton.getGlobalBounds().width + windowPosition.x)
			&& mouseY > homeButton.getPosition().y + windowPosition.y + 70 && mouseY < (homeButton.getPosition().y + homeButton.getGlobalBounds().height + windowPosition.y + 70)) {
			if (Mouse::isButtonPressed(Mouse::Left))
				return true;
			return false;
		}
		break;
	case 4: //In game undo button
		if (mouseX > undoButton.getPosition().x + windowPosition.x && mouseX < (undoButton.getPosition().x + undoButton.getGlobalBounds().width + windowPosition.x)
			&& mouseY > undoButton.getPosition().y + windowPosition.y + 70 && mouseY < (undoButton.getPosition().y + undoButton.getGlobalBounds().height + windowPosition.y + 70)) {
			if (Mouse::isButtonPressed(Mouse::Left))
				return true;
			return false;
		}
		break;
	}
	return false;
}
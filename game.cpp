/*
	John Ayad, 900150853
	Monica Fahmy, 900142228
	Youssef Ibrahim, 900142576
	All Rights Reserved.

	CS110 - Spring 2016 - Dr. Howaida Ismail
	Sokoban
*/
#include "game.h"
#include "variables.h"

game::game()
{
	window = new RenderWindow(VideoMode(SCRWIDTH, SCRHEIGHT), "Sokoban - Hackarz Version"); //SFML Window

	icon.loadFromFile("HackarzIcon.png");
	window->setIcon(50, 50, icon.getPixelsPtr());
	window->setKeyRepeatEnabled(false);
	window->setFramerateLimit(60);

	bgMusic.play();

	initialize();
	levelChooser();

}

void game::render() {
	window->clear();
	switch (status) {
	case 0: //MainMenu
		mmenu.draw(*window);
		break;
	case 1: //Game
		window->draw(gameBG);
		boxUpdate();
		for (int i = 0; i < 17; i++) {
			for (int j = 0; j < 17; j++) {
				map1A[i][j].draw(*window);
			}
		}
		player.draw(*window);
		for (int i = 0; i < 17; i++) {
			for (int j = 0; j < 17; j++) {
				map1B[i][j].draw(*window);
			}
		}
		counterText.setString("PUSHES  LEFT  ARE  " + to_string(pushLeft + 1));
		if (!infinityModeToggle)
			window->draw(counterText);
		window->draw(undoButton);
		window->draw(restartButton);
		window->draw(homeButton);
		if (gameFinished) {
			window->draw(gameWinSplash);
			window->draw(gameWinHome);
			levelWon = true;
		}
		else if ((gameWin(0, 0) || levelWon) && !gameFinished) {
			window->draw(gameWinSplash);
			window->draw(gameWinHome);
			window->draw(gameWinNext);
			levelWon = true;
		}
		else if (gameover)
		{
			window->draw(gameWinSplash);
			window->draw(gameWinHome);
		}
		break;
	case 2: //Settings
		smenu.draw(*window);
		if (showTutorial) {
			smenu.showT(*window);
		}
		break;
	case 3: //LevelChooser
		window->draw(levelChoose);
		window->draw(levelIP);
		if (warning)
			window->draw(levelWarning);
		break;
	}
	window->display();
}

void game::gameLoop() {

	while (window->isOpen()) {
		Event event;
		while (window->pollEvent(event)) {
			switch (status) {
			case 0: //MainMenu
				if (mmenu.mousePress(0, *window)) { //Play button pressed
					status = 3;
				}
				if (mmenu.mousePress(1, *window)) { //Settings button pressed
					status = 2;
				}
				if (mmenu.mousePress(2, *window)) { //Volume button pressed
					mmenu.volumePressed(sound);
					bxMusic.switcher();
					bgMusic.switcher();
				}
				break;
			case 1: //Game
				if (!levelWon && !gameover) {
					if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
						cheatCode = "";
						move(3);
					}
					else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
						cheatCode = "";
						move(2);
					}
					else if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
						cheatCode = "";
						move(0);
					}
					else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
						cheatCode = "";
						move(1);
					}
					else if (event.type == Event::TextEntered) {
						if ((event.text.unicode == 106 || event.text.unicode == 74) && cheatCode.length() == 0) {
							cheatCode = "";
							cheatCode.push_back('J');
						}
						else if ((event.text.unicode == 109 || event.text.unicode == 77) && cheatCode == "J") {
							cheatCode.push_back('M');
						}
						else if ((event.text.unicode == 121 || event.text.unicode == 89) && cheatCode == "JM") {
							cheatCode.push_back('Y');
						}
						else
							cheatCode = "";
						if (cheatCode == "JMY") {
							levelWon = true;
						}
					}
					else if (mousePress(2) || Keyboard::isKeyPressed(Keyboard::R)) { //Restart button
																					 //Initialize Level
						cheatCode = "";
						level currentLevel;
						levelInitalize(currentLevel, levelN);
					}
					else if (mousePress(3) || Keyboard::isKeyPressed(Keyboard::H)) { //Home button
						cheatCode = "";
						status = 0;
						s = "";
						counter = 0;
						warning = false;
						levelWon = false;
						gameFinished = false;
						gameover = false;
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
					else if (mousePress(4) || Keyboard::isKeyPressed(Keyboard::U)) { //Undo button
						undo();
					}
					else if (Keyboard::isKeyPressed(Keyboard::F10)) {
						pushLeft++;
					}
					if (pushLeft < 0 && !infinityModeToggle)
					{
						gameover = true;
					}
				}
				else if (mousePress(0)) { //Next Button
					cheatCode = "";
					levelN++;
					if (levelN > range) gameFinished = true;
					if (levelN <= range) {
						levelWon = false;
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
					else { //Level out of range
						   //We should announce that he finished the game
						gameFinished = true;
						Image temp;
						temp.loadFromFile("images/game_finished.png");
						gameWinSplashTexture.update(temp);
					}
				}
				else if (mousePress(1)) { //Home Button
					cheatCode = "";
					status = 0;
					s = "";
					counter = 0;
					warning = false;
					levelWon = false;
					gameover = false;
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
				if (!showTutorial) {
					if (smenu.mousePress(0, *window)) { //Tutorial button pressed
						smenu.tutorialPressed(showTutorial);
						smenu.showT(*window);
					}
					if (smenu.mousePress(1, *window)) { //Home button pressed
						status = 0;
					}
					if (smenu.mousePress(2, *window)) { //Mode button pressed
						smenu.modePressed(infinityModeToggle);
					}
				}
				else if (smenu.mousePress(3, *window)) {
					showTutorial = false;
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
					}
				}
				break;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed)
				window->close();
		}
		if (win_clock.getElapsedTime().asSeconds() > 0.3f && !gameFinished && !gameover) {
			if (win_pic) {
				Image img;
				img.loadFromFile("images/game_win_2.png");
				gameWinSplashTexture.update(img);
				win_pic = false;
				win_clock.restart();
			}
			else if (!gameover && !gameFinished) {
				Image img;
				img.loadFromFile("images/game_win.png");
				gameWinSplashTexture.update(img);
				win_pic = true;
				win_clock.restart();
			}
		}
		else if (gameover)
		{
			Image img;
			img.loadFromFile("images/game_over.png");
			gameWinSplashTexture.update(img);
		}
		player.update();
		render();
	}
}

void game::levelChooser() {
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

void game::initialize() {
	//Game background
	Color background(47, 75, 110);
	gameBG.setFillColor(background);
	gameBG.setPosition(0, 0);
	gameBG.setSize(Vector2f(SCRWIDTH, SCRHEIGHT));

	//Game Won Sprite
	if (!gameWinSplashTexture.loadFromFile("images/game_win.png"))
	{
		std::cout << "Failed to load win splash spritesheet!" << std::endl;
	}
	gameWinSplash.setTexture(gameWinSplashTexture);
	gameWinSplash.setPosition(Vector2f(0, 0));

	//Next button
	if (!gameWinNextTexture.loadFromFile("images/next_button.png"))
	{
		std::cout << "Failed to load next button spritesheet!" << std::endl;
	}
	gameWinNext.setTexture(gameWinNextTexture);
	gameWinNext.setPosition(Vector2f(590, 810));

	//Home button
	if (!gameWinHomeTexture.loadFromFile("images/home_button.png"))
	{
		std::cout << "Failed to load home button spritesheet!" << std::endl;
	}
	gameWinHome.setTexture(gameWinHomeTexture);
	gameWinHome.setPosition(Vector2f(70, 810));

	//undo Button (in game)
	if (!undoButtonTexture.loadFromFile("sprites/undo.png"))
	{
		std::cout << "Failed to load undo button spritesheet!" << std::endl;
	}
	undoButton.setTexture(undoButtonTexture);
	undoButton.setPosition(Vector2f(1, 937));

	//home Button (in game)
	if (!homeButtonTexture.loadFromFile("sprites/home.png"))
	{
		std::cout << "Failed to load home button spritesheet!" << std::endl;
	}
	homeButton.setTexture(homeButtonTexture);
	homeButton.setPosition(Vector2f(445, 937));

	//restart Button (in game)
	if (!restartButtonTexture.loadFromFile("sprites/restart.png"))
	{
		std::cout << "Failed to load restart button spritesheet!" << std::endl;
	}
	restartButton.setTexture(restartButtonTexture);
	restartButton.setPosition(Vector2f(888, 937));

	//counter text (in game)
	counterFont.loadFromFile("arcade.ttf");
	counterText.setFont(counterFont);
	counterText.setCharacterSize(30);
	counterText.setPosition(Vector2f(10, 10));
	counterText.setString("PUSHES LEFT ARE " + to_string(pushLeft + 1));

}

void game::levelInitalize(level& currentLevel, int N) {
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
	pushLeft = currentLevel.getPush() + 6;
}

bool game::valideMove(int direction)
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

bool game::NextIsBox(int direction)
{
	int x1 = playerLocX + Dx[direction]; //one in x
	int y1 = playerLocY + Dy[direction]; //one in y

	return (map1B[y1][x1].getType() == 3 || map1B[y1][x1].getType() == 6);
}

void game::boxUpdate() {
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

bool game::gameWin(int i, int j) {
	if (map1B[i][j].getType() == 3) {
		return false;
	}
	else if (j < 16 && i < 17) {
		return (true && gameWin(i, j+1));
	}
	else if (j == 16 && i < 17) {
		return (true && gameWin(i + 1, 0));
	}
	else return true;
}

void game::textAligner(Text& text) {
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(Vector2f(SCRWIDTH / 2.0f, SCRHEIGHT / 2.0f));
}

bool game::mousePress(int spriteNo) {
	int mouseX = Mouse::getPosition().x;
	int mouseY = Mouse::getPosition().y;

	Vector2i windowPosition = window->getPosition();

	switch (spriteNo) {
	case 0: //Next Button
		if (mouseX > gameWinNext.getPosition().x + windowPosition.x && mouseX < (gameWinNext.getPosition().x + gameWinNext.getGlobalBounds().width + windowPosition.x)
			&& mouseY > gameWinNext.getPosition().y + windowPosition.y + 30 && mouseY < (gameWinNext.getPosition().y + gameWinNext.getGlobalBounds().height + windowPosition.y + 30)) {
			if (Mouse::isButtonPressed(Mouse::Left) && Event::MouseButtonReleased)
				return true;
			return false;
		}
		break;
	case 1: //Home Button
		if (mouseX > gameWinHome.getPosition().x + windowPosition.x && mouseX < (gameWinHome.getPosition().x + gameWinHome.getGlobalBounds().width + windowPosition.x)
			&& mouseY > gameWinHome.getPosition().y + windowPosition.y + 30 && mouseY < (gameWinHome.getPosition().y + gameWinHome.getGlobalBounds().height + windowPosition.y + 30)) {
			if (Mouse::isButtonPressed(Mouse::Left) && Event::MouseButtonReleased)
				return true;
			return false;
		}
		break;
	case 2: //In game restart button
		if (mouseX > restartButton.getPosition().x + windowPosition.x && mouseX < (restartButton.getPosition().x + restartButton.getGlobalBounds().width + windowPosition.x)
			&& mouseY > restartButton.getPosition().y + windowPosition.y + 60 && mouseY < (restartButton.getPosition().y + restartButton.getGlobalBounds().height + windowPosition.y + 60)) {
			if (Mouse::isButtonPressed(Mouse::Left) && Event::MouseButtonReleased)
				return true;
			return false;
		}
		break;
	case 3: //In game Home button
		if (mouseX > homeButton.getPosition().x + windowPosition.x && mouseX < (homeButton.getPosition().x + homeButton.getGlobalBounds().width + windowPosition.x)
			&& mouseY > homeButton.getPosition().y + windowPosition.y + 60 && mouseY < (homeButton.getPosition().y + homeButton.getGlobalBounds().height + windowPosition.y + 60)) {
			if (Mouse::isButtonPressed(Mouse::Left) && Event::MouseButtonReleased)
				return true;
			return false;
		}
		break;
	case 4: //In game undo button
		if (mouseX > undoButton.getPosition().x + windowPosition.x && mouseX < (undoButton.getPosition().x + undoButton.getGlobalBounds().width + windowPosition.x)
			&& mouseY > undoButton.getPosition().y + windowPosition.y + 60 && mouseY < (undoButton.getPosition().y + undoButton.getGlobalBounds().height + windowPosition.y + 60)) {
			if (Mouse::isButtonPressed(Mouse::Left) && Event::MouseButtonReleased)
				return true;
			return false;
		}
		break;
	}
	return false;
}

void game::undo() {
	switch (direction) {
	case 0: //Up
		if (player.move(1)) {
			if (nextWasBox) {
				swap(map1B[playerLocY][playerLocX], map1B[playerLocY - 1][playerLocX]);
				pushLeft++;
			}
			playerLocY++;
		}
		break;
	case 1: //Down
		if (player.move(0)) {
			if (nextWasBox) {
				swap(map1B[playerLocY][playerLocX], map1B[playerLocY + 1][playerLocX]);
				pushLeft++;
			}
		}
		playerLocY--;
		break;
	case 2: //Left
		if (player.move(3)) {
			if (nextWasBox) {
				swap(map1B[playerLocY][playerLocX], map1B[playerLocY][playerLocX - 1]);
				pushLeft++;
			}
		}
		playerLocX++;
		break;
	case 3:
		if (player.move(2)) {
			if (nextWasBox) {
				swap(map1B[playerLocY][playerLocX], map1B[playerLocY][playerLocX + 1]);
				pushLeft++;
			}
		}
		playerLocX--;
		break;
	}
	nextWasBox = false;
	direction = -1;
}

void game::move(int dir) {
	switch (dir) {
		case 0: //Up
			if (valideMove(0))
			{
				if (player.move(0)) {
					if (NextIsBox(0)) {
						swap(map1B[playerLocY - 1][playerLocX], map1B[playerLocY - 2][playerLocX]);
						bxMusic.play();
						map1B[playerLocY - 1][playerLocX].setType(5);
						pushLeft--;
						nextWasBox = true;
					}
					else nextWasBox = false;
					direction = 0;
					playerLocY--;
				}
			}
			break;
		case 1: //Down
			if (valideMove(1))
			{
				if (player.move(1)) {
					if (NextIsBox(1)) {
						swap(map1B[playerLocY + 1][playerLocX], map1B[playerLocY + 2][playerLocX]);
						bxMusic.play();
						map1B[playerLocY + 1][playerLocX].setType(5);
						pushLeft--;
						nextWasBox = true;
					}
					else nextWasBox = false;
					direction = 1;
					playerLocY++;
				}
			}
			break;
		case 2: //Left
			if (valideMove(2))
			{
				if (player.move(2)) {
					if (NextIsBox(2)) {
						swap(map1B[playerLocY][playerLocX - 1], map1B[playerLocY][playerLocX - 2]);
						bxMusic.play();
						map1B[playerLocY][playerLocX - 1].setType(5);
						pushLeft--;
						nextWasBox = true;
					}
					else nextWasBox = false;
					direction = 2;
					playerLocX--;
				}
			}
			break;
		case 3: //Right
			if (valideMove(3))
			{
				if (player.move(3)) {
					if (NextIsBox(3)) {
						swap(map1B[playerLocY][playerLocX + 1], map1B[playerLocY][playerLocX + 2]);
						bxMusic.play();
						map1B[playerLocY][playerLocX + 1].setType(5);
						pushLeft--;
						nextWasBox = true;
					}
					else nextWasBox = false;
					direction = 3;
					playerLocX++;
				}
			}
			break;
	}
}

game::~game()
{
	delete window;
}
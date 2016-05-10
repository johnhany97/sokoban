/*
	John Ayad, 900150853
	Monica Fahmy, 900142228
	Youssef Ibrahim, 900142576
	All Rights Reserved.

	CS110 - Spring 2016 - Dr. Howaida Ismail
	Sokoban
*/
#include <iostream>
#include "settingsmenu.h"

using namespace sf;

settingsmenu::settingsmenu()
{
	//Load Default Font
	mainFont.loadFromFile("arcade.ttf");

	//Background
	Color background(47, 75, 110);
	settingsBG.setFillColor(background);
	settingsBG.setPosition(0, 0);
	settingsBG.setSize(Vector2f(950, 1000));

	//Settings Title
	if (!settingsTitleTexture.loadFromFile("images/settings_title.png")) {
		std::cout << "Failed to load settings title spritesheet!" << std::endl;
	}
	settingsTitle.setTexture(settingsTitleTexture);
	settingsTitle.setPosition(Vector2f(0, 0));

	//ModeButton
	if (!modeButtonTexture.loadFromFile("images/classic_button.png")) {
		std::cout << "Failed to load classic mode button spritesheet!" << std::endl;
	}
	modeButton.setTexture(modeButtonTexture);
	modeButton.setPosition(Vector2f(72, 536.5));

	//TutorialButton
	if (!tutorialButtonTexture.loadFromFile("images/tutorial_button.png")) {
		std::cout << "Failed to load tutorial button spritesheet!" << std::endl;
	}
	tutorialButton.setTexture(tutorialButtonTexture);
	tutorialButton.setPosition(Vector2f(596.5, 536.5));

	//HomeButton
	if (!homeButtonTexture.loadFromFile("images/home_button.png")) {
		std::cout << "Failed to load home button spritesheet!" << std::endl;
	}
	homeButton.setTexture(homeButtonTexture);
	homeButton.setPosition(Vector2f(332, 742));

	//Tutorial
	if (!tutorialTexture.loadFromFile("images/tutorial.png")) {
		std::cout << "Failed to load tutorial spritesheet!" << std::endl;
	}
	tutorial.setTexture(tutorialTexture);
	tutorial.setPosition(Vector2f(0, 0));
}

void settingsmenu::draw(RenderWindow& window) {
	window.draw(settingsBG);
	window.draw(settingsTitle);
	window.draw(modeButton);
	window.draw(tutorialButton);
	window.draw(homeButton);
}

bool settingsmenu::mousePress(int spriteNo, RenderWindow &window) {
	int mouseX = Mouse::getPosition().x;
	int mouseY = Mouse::getPosition().y;

	Vector2i windowPosition = window.getPosition();

	switch (spriteNo) {
	case 0: //Tutorial button
		if (mouseX > tutorialButton.getPosition().x + windowPosition.x && mouseX < (tutorialButton.getPosition().x + tutorialButton.getGlobalBounds().width + windowPosition.x)
			&& mouseY > tutorialButton.getPosition().y + windowPosition.y + 60 && mouseY < (tutorialButton.getPosition().y + tutorialButton.getGlobalBounds().height + windowPosition.y + 60)) {
			if (Mouse::isButtonPressed(Mouse::Left) && Event::MouseButtonReleased)
				return true;
			return false;
		}
		break;
	case 1: //Home button
		if (mouseX > homeButton.getPosition().x + windowPosition.x && mouseX < (homeButton.getPosition().x + homeButton.getGlobalBounds().width + windowPosition.x)
			&& mouseY > homeButton.getPosition().y + windowPosition.y + 60 && mouseY < (homeButton.getPosition().y + homeButton.getGlobalBounds().height + windowPosition.y + 60)) {
			if (Mouse::isButtonPressed(Mouse::Left) && Event::MouseButtonReleased)
				return true;
			return false;
		}
		break;
	case 2: //Gamemode button
		if (mouseX > modeButton.getPosition().x + windowPosition.x && mouseX < (modeButton.getPosition().x + modeButton.getGlobalBounds().width + windowPosition.x)
			&& mouseY > modeButton.getPosition().y + windowPosition.y + 60 && mouseY < (modeButton.getPosition().y + modeButton.getGlobalBounds().height + windowPosition.y + 60)) {
			if (Mouse::isButtonPressed(Mouse::Left) && Event::MouseButtonReleased)
				return true;
			return false;
		}
		break;
	case 3: //Tutorial
		if (mouseX > tutorial.getPosition().x + windowPosition.x && mouseX < (tutorial.getPosition().x + tutorial.getGlobalBounds().width + windowPosition.x)
			&& mouseY > tutorial.getPosition().y + windowPosition.y + 60 && mouseY < (tutorial.getPosition().y + tutorial.getGlobalBounds().height + windowPosition.y + 60)) {
			if (Mouse::isButtonPressed(Mouse::Left) && Event::MouseButtonReleased)
				return true;
			return false;
		}
	}
	return false;
}

void settingsmenu::modePressed(bool& classicModeToggle) {
	if (classicModeToggle) {
		//Switch to off
		classicModeToggle = false;
		Image temp;
		if (!temp.loadFromFile("images/classic_button.png")) {
			std::cout << "Failed to classic mode button off spritesheet!" << std::endl;
		}
		modeButtonTexture.update(temp);
	}
	else {
		//Switch to on
		classicModeToggle = true;
		Image temp;
		if (!temp.loadFromFile("images/infinity_button.png")) {
			std::cout << "Failed to infinity mode button off spritesheet!" << std::endl;
		}
		modeButtonTexture.update(temp);
	}
}

void settingsmenu::tutorialPressed(bool& showTutorial) {
	if (showTutorial) {
		//Switch to off
		showTutorial = false;
	}
	else {
		//Switch to on
		showTutorial = true;
	}
}

void settingsmenu::showT(RenderWindow &window) {
	window.draw(tutorial);
}
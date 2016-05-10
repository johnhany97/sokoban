/*
	John Ayad, 900150853
	Monica Fahmy, 900142228
	Youssef Ibrahim, 900142576
	All Rights Reserved.

	CS110 - Spring 2016 - Dr. Howaida Ismail
	Sokoban
*/
#include <iostream>
#include "mainmenu.h"

using namespace sf;

mainmenu::mainmenu()
{
	//Title
	mainTitleTexture.loadFromFile("images/title.png");
	if (!mainTitleTexture.loadFromFile("images/title.png"))
	{
		std::cout << "Failed to load main title spritesheet!" << std::endl;
	}
	mainTitle.setTexture(mainTitleTexture, true);
	mainTitle.setPosition(Vector2f(0, 0));

	//Background
	Color background(47, 75, 110);
	mainBG.setFillColor(background);
	mainBG.setPosition(0, 0);
	mainBG.setSize(Vector2f(950, 1000));

	//Play Button
	playButtonTexture.loadFromFile("images/play_button.png");
	if (!playButtonTexture.loadFromFile("images/play_button.png"))
	{
		std::cout << "Failed to load play button spritesheet!" << std::endl;
	}
	playButton.setTexture(playButtonTexture, true);
	playButton.setPosition(Vector2f(123, 601));

	//Settings Button
	settingsButtonTexture.loadFromFile("images/settings_button.png");
	if (!settingsButtonTexture.loadFromFile("images/settings_button.png"))
	{
		std::cout << "Failed to load settings button spritesheet!" << std::endl;
	}
	settingsButton.setTexture(settingsButtonTexture, true);
	settingsButton.setPosition(Vector2f(123, 424.5));

	//Volume Button
	volumeButtonTexture.loadFromFile("images/volume_button.png");
	if (!volumeButtonTexture.loadFromFile("images/volume_button.png"))
	{
		std::cout << "Failed to load volume button spritesheet!" << std::endl;
	}
	volumeButton.setTexture(volumeButtonTexture, true);
	volumeButton.setPosition(Vector2f(499, 424.5));
}

void mainmenu::draw(RenderWindow& window) {
	window.draw(mainBG);
	window.draw(mainTitle);
	window.draw(playButton);
	window.draw(settingsButton);
	window.draw(volumeButton);
}

bool mainmenu::mousePress(int spriteNo, RenderWindow &window) {
	int mouseX = Mouse::getPosition().x;
	int mouseY = Mouse::getPosition().y;

	Vector2i windowPosition = window.getPosition();

	switch (spriteNo) {
	case 0: //Play Button
		if (mouseX > playButton.getPosition().x + windowPosition.x && mouseX < (playButton.getPosition().x + playButton.getGlobalBounds().width + windowPosition.x)
			&& mouseY > playButton.getPosition().y + windowPosition.y + 60 && mouseY < (playButton.getPosition().y + playButton.getGlobalBounds().height + windowPosition.y + 60)) {
			if (Mouse::isButtonPressed(Mouse::Left) && Event::MouseButtonReleased)
				return true;
			return false;
		}
		break;
	case 1: //Settings Button
		if (mouseX > settingsButton.getPosition().x + windowPosition.x && mouseX < (settingsButton.getPosition().x + settingsButton.getGlobalBounds().width + windowPosition.x)
			&& mouseY > settingsButton.getPosition().y + windowPosition.y + 60 && mouseY < (settingsButton.getPosition().y + settingsButton.getGlobalBounds().height + windowPosition.y + 60)) {
			if (Mouse::isButtonPressed(Mouse::Left) && Event::MouseButtonReleased)
				return true;
			return false;
		}
		break;
	case 2: //Volume Button
		if (mouseX > volumeButton.getPosition().x + windowPosition.x && mouseX < (volumeButton.getPosition().x + volumeButton.getGlobalBounds().width + windowPosition.x)
			&& mouseY > volumeButton.getPosition().y + windowPosition.y + 60 && mouseY < (volumeButton.getPosition().y + volumeButton.getGlobalBounds().height + windowPosition.y + 60)) {
			if (Mouse::isButtonPressed(Mouse::Left) && Event::MouseButtonReleased)
				return true;
			return false;
		}
		break;
	}
	return false;
}

void mainmenu::volumePressed(bool& sound) {
	if (sound) {
		//Switch to off
		sound = false;
		Image temp;
		temp.loadFromFile("images/volume_button_off.png");
		if (!temp.loadFromFile("images/volume_button_off.png")) {
			std::cout << "Failed to load volume button off spritesheet!" << std::endl;
		}
		volumeButtonTexture.update(temp);
	}
	else {
		//Switch to on
		sound = true;
		Image temp;
		temp.loadFromFile("images/volume_button.png");
		if (!temp.loadFromFile("images/volume_button.png")) {
			std::cout << "Failed to load volume button spritesheet!" << std::endl;
		}
		volumeButtonTexture.update(temp);
	}
}
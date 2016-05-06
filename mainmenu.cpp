#include "mainmenu.h"
#include <iostream>
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
	playButtonTexture.loadFromFile("images/play_button.png");
	if (!playButtonTexture.loadFromFile("images/play_button.png"))
	{
		std::cout << "Failed to load play button spritesheet!" << std::endl;
	}
	playButton.setTexture(playButtonTexture, true);
	playButton.setPosition(Vector2f(123, 601));
	//mainPlay.setFont(mainFont);
	//mainPlay.setString("Play (P)");
	//mainPlay.setCharacterSize(80);
	//mainPlay.setColor(Color::White);
	//mainPlay.setPosition(Vector2f(380, 500));

	//Settings Button
	settingsButtonTexture.loadFromFile("images/settings_button.png");
	if (!settingsButtonTexture.loadFromFile("images/settings_button.png"))
	{
		std::cout << "Failed to load settings button spritesheet!" << std::endl;
	}
	settingsButton.setTexture(settingsButtonTexture, true);
	settingsButton.setPosition(Vector2f(123, 424.5));
	//mainSettings.setFont(mainFont);
	//mainSettings.setString("Settings (S)");
	//mainSettings.setCharacterSize(80);
	//mainSettings.setColor(Color::White);
	//mainSettings.setPosition(Vector2f(330, 700));

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
	window.draw(mainTitle);
	window.draw(playButton);
	window.draw(settingsButton);
	window.draw(volumeButton);
}

bool mainmenu::mousePress(int spriteNo, RenderWindow &window) {
	int mouseX = sf::Mouse::getPosition().x;
	int mouseY = sf::Mouse::getPosition().y;

	Vector2i windowPosition = window.getPosition();

	switch (spriteNo) {
	case 0: //Play Button
		if (mouseX > playButton.getPosition().x + windowPosition.x && mouseX < (playButton.getPosition().x + playButton.getGlobalBounds().width + windowPosition.x)
			&& mouseY > playButton.getPosition().y + windowPosition.y + 30 && mouseY < (playButton.getPosition().y + playButton.getGlobalBounds().height + windowPosition.y + 30)) {
			if (Mouse::isButtonPressed(Mouse::Left))
				return true;
			return false;
		}
		break;
	case 1: //Settings Button
		if (mouseX > settingsButton.getPosition().x + windowPosition.x && mouseX < (settingsButton.getPosition().x + settingsButton.getGlobalBounds().width + windowPosition.x)
			&& mouseY > settingsButton.getPosition().y + windowPosition.y + 30 && mouseY < (settingsButton.getPosition().y + settingsButton.getGlobalBounds().height + windowPosition.y + 30)) {
			if (Mouse::isButtonPressed(Mouse::Left))
				return true;
			return false;
		}
		break;
	case 2: //Volume Button
		if (mouseX > volumeButton.getPosition().x + windowPosition.x && mouseX < (volumeButton.getPosition().x + volumeButton.getGlobalBounds().width + windowPosition.x)
			&& mouseY > volumeButton.getPosition().y + windowPosition.y + 30 && mouseY < (volumeButton.getPosition().y + volumeButton.getGlobalBounds().height + windowPosition.y + 30)) {
			if (Mouse::isButtonPressed(Mouse::Left))
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
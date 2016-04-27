/*
	John Ayad, 900150853
	Monica Fahmy, 900142228
	Youssef Ibrahim, 900142576
	All Rights Reserved.

	CS110 - Spring 2016 - Dr. Howaida Ismail
	Sokoban
*/
#include <iostream>
#include "player.h"
#include "box.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

RenderWindow window(VideoMode(950, 950), "Sokoban - Hackarz Version");

int main() {

	while (window.isOpen()){
		Event event;
		while (window.pollEvent(event)) {
			if (Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed)
				window.close();
		}
		window.clear();

		window.display();
	}

	system("pause");
	return 0;
}
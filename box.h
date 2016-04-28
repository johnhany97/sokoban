#ifndef BOX_H
#define BOX_H
#include <SFML/Graphics.hpp>
class box
{
public:
	box();
	void setPosition(int, int);
	sf::Vector2f getPosition();
	void setIdealLoc(int, int);
	int getXPosition();
	int getYPosition();
	void move(int);
	void goalReach();
	bool goalReached();
	void draw(sf::RenderWindow&);

private:
	sf::Sprite bx;
	sf::Texture bxTexture;
	int xLocation, yLocation;
	int idealLocX, idealLocY;
	bool onGoal;
};

#endif BOX_H
#ifndef CELL_H
#define CELL_H
#include <SFML/Graphics.hpp>
class cell
{
private:
	enum kind { empty, wall, goal, box, player, space, box_win};
	sf::Sprite cl;
	sf::Texture clTexture;
	int xLoc, yLoc;
	bool onGoal;
	kind type;
	//Animations
	int animationcounter, currentDir;
	bool moving;
	bool needToSwap;
public:
	cell();
	kind getType();
	void setType(int);
	void initialize();
	void setPosition(int, int);
	sf::Vector2f getPosition();
	int getXPosition();
	int getYPosition();
	void goalReach(int);
	bool goalReached();
	void draw(sf::RenderWindow&);
	void switcher(int);
	bool move(int);
	void update();
	bool doesNeedToSwap();
};

#endif
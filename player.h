#ifndef PLAYER_H
#define PLAYER_H

class player
{
public:
	player();
	void setPosition(int, int);
	Vector2f getPosition();
	int getXPosition();
	int getYPosition();

private:
	Sprite pl;
	Texture plTexture;
	int xLocation, yLocation;
};

#endif
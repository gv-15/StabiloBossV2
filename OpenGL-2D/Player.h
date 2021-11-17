#pragma once

#include "Sprite.h"
class Player : public Sprite
{
	double limitDown = -0.99, limitUp = 0.99, limitLeft = -0.99, limitRight = 0.99;
	int score;
public:
	Player(string img);
	~Player();
	void setcoord(int q, int w);
	void setlimit(int q, int w);
	void moveUp(double dt);
	void moveDown(double dt);
	void moveRight(double dt);
	void moveLeft(double dt);
	bool movegeneral(int x1, int y1);
	int getScore();
	void addScore();
	void setScore(int pScore);
};


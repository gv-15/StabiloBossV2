#pragma once

#include "Sprite.h"
class Player : public Sprite
{	
	double m_posx = 0;
	double m_posy = 0;
	double limitDown = 0, limitUp = 0, limitLeft = 0, limitRight = 0;
	int score;
public:
	Player(string img, double m_posx, double m_posy);
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


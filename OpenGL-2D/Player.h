#pragma once

#include "Sprite.h"
class Player : public Sprite
{	
	
	double limitDown = 0, limitUp = 0, limitLeft = 0, limitRight = 0;
	int score, m_lifes = 3;
public:
	Player(string img, double m_posx, double m_posy, double x1, double y2);
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
	int getLifes();
	void ReduceLifes(); //No se si falta mas pero tiene buena pinta
};


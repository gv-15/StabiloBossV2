#pragma once

#include "AnimatedSprite.h"
class Projectile : public AnimatedSprite
{
protected:
	bool m_right;

public:
	Projectile(double coordPlayerX, double coordPlayerY, bool direction, string dirimg);
	~Projectile();
	void draw(double dt);
	bool isHitP1();
	bool isHitP2();
};




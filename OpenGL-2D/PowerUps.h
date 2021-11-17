#pragma once

#include "Sprite.h"

class PowerUps : public Sprite
{
	string tipo;

public:
	PowerUps(string img);
	~PowerUps();
	
	void setType(string s);
	void movefaster();
	void moveslower();
	void youdie();
	void teleport();
	void ignoreObstacle();

};


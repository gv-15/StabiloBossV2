#pragma once

#include "Sprite.h"

class PowerUp : public Sprite
{
	string tipo;
	float  Duration;
	bool   Activated;

public:
	PowerUp(string imgagedir, double m_posx1, double m_posy1);
	~PowerUp();
	
	void Activate(string s);
	void movefaster();
	void moveslower();
	void youdie();
	void teleport();
	void ignoreObstacle();
	string GetType();
	void setActivated(bool b);

};


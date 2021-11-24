#pragma once

#include "Sprite.h"
class Wall : public Sprite
{
public:
	Wall(string Filename, double x, double y, double x1, double y2);
	~Wall();
	void setcoord(int x, int y);
};
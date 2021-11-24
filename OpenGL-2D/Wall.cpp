#include "stdafx.h"
#include "Wall.h"

Wall::Wall(string dirimg, double x, double y, double x1, double y2)
	:Sprite(dirimg, x, y, x1,  y2)
{

}


Wall::~Wall()
{
}

void Wall::setcoord(int x, int y)
{
	m_x = x;
	m_y = y;
}
#include "Projectile.h"
#include "Player.h"
#include "Renderer.h"
#include "Text.h"
#include "stdafx.h"



Projectile::Projectile(double coordPlayerX, double coordPlayerY, bool direction,string dirimg)
:AnimatedSprite(dirimg.c_str(),5,2,false)
{
	setPosition(coordPlayerX, coordPlayerY);
	setRotation(0.0);
	setSize(0.1);
	setDepth(1.5);
	m_right = direction;
}

Projectile::~Projectile()
{
}

#define PROJECTILE_SPEED 0.7

void Projectile::draw(double dt)
{
	if (m_right == true)
	{
		m_x += PROJECTILE_SPEED *dt;
	}

	if (m_right == false)
	{
		m_x -= PROJECTILE_SPEED *dt;
	}

	if (m_x <= -1.0 || m_x >= 1.0 || m_y <= -1.0 || m_y >= 1.0)
		markForDeletion();
	else if (isHitP1() || isHitP2())
		markForDeletion();
	else 
		AnimatedSprite::draw(dt);
}

bool Projectile::isHitP1()
{
	Player* player2 = (Player*)Renderer::get()->getObject("Player2");
	Player* player1 = (Player*)Renderer::get()->getObject("Player1");
	Text2D *text2 = (Text2D*)Renderer::get()->getObject("text2");
	bool hit = false;
	double dist = (sqrt(pow((player1->getX() - m_x), 2) + pow((player1->getY() - m_y), 2)));
	double size = (player1->getSize() + getSize());

	if (dist <= size)
		hit = true;
	else
		hit = false;

	if (hit && !m_right)
	{
		player2->addScore();
		text2->updateScore(player2->getScore());
		return true;
	}
	else
		return false;
}

bool Projectile::isHitP2()
{
	Player* player2 = (Player*)Renderer::get()->getObject("Player2");
	Player* player1 = (Player*)Renderer::get()->getObject("Player1");
	Text2D *text1 = (Text2D*)Renderer::get()->getObject("text1");
	bool hit = false;

	double dist = (sqrt(pow((player2->getX() - m_x), 2) + pow((player2->getY() - m_y), 2)));
	double size = (player2->getSize() + getSize());

	if (dist <= size)
		hit = true;
	else
		hit = false;

	if (m_right && hit)
	{
		player1->addScore();
		text1->updateScore(player1->getScore());
		return true;
	}
	else
		return false;
}

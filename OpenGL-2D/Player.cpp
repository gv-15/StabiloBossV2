#include "stdafx.h"
#include "Player.h"
#include "World.h"
#include "Sprite.h"

Player::Player(string dirimg)
:Sprite(dirimg, m_posx, m_posy)
{
	score = 0;
}


Player::~Player()
{
}

#define PLAYER_SPEED 0.1

void Player::moveUp(double dt)
{
		if (m_y < limitUp) {
			m_y = m_y + PLAYER_SPEED * dt;
			SetPosition(m_x, m_y);
		}
}

void Player::moveDown(double dt)
{
	if (m_y > limitDown) {
		m_y = m_y - PLAYER_SPEED * dt;
		SetPosition(m_x, m_y);
	}
}

void Player::moveLeft(double dt) 
{
	if (m_x > limitLeft) {
		m_x = m_x + PLAYER_SPEED * dt;
		SetPosition(m_x, m_y);
	}
}

void Player::moveRight(double dt) 
{
	if (m_x < limitRight) {
		m_x = m_x - PLAYER_SPEED * dt;
		SetPosition(m_x, m_y);
	}
}

void Player::addScore()
{
	score++;
}

int Player::getScore()
{
	return score;
}

void Player::setScore(int pScore) {
	score = pScore;
}
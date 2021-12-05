#include "stdafx.h"
#include "Player.h"
#include "World.h"
#include "Sprite.h"

Player::Player(string dirimg, double m_posx1, double m_posy1, double x1, double y2)
:Sprite(dirimg, m_posx1, m_posy1, x1, y2)
{
	
	score = 0;
	limitDown = -0.9;
	limitUp = 0.75;
	limitLeft = -0.9; 
	limitRight = 0.9;
	
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
		m_x = m_x - PLAYER_SPEED * dt;
		SetPosition(m_x, m_y);
	}
}

void Player::moveRight(double dt) 
{
	if (m_x < limitRight) {
		m_x = m_x + PLAYER_SPEED * dt;
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

int Player::getLives()
{
	return m_lives;
}

void Player::ReduceLives()
{
	m_lives--;
}

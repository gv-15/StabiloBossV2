#include "stdafx.h"
#include "Player.h"
#include "World.h"
#include "Sprite.h"

Player::Player(string dirimg, double m_posx1, double m_posy1)
:Sprite(dirimg, m_posx1, m_posy1)
{
	m_posx = m_posx1;
	m_posy = m_posy1;
	score = 0;
	limitDown = -0.99;
	limitUp = 0.99;
	limitLeft = -0.99; 
	limitRight = 0.99;
}


Player::~Player()
{
}

#define PLAYER_SPEED 0.1

void Player::moveUp(double dt)
{
		if (m_posy < limitUp) {
			m_posy = m_posy + PLAYER_SPEED * dt;
			SetPosition(m_posx, m_posy);
		}
}

void Player::moveDown(double dt)
{
	if (m_posy > limitDown) {
		m_posy = m_posy - PLAYER_SPEED * dt;
		SetPosition(m_posx, m_posy);
	}
}

void Player::moveLeft(double dt) 
{
	if (m_posx > limitLeft) {
		m_posx = m_posx + PLAYER_SPEED * dt;
		SetPosition(m_posx, m_posy);
	}
}

void Player::moveRight(double dt) 
{
	if (m_posx < limitRight) {
		m_posx = m_posx - PLAYER_SPEED * dt;
		SetPosition(m_posx, m_posy);
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
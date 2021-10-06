#include "pch.h"
#include "Player.h"
#include "World.h"



Player::Player(int id, int x , int y)
{
	m_id = id;
	m_x = x;
	m_y = y;
}

int Player::GetId() 
{
	return m_id;
}

int Player::GetCoins()
{
	return m_coins;
}

void Player::AddCoin()
{
	m_coins = m_coins + 1;
}

int Player::GetPlayerX()
{
	return m_x;
}
int Player::GetPLayerY()
{
	return m_y;
}
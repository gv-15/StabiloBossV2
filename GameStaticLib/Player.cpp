#include "pch.h"
#include "Player.h"
#include "World.h"



Player::Player(int id)
{
	m_id = id;
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
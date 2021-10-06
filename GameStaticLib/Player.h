#pragma once

class Player
{

	int m_id;
	int m_coins = 0;
public:
	Player(int id);
	~Player(){}

	int GetId();
	void AddCoin();
	int GetCoins();
};


#pragma once

class Player
{
public:
	Player(int id);
	~Player();

	int GetId();
	void AddCoin();
	int GetCoins();
};


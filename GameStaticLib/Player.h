#pragma once

class Player
{

	int m_id;
	int m_coins = 0;
	int m_x = 0;
	int m_y = 0;
public:
	Player(int id, int x, int y);
	~Player(){}

	int GetId();
	void AddCoin();
	int GetCoins();
	int GetPlayerX();
	int GetPLayerY();
	void SetPlayerX(int i);
	void SetPlayerY(int i);

};


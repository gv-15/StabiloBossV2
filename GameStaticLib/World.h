#pragma once
#include "Timer.h"
#include <string>
#include <vector>
#include "Player.h"
using namespace std;

class World
{
	int m_WorldCoins;
	vector <Player> m_players;

public:

	World(string nameFile);

	~World();
	
	void Draw();

	int GetNumPlayers();

	Player* GetPlayer(int id);

	int GetNumCoinsLeft();
};
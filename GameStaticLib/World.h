#pragma once
#include "Timer.h"
#include <string>
#include <vector>
#include "Player.h"
using namespace std;

class World
{
	int m_WorldCoins = 0;
	vector <Player> m_players;
	int m_Height = 0;
	int m_Width = 0;
public:

	World(string nameFile);

	~World();
	
	void Draw();

	void Load(string nameFile);

	//Theses are only suggestions...
	int GetNumPlayers();

	Player* GetPlayer(int id);

	int GetNumCoinsLeft();

	int GetHeight();

	int GetWidth();
};
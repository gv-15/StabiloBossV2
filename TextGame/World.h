#pragma once
#include "Timer.h"
#include <string>
#include <vector>
#include "Player.h"
using namespace std;

class World
{
public:
	World(string nameFile);
	~World();
	
	void Draw();

	//Theses are only suggestions...
	int GetNumPlayers();
	Player* GetPlayer(int id);
	int GetNumCoinsLeft();
};
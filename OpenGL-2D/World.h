#pragma once

#include <string>
#include <vector>
#include "Player.h"
#include "Timer.h"
#include "Sprite.h"
#include "Renderer.h"

using namespace std;

class World : public Sprite 
{
	static World* m_pInstance;

	Timer m_timer;
	int lifeP1, lifeP2;
	Player *pPlayer1, *pPlayer2;

	struct point2D {
		double x, y;
	};

#define NUM_POINTS 7


public:
	World(Renderer renderer);
	~World();
	
	void updateworld(int xold, int yold, int xnew, int ynew);
	bool isplayer(char a);

	Player& getPlayer(int p);

	static World* getInstance() { return m_pInstance; }
};
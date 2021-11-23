#pragma once
#include "Player.h"
#include "../3rd-party/SoundManager/SoundManager.h" 
#include "PowerUp.h"

class Renderer;

class GameLogic
{
	static GameLogic* m_pInstance;
	Renderer* m_pRenderer;
	 	
	Player* player2 = &Player("alien-01",0.5,0.5);
	Player* player1 = &Player("alien-02",0.3,0.3);

	static void __processKeyboard(unsigned char key, int x, int y);
	static void __processUpKeyboard(unsigned char key, int x, int y);
	void ProcessKeyboard(unsigned char key, int x, int y);
	void ProcessUpKeyboard(unsigned char key, int x, int y);

	vector<PowerUp>  PowerUps;

public:

	GameLogic(Renderer* pRenderer);
	~GameLogic();
	
	void Initialize();

	void ProcessEvents();

	bool IsGameEnded();

	bool CheckCollision(Sprite& s1, Sprite& s2);

	void PickupPowerup(PowerUp p);

	void ActivatePowerUp(PowerUp pu);
};


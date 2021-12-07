#pragma once
#include "Player.h"
#include "../3rd-party/SoundManager/SoundManager.h" 
#include "PowerUp.h"

class Renderer;

class GameLogic
{
	static GameLogic* m_pInstance;
	Renderer* m_pRenderer;
	 	
	
	//Player* player1 = (Player*)m_pRenderer->ObjectByName("Player1");
	

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

	void Kill();

	bool IsGameEnded();

	bool CheckCollision(Sprite& s1, Sprite& s2);

	bool CanMove(Player* p);

	bool CanMoveRightPlayer(Player* p);

	bool CanMoveUp(Player* p);

	bool CanMoveDown(Player* p);

	bool CanMoveRight(Player* p);

	bool CanMoveLeft(Player* p);

	
	//void PickupPowerup(PowerUp p);

	//void ActivatePowerUp(PowerUp pu);
};


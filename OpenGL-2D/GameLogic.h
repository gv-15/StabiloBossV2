#pragma once
#include "Player.h"
#include "../3rd-party/SoundManager/SoundManager.h" 

class Renderer;

class GameLogic
{
	static GameLogic* m_pInstance;
	Renderer* m_pRenderer;
	 	
	Player* player2 = &Player("/img/PLAYER2 VERDEAZUL SMALL", 0.5, 0.5);
	Player* player1 = &Player("/img/PLAYER1 ROSA SMALL", 0.2, 0.2);
	//Player* player1 = (Player*)m_pRenderer->ObjectByName("Player1");
	

	static void __processKeyboard(unsigned char key, int x, int y);
	static void __processUpKeyboard(unsigned char key, int x, int y);
	void ProcessKeyboard(unsigned char key, int x, int y);
	void ProcessUpKeyboard(unsigned char key, int x, int y);

public:

	GameLogic(Renderer* pRenderer);
	~GameLogic();
	
	void Initialize();

	void ProcessEvents();

	bool IsGameEnded();
};


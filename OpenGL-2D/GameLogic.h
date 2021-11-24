#pragma once
#include "Player.h"
#include "../3rd-party/SoundManager/SoundManager.h" 

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

public:

	GameLogic(Renderer* pRenderer);
	~GameLogic();
	
	void Initialize();

	void ProcessEvents();

	bool IsGameEnded();
};


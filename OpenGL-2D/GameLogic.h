#pragma once
#include "Player.h"
#include "../3rd-party/SoundManager/SoundManager.h" 
#include "PowerUp.h"
#include "MaquinaEstados.h"

class Renderer;

class GameLogic
{
	static GameLogic* m_pInstance;
	Renderer* m_pRenderer;
	MaquinaEstados maquina;
	 	
	
	//Player* player1 = (Player*)m_pRenderer->ObjectByName("Player1");
	
	void ProcessSpecialFunc(int key, int x, int y);
	static void __processSpecialFunc(int key, int x, int y);
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

	/*float roundoff(float value, unsigned char prec);

	void PantallaFinal();*/

	bool CheckCollision(Sprite& s1, Sprite& s2);

	bool CanMoveRightPlayer(Player* p);

	bool CanMoveUpPlayer(Player* p);

	bool CanMoveUp(Player* p);

	bool CanMoveDown(Player* p);

	bool CanMoveRight(Player* p);

	bool CanMoveLeftPlayer(Player* p);

	bool CanMoveDownPlayer(Player* p);

	bool CanMoveLeft(Player* p);

	void cambiarEstado(Estado e);


	//void restart();

	//char GetNextPressedKey();

	void Clear();
};


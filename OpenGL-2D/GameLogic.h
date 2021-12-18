#pragma once
#include "Player.h"
#include "../3rd-party/SoundManager/SoundManager.h" 
#include "PowerUp.h"
#include "MaquinaEstados.h"
#include "Timer.h"

class Renderer;

class GameLogic
{
	static GameLogic* m_pInstance;
	Renderer* m_pRenderer;
	MaquinaEstados maquina;
	Timer timer;
	string color1 = "";
	string color2 = "";

	
	void ProcessSpecialFunc(int key, int x, int y);
	static void __processSpecialFunc(int key, int x, int y);
	static void __processKeyboard(unsigned char key, int x, int y);
	static void __processUpKeyboard(unsigned char key, int x, int y);
	void ProcessKeyboard(unsigned char key, int x, int y);
	void ProcessUpKeyboard(unsigned char key, int x, int y);

public:

	GameLogic(Renderer* pRenderer);

	~GameLogic();
	
	void Initialize();

	void ProcessEvents();

	void Kill();

	void Knockback();

	void KnockbackDown(Player* p1, Player* p2);

	void KnockbackUp(Player* p1, Player* p2);

	void KnockbackRight(Player* p1, Player* p2);

	void KnockbackLeft(Player* p1, Player* p2);

	bool IsGameEnded();

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

	void MostrarGanador();
};


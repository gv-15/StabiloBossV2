#include "stdafx.h"
#include "GameLogic.h"
#include "World.h"
#include "Projectile.h"
#include "Renderer.h"
#include "../3rd-party/freeglut3/include/GL/freeglut.h"
#include "AnimatedSprite.h"
#include "Player.h"

GameLogic* GameLogic::m_pInstance = nullptr;
bool w, a, s, d, ar2, ab2, der2, izq2, esc;

GameLogic::GameLogic(Renderer* pRenderer)
{
	m_pRenderer = pRenderer;
	
}


GameLogic::~GameLogic()
{
}

void GameLogic::__processKeyboard(unsigned char key, int x, int y)
{
	if (m_pInstance)
		m_pInstance->ProcessKeyboard(key, x, y);
}

void GameLogic::__processUpKeyboard(unsigned char key, int x, int y) {
	if (m_pInstance)
		m_pInstance->ProcessUpKeyboard(key, x, y);
}

void GameLogic::Initialize()
{
	glutKeyboardFunc(__processKeyboard);
	glutKeyboardUpFunc(__processUpKeyboard);

}


void GameLogic::ProcessKeyboard(unsigned char key, int x, int y)
{
	Player* player1 = (Player*)m_pRenderer->ObjectByName("Player1");
	Player* player2 = (Player*)m_pRenderer->ObjectByName("Player2");

	switch (key)
	{

	case 'w':
		w = true;
		break;
	case 'a':
		a = true;
		break;
	case 'd':
		d = true;
		break;
	case 's':
		s = true;
		break;
	case 72:
		ar2 = true;
		break;

	case 80:
		ab2 = true;
		break;

	case 75:
		izq2 = true;
		break;

	case 77:
		der2 = true;
		break;
	case 27:
		esc = true;
		exit(0);
	}
}

void GameLogic::ProcessUpKeyboard(unsigned char key, int x, int y)
{
	Player* player1 = (Player*)m_pRenderer->ObjectByName("Player1");
	Player* player2 = (Player*)m_pRenderer->ObjectByName("Player2");
	
	switch (key)
	{
		//TODO: save the state of the key
	case 'w':
		w = false;
		break;
	case 'a':
		a = false;
		break;
	case 'd':
		d = false;
		break;
	case 's':
		s = false;
		break;
	case 72:
		ar2 = false;
		break;

	case 80:
		ab2 = false;
		break;

	case 75:
		izq2 = false;
		break;

	case 77:
		der2 = false;
		break;
	case 27:
		esc = false;
	}
}

void GameLogic::ProcessEvents() //NO funciona no es ni asi esta puesto para que no de errores de compilacion y poco mas
{
/*
	if (w = true)
	{
		player1->moveUp(1 / 30);
	}
	if (a = true)
	{
		player1->moveLeft(1 / 30);
	}
	if (d = true)
	{
		player1->moveRight(1 / 30);
	}
	if (s = true)
	{
		player1->moveDown(1 / 30);
	}
	if (ar2 = true)
	{
		player2->moveUp(1 / 30);
	}
	if (ab2 = true)
	{
		player2->moveDown(1 / 30);
	}
	if (izq2 = true)
	{
		player2->moveLeft(1 / 30);
	}
	if (der2)
	{
		player2->moveRight(1 / 30);
	}
	if (esc = true)
	{
		//'Esc' key pressed. Exit the game
		exit(0);
	}
	*/
}

bool GameLogic::IsGameEnded()
{
	//TODO
	return false;
}
#include "stdafx.h"
#include "GameLogic.h"
#include "World.h"
#include "Projectile.h"
#include "Renderer.h"
#include "../3rd-party/freeglut3/include/GL/freeglut.h"
#include "AnimatedSprite.h"
#include "Player.h"

GameLogic* GameLogic::m_pInstance = nullptr;
bool w = false;
bool a = false; 
bool s = false; 
bool d = false;
bool ar2 = false;
bool ab2 = false;
bool der2 = false; 
bool izq2 = false; 
bool esc = false;

GameLogic::GameLogic(Renderer* pRenderer)
{
	m_pRenderer = pRenderer;
	m_pInstance = this;
	
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
		   player1->SetRotation(90);
		break;
	case 'a':
		a = true;
		player1->SetRotation(-90);
		break;
	case 'd':
		d = true;
		player1->SetRotation(0);
		break;
	case 's':
		s = true;
		player1->SetRotation(180);
		break;
	case 72:
		ar2 = true;
		player2->SetRotation(90);
		break;

	case 80:
		ab2 = true;
		player2->SetRotation(180);
		break;

	case 75:
		izq2 = true;
		player2->SetRotation(-90);
		break;

	case 77:
		der2 = true;
		player2->SetRotation(0);
		break;
	case 27:
		esc = true;
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
	Player* player1 = (Player*)m_pRenderer->ObjectByName("Player1");
	Player* player2 = (Player*)m_pRenderer->ObjectByName("Player2");

	if (w == true)
	{
		player1->moveUp(0.034);
	}
	if (a == true)
	{
		player1->moveLeft(0.034);
	}
	if (d == true)
	{
		player1->moveRight(0.034);
	}
	if (s == true)
	{
		player1->moveDown(0.034);
	}
	if (ar2 == true)
	{
		player2->moveUp(1/30);
	}
	if (ab2 == true)
	{
		player2->moveDown(1/30);
	}
	if (izq2 == true)
	{
		player2->moveLeft(1/30);
	}
	if (der2 == true)
	{
		player2->moveRight(1/30);
	}
	if (esc == true)
	{
		//'Esc' key pressed. Exit the game
		exit(0);
	}
	
	
}

bool GameLogic::IsGameEnded()
{
	//TODO
	return false;
}
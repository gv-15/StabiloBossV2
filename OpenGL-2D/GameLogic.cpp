#include "stdafx.h"
#include "GameLogic.h"
#include "World.h"
#include "Projectile.h"
#include "Renderer.h"
#include "../3rd-party/freeglut3/include/GL/freeglut.h"
#include "AnimatedSprite.h"
#include "Player.h"
#include "Wall.h"
#include <iostream>



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

bool CheckCollision(Sprite& one, Sprite& two) // AABB - AABB collision
{
	bool collisionX = one.GetX() + one.GetSize() >= two.GetX() &&
		two.GetX() + two.GetSize() >= one.GetX();
	// collision y-axis?
	bool collisionY = one.GetY() + one.GetSize() >= two.GetY() &&
		two.GetY() + two.GetSize() >= one.GetY();
	// collision only if on both axes
	return collisionX && collisionY;
}

bool GameLogic::CanMove(Player* p) {
	//bool obstacle = false;
	//int n = 1;
	//Wall* wall;
	//std::string wallname;


	//while (n < 4 && obstacle == false) {
	//	wallname = "wall";
	//	wallname += std::to_string(n);
	//	wall = (Wall*)m_pRenderer->ObjectByName(wallname);

	//	// collision x-axis
	//	bool collisionX = p->GetX() + p->GetSize() >= wall->GetX() &&
	//		wall->GetX() + wall->GetSize() >= p->GetX();
	//	// collision y-axis?
	//	bool collisionY = p->GetY() + p->GetSize() >= wall->GetY() &&
	//		wall->GetY() + wall->GetSize() >= p->GetY();
	//	// collision only if on both axes

	//	obstacle = collisionX && collisionY;
	//	n++;
	//}
	//
	return false;
	//return !obstacle;
}

void GameLogic::PickupPowerup(PowerUp powerUp)
{
	//if (CheckCollision(*Player, powerUp)) //misma posición
	//{	
	//	ActivatePowerUp(powerUp);
	//	powerUp.setActivated(true);

	//}
};

/*void GameLogic::ActivatePowerUp(PowerUp p)
{
	//Eliminar del tablero la foto

	string t = p.GetType();

	int indice = 0;
	
	for (int i = 0; i < PowerUps.size(); i++)
	{
		if (t._Equal(PowerUps[i].GetType()))
		{
			indice = i;
		}
			
	}

	//PowerUps.erase(i); Eliminar del array del mapa

	p.Activate(t);
	
}; */

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
		player1->SetRotation(0);
		break;
	case 'a':
		a = true;
		player1->SetRotation(90);
		break;
	case 'd':
		d = true;
		player1->SetRotation(-90);
		break;
	case 's':
		s = true;
		player1->SetRotation(180);
		break;
	case 'i':
		ar2 = true;
		player2->SetRotation(0);
		break;

	case 'k':
		ab2 = true;
		player2->SetRotation(180);
		break;

	case 'j':
		izq2 = true;
		player2->SetRotation(90);
		break;

	case 'l':
		der2 = true;
		player2->SetRotation(-90);
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
	case 'i':
		ar2 = false;
		break;

	case 'k':
		ab2 = false;
		break;

	case 'j':
		izq2 = false;
		break;

	case 'l':
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
		//if(CanMove(player1)){
			
			player1->moveUp(0.034);
			//player1->ReduceLives();aa
		//}
	}
	if (a == true)
	{
		//if (CanMove(player1)) {
	
		    int p0 = player1->getLives();
			player1->ReduceLives();
			int p = player1->getLives() ;
			m_pRenderer->DrawScene();
			player1->moveLeft(0.034);
		//}
	}
	if (d == true)
	{
		//if (CanMove(player1)) {
			player1->moveRight(0.034);
		//}
	}
	if (s == true)
	{
		//if (CanMove(player1)) {
			player1->moveDown(0.034);
		//}
	}
	if (ar2 == true)
	{
		//if (CanMove(player2)) {

			player2->moveUp(0.034);
		//}
	}
	if (ab2 == true)
	{
		player2->moveDown(0.034);
	}
	if (izq2 == true)
	{
		player2->moveLeft(0.034);
	}
	if (der2 == true)
	{
		player2->moveRight(0.034);
	}
	if (esc == true)
	{
		//'Esc' key pressed. Exit the game
		exit(0);
	}
	
	
}

bool GameLogic::IsGameEnded()
{
	Player* player1 = (Player*)m_pRenderer->ObjectByName("Player1");
	Player* player2 = (Player*)m_pRenderer->ObjectByName("Player2");
    if (player1->getLives() > 0 && player2->getLives() > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
	

}
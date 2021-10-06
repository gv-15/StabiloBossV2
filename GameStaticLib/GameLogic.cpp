#include "pch.h"
#include <iostream>
#include <iostream>
#include <chrono>
#include <thread>
#include "GameLogic.h"
#include "System.h"
#include "World.h"
#include "Player.h"


GameLogic::GameLogic(World* pWorld)
{
	m_pWorld = pWorld;
}


GameLogic::~GameLogic()
{
}

void GameLogic::ProcessInput()
{

	if (!System::IsKeyPressed())
		return; //no keyboard event to be processed


	while (System::IsKeyPressed())
	{
		char c = System::GetNextPressedKey();
		switch (c)
		{
		case 'w':
			//...
			break;
			//...
		case 27:
			//'Esc' key pressed. Exit the game
			exit(0);
		}
	}
}

bool GameLogic::IsGameEnded()
{
	//TODO: when will the game end? --> The game will end when the coins in map are 0
	if (m_pWorld->GetNumCoinsLeft() == 0)
	{
		return true;
	}
	else 
	{
		return false;
	}
}
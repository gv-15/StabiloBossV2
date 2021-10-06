#include "pch.h"
#include "World.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <chrono>
#include <thread>
#include <fstream>
#include "System.h"
#include <stdio.h>
#include <istream>
#include <fstream>

using namespace std;


World::World(std::string nameFile)
{
	


	vector < vector<char>> m_mundo(this->GetHeight(), vector<char>(this->GetWidth(), 0));
}


World::~World()
{
	//Destructor
}


void World::Draw()
{
	System::Clear();

	//TODO: -write the points each player has
	
	//TODO: -draw the maze

	//TODO: -write the time elapsed since the beginning
	//		-set the proper position/color
	
}

int World::GetNumPlayers()
{
	return m_players.size();
}

int World::GetNumCoinsLeft()
{
	return m_WorldCoins;
}

Player* World::GetPlayer(int id)
{
	return &m_players[id];
}

int World::GetHeight()
{
	return m_Height;
}

int World::GetWidth()
{
	return m_Width;
}

vector<vector<char>> World::getWorld()
{
	return m_mundo;
}

void World::MoveUp()
{
	

}

void World::MoveDown()
{


}

void World::MoveRight()
{


}

void World::MoveLeft()
{


}

void World::MoveUp1()
{


}

void World::MoveDown1()
{


}

void World::MoveRight1()
{


}

void World::MoveLeft1()
{


}

Player* World::GetPlayerById(int id)
{

	int max = m_players.size();
	int i = 0;
	bool found = false;
	while (i < max && found == false)
	{
		if (m_players[i].GetId() == id)
		{
			found = true;
		}
		else
		{
			i++;
		}

		if (found)
		{
			return &m_players[i];
		}
		else
		{
			return nullptr;
		}
	}
}
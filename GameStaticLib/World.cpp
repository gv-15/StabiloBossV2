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
#include <iostream>
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

void World::Load(std::string nameFile)
{
	int nLine = 1;
	vector<vector<char>> resultado;
	string cadena, mundo;
	ifstream fe(nameFile);
	if(fe.is_open())
	{
		while (!fe.eof() && nLine <= m_Height)
		{
			fe >> cadena;
			if(cadena.size() == m_Width)
			{
				for (int i = 0; i < m_Width; i++)
				{
					m_mundo[nLine][i]=cadena.at(i);
				}
			}
			nLine++;
		}
	}
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
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
	char buffer[256];
	ifstream fe(nameFile);
	if(fe.is_open())
	{
		while (!fe.eof())
		{
			fe.getline(buffer,256);
			m_Width = fe.gcount();
			for (int i = 0; i < m_Width; i++)
			{
				m_mundo[nLine][i]=buffer[i];

				if(buffer[i] == 'Y' || buffer[i] == 'I')
				{
					if(buffer[i] == 'I')
					{
						Player p = Player(0, i, nLine);
						m_players.push_back(p);
					}

					if (buffer[i] == 'Y')
					{
						Player p = Player(1, i, nLine);
						m_players.push_back(p);
					}
				}
				
				if(buffer[i] == '0')
				{
					m_WorldCoins++;
				}
			}
			nLine++;
		}
		m_Height = nLine;
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

void World::MoveUp(int i)
{
	

}

void World::MoveDown(int i)
{


}

void World::MoveRight(int i)
{


}

void World::MoveLeft(int i)
{


}

void World::MoveUp1(int i)
{


}

void World::MoveDown1(int i)
{


}

void World::MoveRight1(int i)
{


}

void World::MoveLeft1(int i)
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
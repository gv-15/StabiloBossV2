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
			m_Width = sizeof(buffer);
			for (int i = 0; i < m_Width; i++)
			{
				m_mundo[nLine][i]=buffer[i];
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
	int x = GetPlayerById(i)->GetPlayerX();
	int y = GetPlayerById(i)->GetPLayerY();
	GetPlayerById(i)->SetPLayerY(y - 1);
	if (m_mundo[y][x] != '#' || m_mundo[y][x] != 'I')
	{ 
	m_mundo[y][x] = 'T';
	m_mundo[y-1][x] = 'Y';
	}
	else if(m_mundo[y][x] != '0')
	{
	m_mundo[y][x] = 'T';
	m_mundo[y - 1][x] = 'Y';
	m_WorldCoins = m_WorldCoins - 1;
	GetPlayerById(i)->AddCoin();
	}

}

void World::MoveDown(int i)
{
	int x = GetPlayerById(i)->GetPlayerX();
	int y = GetPlayerById(i)->GetPLayerY();
	GetPlayerById(i)->SetPLayerY(y + 1);
	
	if (m_mundo[y][x] != '#' || m_mundo[y][x] != 'I')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y + 1][x] = 'Y';
	}
	else if (m_mundo[y][x] != '0')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y + 1][x] = 'Y';
		m_WorldCoins = m_WorldCoins - 1;
		GetPlayerById(i)->AddCoin();
	}
}

void World::MoveRight(int i)
{
	int x = GetPlayerById(i)->GetPlayerX();
	int y = GetPlayerById(i)->GetPLayerY();
	GetPlayerById(i)->SetPLayerY(x + 1);
	
	if (m_mundo[y][x] != '#' || m_mundo[y][x] != 'I')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y][x + 1] = 'Y';
	}
	else if (m_mundo[y][x] != '0')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y][x + 1] = 'Y';
		m_WorldCoins = m_WorldCoins - 1;
		GetPlayerById(i)->AddCoin();
	}
}

void World::MoveLeft(int i)
{
	int x = GetPlayerById(i)->GetPlayerX();
	int y = GetPlayerById(i)->GetPLayerY();
	GetPlayerById(i)->SetPLayerY(x - 1);
	
	if (m_mundo[y][x] != '#' || m_mundo[y][x] != 'I')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y][x - 1] = 'Y';
	}
	else if (m_mundo[y][x] != '0')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y][x - 1] = 'Y';
		m_WorldCoins = m_WorldCoins - 1;
		GetPlayerById(i)->AddCoin();
	}
}

void World::MoveUp1(int i)
{
	int x = GetPlayerById(i)->GetPlayerX();
	int y = GetPlayerById(i)->GetPLayerY();
	GetPlayerById(i)->SetPLayerY(y - 1);

	if (m_mundo[y][x] != '#' || m_mundo[y][x] != 'Y')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y - 1][x] = 'I';
	}
	else if (m_mundo[y][x] != '0')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y - 1][x] = 'I';
		m_WorldCoins = m_WorldCoins - 1;
		GetPlayerById(i)->AddCoin();
	}
}

void World::MoveDown1(int i)
{
	int x = GetPlayerById(i)->GetPlayerX();
	int y = GetPlayerById(i)->GetPLayerY();
	GetPlayerById(i)->SetPLayerY(y + 1);

	if (m_mundo[y][x] != '#' || m_mundo[y][x] != 'Y')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y + 1][x] = 'I';
	}
	else if (m_mundo[y][x] != '0')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y + 1][x] = 'I';
		m_WorldCoins = m_WorldCoins - 1;
		GetPlayerById(i)->AddCoin();
	}
}

void World::MoveRight1(int i)
{
	int x = GetPlayerById(i)->GetPlayerX();
	int y = GetPlayerById(i)->GetPLayerY();
	GetPlayerById(i)->SetPLayerY(x + 1);
	
	if (m_mundo[y][x] != '#' || m_mundo[y][x] != 'Y')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y][x + 1] = 'I';
	}
	else if (m_mundo[y][x] != '0')
	{
	m_mundo[y][x] = 'T';
	m_mundo[y][x + 1] = 'I';
	m_WorldCoins = m_WorldCoins - 1;
	GetPlayerById(i)->AddCoin();
	}
}

void World::MoveLeft1(int i)
{
	int x = GetPlayerById(i)->GetPlayerX();
	int y = GetPlayerById(i)->GetPLayerY();
	GetPlayerById(i)->SetPLayerY(x - 1);
	
	if (m_mundo[y][x] != '#' || m_mundo[y][x] != 'Y')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y][x - 1] = 'I';
	}
	else if (m_mundo[y][x] != '0')
	{
	m_mundo[y][x] = 'T';
	m_mundo[y][x - 1] = 'I';
	m_WorldCoins = m_WorldCoins - 1;
	GetPlayerById(i)->AddCoin();
	}
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
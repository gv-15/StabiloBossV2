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


}


World::~World()
{
	//Destructor
}


void World::Draw()
{
	m_mundo = vector<vector<char>>(4);

	//System::Clear();

	//TODO: -write the points each player has

	//TODO: -draw the maze

	//TODO: -write the time elapsed since the beginning
	//		-set the proper position/color

	//vector<vector<char>> m_mundo(this->GetHeight(), vector<char>(this->GetWidth(),0));

	for (int i = 0;i < 4;i++)
	{
		m_mundo[i] = vector<char>(4);
	}

	char espacio = ' ';
	char caracter = ' ';

	m_mundo[0][0] = '#';
	m_mundo[0][1] = 'I';
	m_mundo[0][2] = '#';
	m_mundo[0][3] = ' ';
	m_mundo[1][0] = '#';
	m_mundo[1][1] = 'Y';
	m_mundo[1][2] = '#';
	m_mundo[1][3] = ' ';
	m_mundo[2][0] = '#';
	m_mundo[2][1] = '0';
	m_mundo[2][2] = '#';
	m_mundo[2][3] = ' ';


	for (int i = 0; i < m_mundo.size(); i++)
	{
		for (int j = 0; j < m_mundo.size(); j++)
		{
			caracter = m_mundo[i][j];

			if (caracter == espacio)
			{
				cout << '\n';
				

			}	

			else 
			{
				cout << m_mundo[i][j];
			}
			
			
		}
		
	}
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
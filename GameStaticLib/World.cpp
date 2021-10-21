#include "pch.h"
#include "World.h"
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
#include "Player.h"


using namespace std;
using namespace chrono;

Timer timer;

World::World(std::string pNameFile)
{
	
	namefile = pNameFile;


	vector<vector<char>> m_mundo;

	timer.Start();

}


World::~World()
{
	//Destructor
}

void World::Load()
{
	int nLine = 0;
	char buffer[256]; //se guarda cada línea que lea
	ifstream fe(namefile);
	if(fe.is_open())
	{
		//m_mundo  vector<char>();
		while (!fe.eof()) //end of file
		{
			fe.getline(buffer,256);
			int numChars = fe.gcount(); //cantidad de carcateres de la línea
			m_mundo.push_back(vector<char>());
			for (int i = 0; i < numChars; i++)
			{
				if (buffer[i] != '\0')
				{
					m_Width = i+1;
					m_mundo[nLine].push_back(buffer[i]);
				}

				if(buffer[i] == 'Y' || buffer[i] == 'I')
				{
					if(buffer[i] == 'I')
					{
						Player p = Player(1, i, nLine);
						m_players.push_back(p);
					}

					if (buffer[i] == 'Y')
					{
						Player p = Player(0, i, nLine);
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
		

		m_Height = nLine; //sumatorio de líneas que ha leído
	}
}


void World::Draw()
{
	
	//System::Clear();

	//TODO: -write the points each player has

	//TODO: -draw the maze

	//TODO: -write the time elapsed since the beginning
	//		-set the proper position/color

	ConsoleColor backgroundColor = Black;
	ConsoleColor foregroundColorInterfez = Green;
	System::SetTextColor(foregroundColorInterfez, backgroundColor);

	
	cout << "Jugador 1: " << m_players[0].GetCoins()  << "\t" << "Monedas restantes: " << m_WorldCoins 
		<<"\t" << "Jugador 2: " << m_players[1].GetCoins() << "\n\n";

	char espacio = '\0';
	char caracter = ' ';	
	

	for (int i = 0; i < m_Height; i++)
	{
		for (int j = 0; j < m_Width; j++)
		{
			caracter = m_mundo[i][j];
			
			if (caracter == 'T')
			{
				cout << ' ';

			}
			else
			{
				if (caracter == '0') {
					ConsoleColor foregroundColorCoin = Yellow;
					System::SetTextColor(foregroundColorCoin, backgroundColor);
					cout << m_mundo[i][j];
				}

				else if (caracter == 'Y') {
					ConsoleColor foregroundColorP1 = Blue;
					System::SetTextColor(foregroundColorP1, backgroundColor);
					cout << m_mundo[i][j];
				}

				else if (caracter == 'I') {
					
					ConsoleColor foregroundColorP2 = Red;
					System::SetTextColor(foregroundColorP2, backgroundColor);
					cout << m_mundo[i][j];
				}

				else if (caracter == '#') {
					
					ConsoleColor foregroundColorPared = White;
					System::SetTextColor(foregroundColorPared, backgroundColor);
					cout << m_mundo[i][j];
				}
				

				
			}
			
			

		}

		cout << '\n';
	}

	cout << "\n" << "Timer:" << timer.ElapsedSeconds();

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
vector <Player> World::GetmPlayers()
{
	return m_players;
}


vector < vector<char>> World::GetmMundo()
{
	return m_mundo;
}

Timer World::GetTimer() 
{
	return timer;
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
	int y = GetPlayerById(i)->GetPlayerY();
	
	if (m_mundo[y-1][x] != '#' && m_mundo[y-1][x] != 'I' && m_mundo[y-1][x] != '0')
	{ 
	GetPlayerById(i)->SetPlayerY(y - 1);
	m_mundo[y][x] = 'T';
	m_mundo[y-1][x] = 'Y';
	}
	else if(m_mundo[y-1][x] == '0')
	{
	m_mundo[y][x] = 'T';
	m_mundo[y - 1][x] = 'Y';
	GetPlayerById(i)->AddCoin();
	GetPlayerById(i)->SetPlayerY(y - 1);
	m_WorldCoins = m_WorldCoins - 1;
	}
	

}

void World::MoveDown(int i)
{

	int x = GetPlayerById(i)->GetPlayerX();
	int y = GetPlayerById(i)->GetPlayerY();
	
	if (m_mundo[y+1][x] != '#' && m_mundo[y+1][x] != 'I' && m_mundo[y+1][x] != '0')
	{
		GetPlayerById(i)->SetPlayerY(y + 1);
		m_mundo[y][x] = 'T';
		m_mundo[y + 1][x] = 'Y';
	}
	else if (m_mundo[y+1][x] == '0')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y + 1][x] = 'Y';
		GetPlayerById(i)->AddCoin();
		GetPlayerById(i)->SetPlayerY(y + 1);
		m_WorldCoins = m_WorldCoins - 1;;
	}
	
}

void World::MoveRight(int i)
{
	int x = GetPlayerById(i)->GetPlayerX();
	int y = GetPlayerById(i)->GetPlayerY();
	
	if (m_mundo[y][x+1] != '#' && m_mundo[y][x+1] != 'I' && m_mundo[y][x+1] != '0')
	{
		GetPlayerById(i)->SetPlayerX(x + 1);
		m_mundo[y][x] = 'T';
		m_mundo[y][x + 1] = 'Y';
	}
	else if (m_mundo[y][x+1] == '0')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y][x + 1] = 'Y';
		GetPlayerById(i)->AddCoin();
		GetPlayerById(i)->SetPlayerX(x + 1);
		m_WorldCoins = m_WorldCoins - 1;
	}
	
}

void World::MoveLeft(int i)
{
	int x = GetPlayerById(i)->GetPlayerX();
	int y = GetPlayerById(i)->GetPlayerY();
	
	if (m_mundo[y][x-1] != '#' && m_mundo[y][x-1] != 'I' && m_mundo[y][x-1] != '0')
	{
		GetPlayerById(i)->SetPlayerX(x - 1);
		m_mundo[y][x] = 'T';
		m_mundo[y][x - 1] = 'Y';
	}
	else if (m_mundo[y][x-1] == '0')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y][x - 1] = 'Y';
		GetPlayerById(i)->AddCoin();
		GetPlayerById(i)->SetPlayerX(x - 1);
		m_WorldCoins = m_WorldCoins - 1;
	}
	
}

void World::MoveUp1(int i)
{
	int x = GetPlayerById(i)->GetPlayerX();
	int y = GetPlayerById(i)->GetPlayerY();

	if (m_mundo[y-1][x] != '#' && m_mundo[y-1][x] != 'Y' && m_mundo[y-1][x] != '0')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y - 1][x] = 'I';
		GetPlayerById(i)->SetPlayerY(y - 1);
	}
	else if (m_mundo[y-1][x] == '0')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y - 1][x] = 'I';
		GetPlayerById(i)->AddCoin();
		GetPlayerById(i)->SetPlayerY(y - 1);
		m_WorldCoins = m_WorldCoins - 1;
	}
	
}

void World::MoveDown1(int i)
{
	int x = GetPlayerById(i)->GetPlayerX();
	int y = GetPlayerById(i)->GetPlayerY();

	if (m_mundo[y+1][x] != '#' && m_mundo[y+1][x] != 'Y' && m_mundo[y+1][x] != '0')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y + 1][x] = 'I';
		GetPlayerById(i)->SetPlayerY(y + 1);
	}
	else if (m_mundo[y+1][x] == '0')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y + 1][x] = 'I';
		GetPlayerById(i)->AddCoin();
		GetPlayerById(i)->SetPlayerY(y + 1);
		m_WorldCoins = m_WorldCoins - 1;
	}
	
}

void World::MoveRight1(int i)
{
	int x = GetPlayerById(i)->GetPlayerX();
	int y = GetPlayerById(i)->GetPlayerY();
	
	if (m_mundo[y][x+1] != '#' && m_mundo[y][x+1] != 'Y' && m_mundo[y][x+1] != '0')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y][x + 1] = 'I';
		GetPlayerById(i)->SetPlayerX(x + 1);
	}
	else if (m_mundo[y][x+1] == '0')
	{
	m_mundo[y][x] = 'T';
	m_mundo[y][x + 1] = 'I';
	GetPlayerById(i)->AddCoin();
	GetPlayerById(i)->SetPlayerX(x + 1);
	m_WorldCoins = m_WorldCoins - 1;
	}
	
}

void World::MoveLeft1(int i)
{
	int x = GetPlayerById(i)->GetPlayerX();
	int y = GetPlayerById(i)->GetPlayerY();
	
	if (m_mundo[y][x-1] != '#' && m_mundo[y][x-1] != 'Y' && m_mundo[y][x-1] != '0')
	{
		m_mundo[y][x] = 'T';
		m_mundo[y][x - 1] = 'I';
		GetPlayerById(i)->SetPlayerX(x - 1);
	}
	else if (m_mundo[y][x-1] == '0')
	{
	m_mundo[y][x] = 'T';
	m_mundo[y][x - 1] = 'I';
	GetPlayerById(i)->AddCoin();
	GetPlayerById(i)->SetPlayerX(x - 1);
	m_WorldCoins = m_WorldCoins - 1;
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

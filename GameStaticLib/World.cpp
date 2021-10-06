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
}


World::~World()
{
	//Destructor
}

string World::Load(std::string nameFile)
{
	string cadena;
	ifstream fe(nameFile);
	if(fe.is_open())
	{
		while (!fe.eof())
		{
			fe >> cadena;
		}
	}
	return cadena;
}


void World::Draw()
{
	System::Clear();

	//TODO: -write the points each player has
	
	//TODO: -draw the maze

	//TODO: -write the time elapsed since the beginning
	//		-set the proper position/color
	
}


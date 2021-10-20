#include "stdafx.h"
#include "../GameStaticLib/World.h"
#include "../GameStaticLib/GameLogic.h"
#include <thread>  
#include "../GameStaticLib/System.h"
#include <iostream>

int main()
{

	string filename;

	srand(time(NULL));

	int rnd = rand() % 3 + 1;

	if(rnd == 3)
	{
		filename = "../game3.txt";
	}
	else if (rnd  == 2)
	{
		filename = "../game2.txt";
	}
	else
	{
		filename = "../game1.txt";
	}


	World world(filename);

	GameLogic gameLogic(&world);

	cout << "Bienvenido al Gran Laberinto de Stabillo, donde viviras una experiencia llena de color SUERTE!! " << "\n\n" << "Pulsa el boton espacio para empezar";

	while (!gameLogic.IsGameStarted());
	System::Clear();

	world.Load();

	do
	{ 
		System::SetCursorPos(0,0);
		System::HideCursor(); 

		world.Draw();

		gameLogic.ProcessInput();

		
	}
	while (!gameLogic.IsGameEnded());

    return 0;
}


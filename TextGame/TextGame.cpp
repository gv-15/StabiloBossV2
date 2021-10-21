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


	World world1(filename);
	GameLogic gameLogic1(&world1);

	cout  << "Bienvenido al Gran Laberinto de Stabilo, donde viviras una experiencia llena de color ¡¡SUERTE!! " << "\n\n" << "                               Pulsa el boton espacio para empezar"; //El espacio es para que salga en medio

	while (!gameLogic1.IsGameStarted());
	System::Clear();
	world1.~World();
	gameLogic1.~GameLogic();

	World world(filename);
	GameLogic gameLogic(&world);

	world.Load();

	do
	{ 
		System::SetCursorPos(0,0);
		System::HideCursor(); 

		world.Draw();

		gameLogic.ProcessInput();

		
	}
	while (!gameLogic.IsGameEnded());

	cout << "\n"
		 << "Pulsa el boton espacio para salir !!"
	     << "\n"
	    	<< "Pulsa cualquier otro boton para jugar de nuevo !!";
	char c = System::GetNextPressedKey();
	if (c == ' ')
	{	
		return 0;
	}
	else
	{
	System::Clear();
    return main();
	}

	
}


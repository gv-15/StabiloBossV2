#include "stdafx.h"
#include "../GameStaticLib/World.h"
#include "../GameStaticLib/GameLogic.h"
#include <thread>  
#include "../GameStaticLib/System.h"
#include <iostream>

int main()
{
	World world("../game.txt");

	GameLogic gameLogic(&world);

	cout << "Bienvenido al gran laberinto de stabillo, donde viviras una experiencia llena de color SUERTE!! "<<"\n\n"<<"Pulsa el boton espacio para empezar";
		
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


#include "stdafx.h"
#include "../GameStaticLib/World.h"
#include "../GameStaticLib/GameLogic.h"
#include <thread>  
#include "../GameStaticLib/System.h"

int main()
{
	World world("../game.txt");

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

    return 0;
}


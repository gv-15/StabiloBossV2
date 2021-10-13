#include "stdafx.h"
#include "../GameStaticLib/World.h"
#include "../GameStaticLib/GameLogic.h"
#include <thread>  

int main()
{
	World world("C:/Users/esanj/source/repos/TheStabiloBoss/prueba.txt");

	GameLogic gameLogic(&world);

	
	do
	{
		
		world.Load();	
		
		world.Draw();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

		gameLogic.ProcessInput();

		
	}
	while (!gameLogic.IsGameEnded());

    return 0;
}


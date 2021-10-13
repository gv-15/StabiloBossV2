#include "stdafx.h"
#include "../GameStaticLib/World.h"
#include "../GameStaticLib/GameLogic.h"


int main()
{
	World world("C:/Users/esanj/source/repos/TheStabiloBoss/prueba.txt");

	GameLogic gameLogic(&world);

	world.Load();
	do
	{
		world.Draw();

		gameLogic.ProcessInput();
	}
	while (!gameLogic.IsGameEnded());

    return 0;
}


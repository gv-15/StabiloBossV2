#include "stdafx.h"
#include "../GameStaticLib/World.h"
#include "../GameStaticLib/GameLogic.h"


int main()
{
	World world("file.csv");

	GameLogic gameLogic(&world);

	do
	{
		world.Draw();

		gameLogic.ProcessInput();
	}
	while (!gameLogic.IsGameEnded());

    return 0;
}


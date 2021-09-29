// TextGame.cpp : Main program entry point
//

#include "stdafx.h"
#include "World.h"
#include "GameLogic.h"


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


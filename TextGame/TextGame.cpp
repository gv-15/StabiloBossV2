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
	
	int rnd1= rand() % 15 + 1;
	int rnd = 15;
	if(rnd == 15)
	{
		filename = "../game15txt"; //falla
	}
	else if (rnd  == 14)
	{
		filename = "../game14.txt";
	}
	else if (rnd == 13)
	{
		filename = "../game13.txt";
	}
	else if (rnd == 12)
	{
	filename = "../game12.txt";
	}
	else if (rnd == 11)
	{
	filename = "../game11.txt"; //Falla
	}
	else if (rnd == 10)
	{
		filename = "../game10.txt";
	}
	else if (rnd == 9)
	{
		filename = "../game9.txt"; //Falla
	}
    else if (rnd  == 8)
	{
		filename = "../game8.txt";
	}
	else if (rnd == 7)
	{
		filename = "../game7.txt"; //Falla
	}
	else if (rnd == 6)
	{
		filename = "../game6.txt";
	}
	else if (rnd == 5)
	{
		filename = "../game5.txt";
	}
	else if (rnd == 4)
	{
		filename = "../game4.txt";
	}
	else if (rnd == 3)
	{
		filename = "../game3.txt";
	}
	else if (rnd == 2)
	{
		filename = "../game2.txt";
	}
	else
	{
		filename = "../game1.txt";
	}




	World world1(filename);
	GameLogic gameLogic1(&world1);

	cout  << "Bienvenido al Gran Laberinto de Stabilo, donde viviras una colorida aventura en uno de nuestro 15 mapas ¡¡SUERTE!! " << "\n\n" << "                                   Pulsa el boton espacio para empezar"; //El espacio es para que salga en medio

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


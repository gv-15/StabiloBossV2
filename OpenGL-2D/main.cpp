#include "stdafx.h"
#include "GameLogic.h"
#include "Renderer.h"
#include "Sprite.h"
#include "Player.h"
#include "World.h"
#include "Text.h"
#include "Projectile.h"
#include "Text.h"
#include "TextureManager.h"
#include <iostream>
#include "../3rd-party/freeglut3/include/GL/freeglut.h"
#include "AnimatedSprite.h"
#include "../3rd-party/SoundManager/SoundManager.h" //relative path to the main header
using namespace std;

/*Sprite props[20];
Player players[2];
Sprite powerups[4];*/

int main(int argc, char** argv)
{
	Renderer renderer;
	TextureManager textureManager;
	Player player1 = Player("/img/PLAYER1 ROSA SMALL",0.5,0.5);
	player1.SetName("Player1");
	//player1.SetPosition(0.5, 0.5);
	

#ifdef _DEBUG
	textureManager.SetVerbose(true);
#endif

	renderer.SetFrameRate(30);
	GameLogic gameLogic(&renderer);
	renderer.Initialize(argc, argv);

	gameLogic.Initialize();
	renderer.AddObject(&player1);

	//TODO: create players and add them to the renderer


	while (!gameLogic.IsGameEnded())
	{
		//UPDATE////////////////////
		////////////////////////////
		//process queued events
		glutMainLoopEvent();
		gameLogic.ProcessEvents();


		//RENDER////////////////////
		////////////////////////////
		glutPostRedisplay();
		glutSwapBuffers();
	}
   
	return 0;
}

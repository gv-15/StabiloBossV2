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



int main(int argc, char** argv)
{

	Renderer renderer;
	TextureManager textureManager;

	

#ifdef _DEBUG
	textureManager.SetVerbose(true);
#endif

	renderer.SetFrameRate(30);
	GameLogic gameLogic(&renderer);
	renderer.Initialize(argc, argv);
	Player player1 = Player("/img/PLAYER1 ROSA SMALL", 0.9, 0, 0.084, 0.2);
	player1.SetName("Player1");
	Player player2 = Player("/img/PLAYER2 VERDEAZUL SMALL", -0.9, 0, 0.084, 0.2);
	player2.SetName("Player2");
	gameLogic.Initialize();
	renderer.AddObject(&player1);
	renderer.AddObject(&player2);

	


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
	
}

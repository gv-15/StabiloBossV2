#include "stdafx.h"
#include "GameLogic.h"
#include "Renderer.h"
#include "Sprite.h"
#include "Player.h"
#include "World.h"
#include "Wall.h"
#include "Text.h"
#include "Projectile.h"
#include "Text.h"
#include "TextureManager.h"
#include <iostream>
#include "../3rd-party/freeglut3/include/GL/freeglut.h"
#include "AnimatedSprite.h"
#include "../3rd-party/SoundManager/SoundManager.h" //relative path to the main header
#include "MaquinaEstados.h"

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
	
	gameLogic.Initialize(); 
	

	


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

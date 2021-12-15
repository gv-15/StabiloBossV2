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
#include "MaquinaEstados.h"
#include "playsoundapi.h" 
#include "../3rd-party/SoundManager/SoundManager.h"

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
	PlaySound(NULL, NULL, 0);
	PlaySound(TEXT("snd/sonic.wav"), NULL, SND_LOOP | SND_ASYNC);
	


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

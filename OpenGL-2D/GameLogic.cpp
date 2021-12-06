#include "stdafx.h"
#include "GameLogic.h"
#include "World.h"
#include "Projectile.h"
#include "Renderer.h"
#include "../3rd-party/freeglut3/include/GL/freeglut.h"
#include "AnimatedSprite.h"
#include "Player.h"
#include <iostream>
#include <stdio.h>   
#include <conio.h> 
#include "Wall.h" 


using namespace std;

GameLogic* GameLogic::m_pInstance = nullptr;
bool w = false;
bool a = false; 
bool s = false; 
bool d = false;
bool ar2 = false;
bool ab2 = false;
bool der2 = false; 
bool izq2 = false; 
bool esc = false;

GameLogic::GameLogic(Renderer* pRenderer)
{
	m_pRenderer = pRenderer;
	m_pInstance = this;
	maquina = MaquinaEstados();
	maquina.DefinirEstado(Inicio);
	
}


GameLogic::~GameLogic()
{
}

bool CheckCollision(Sprite& one, Sprite& two) // AABB - AABB collision
{
	bool collisionX = one.GetX() + one.GetSize() >= two.GetX() &&
		two.GetX() + two.GetSize() >= one.GetX();
	// collision y-axis?
	bool collisionY = one.GetY() + one.GetSize() >= two.GetY() &&
		two.GetY() + two.GetSize() >= one.GetY();
	// collision only if on both axes
	return collisionX && collisionY;
}

bool GameLogic::CanMoveUp(Player* p) {

	double pxArrIzq = p->GetX() - (p->GetXScale() / 2);
	double pyArrIzq = p->GetY() + (p->GetYScale() / 2);
	double playerW = p->GetXScale();
	double playerH = p->GetYScale();

	bool obstacle = false;
	int n = 1;
	Wall* wall;
	std::string wallname;


	while(n < 4 && obstacle == false){
	
		wallname = "wall";
		wallname += std::to_string(n);
		wall = (Wall*)m_pRenderer->ObjectByName(wallname);

		double wxArrIzq = wall->GetX() - (wall->GetXScale() / 2);
		double wyArrIzq = wall->GetY() + (wall->GetYScale() / 2);
		double wallW = wall->GetXScale();
		double wallH = wall->GetYScale();

		if ((pyArrIzq < wyArrIzq - wallH)  &&
			((pxArrIzq + playerW < wxArrIzq) || (pxArrIzq > wxArrIzq + wallW))) {

			 obstacle = false;

		}
		else if ((pyArrIzq > wyArrIzq ) &&
					((pxArrIzq + playerW > wxArrIzq) || (pxArrIzq < wxArrIzq + wallW)))
		{
			obstacle = false;

		}
		else if ((pyArrIzq >= wyArrIzq - wallH)  &&
			     ((pxArrIzq + playerW >= wxArrIzq) && (pxArrIzq <= wxArrIzq + wallW)) && (pyArrIzq - playerH < wyArrIzq)) 
			 {
			
					obstacle = true;
			 }

		n++;

	}
	

	return !obstacle;
}

bool GameLogic::CanMoveRight(Player* p) {

	double pxArrIzq = p->GetX() - (p->GetYScale() / 2);
	double pyArrIzq = p->GetY() + (p->GetXScale() / 2);
	double playerW = p->GetYScale();
	double playerH = p->GetXScale();

	bool obstacle = false;
	int n = 1;
	Wall* wall;
	std::string wallname;

	while (n < 4 && obstacle == false) {
		wallname = "wall";
		wallname += std::to_string(n);
		wall = (Wall*)m_pRenderer->ObjectByName(wallname);

		double wxArrIzq = wall->GetX() - (wall->GetXScale() / 2);
		double wyArrIzq = wall->GetY() + (wall->GetYScale() / 2);
		double wallW = wall->GetXScale();
		double wallH = wall->GetYScale();

		if ((pxArrIzq + playerW < wxArrIzq) &&
			((pyArrIzq + playerH < wyArrIzq) || (pyArrIzq > wyArrIzq + wallH))) {

				obstacle = false;

		}
		else if ((pxArrIzq + playerW < wxArrIzq) &&
				((pyArrIzq + playerH > wyArrIzq) || (pyArrIzq < wyArrIzq + wallH)))
			 {
					obstacle = false;

			 }
		else if ((pxArrIzq + playerW >= wxArrIzq) &&
				((pyArrIzq - playerH <= wyArrIzq) && (pyArrIzq >= wyArrIzq - wallH)) && (pxArrIzq < wxArrIzq - wallW )) { 

					obstacle = true;
			 }

		n++;

	}


	return !obstacle;
}

bool GameLogic::CanMoveLeft(Player* p) {

	double pxArrIzq = p->GetX() - (p->GetYScale() / 2);
	double pyArrIzq = p->GetY() + (p->GetXScale() / 2);
	double playerW = p->GetYScale();
	double playerH = p->GetXScale();

	bool obstacle = false;
	int n = 1;
	Wall* wall;
	std::string wallname;

	while (n < 4 && obstacle == false) {
		wallname = "wall";
		wallname += std::to_string(n);
		wall = (Wall*)m_pRenderer->ObjectByName(wallname);

		double wxArrIzq = wall->GetX() - (wall->GetXScale() / 2);
		double wyArrIzq = wall->GetY() + (wall->GetYScale() / 2);
		double wallW = wall->GetXScale();
		double wallH = wall->GetYScale();

		if ((pxArrIzq > wxArrIzq + wallW) &&
			((pyArrIzq + playerH < wyArrIzq) || (pyArrIzq > wyArrIzq + wallH))) {

				obstacle = false;

		}
		else if ((pxArrIzq > wxArrIzq + wallW) &&
					((pyArrIzq + playerH > wyArrIzq) || (pyArrIzq < wyArrIzq + wallH)))
			 {		
						obstacle = false;

			 }
		else if ((pxArrIzq <= wxArrIzq + wallW) &&
					((pyArrIzq - playerH <= wyArrIzq) && (pyArrIzq >= wyArrIzq - wallH)) && (pxArrIzq  > wxArrIzq )) { 

						obstacle = true;
			 }

		n++;

	}


	return !obstacle;
}

bool GameLogic::CanMoveDown(Player* p) {
	
	double pxArrIzq = p->GetX() - (p->GetXScale() / 2);
	double pyArrIzq = p->GetY() + (p->GetYScale() / 2);
	double playerW = p->GetXScale();
	double playerH = p->GetYScale();

	bool obstacle = false;
	int n = 1;
	Wall* wall;
	std::string wallname;

	while (n < 4 && obstacle == false) {
		wallname = "wall";
		wallname += std::to_string(n);
		wall = (Wall*)m_pRenderer->ObjectByName(wallname);

		double wxArrIzq = wall->GetX() - (wall->GetXScale() / 2);
		double wyArrIzq = wall->GetY() + (wall->GetYScale() / 2);
		double wallW = wall->GetXScale();
		double wallH = wall->GetYScale();

		if ((pyArrIzq < wyArrIzq - wallH) &&
			((pxArrIzq + playerW < wxArrIzq) || (pxArrIzq > wxArrIzq + wallW))) {

				obstacle = false;

		}
		else if ((pyArrIzq < wyArrIzq) &&
			((pxArrIzq + playerW > wxArrIzq) || (pxArrIzq < wxArrIzq + wallW)))
		{
			obstacle = false;

		}
		else if ((pyArrIzq >= wyArrIzq - wallH) &&
				 ((pxArrIzq + playerW >= wxArrIzq) && (pxArrIzq <= wxArrIzq + wallW)) && (pyArrIzq - playerH <= wyArrIzq)) {

				obstacle = true;
			 }
		 
		n++;

	}


	return !obstacle;
}

void GameLogic::__processKeyboard(unsigned char key, int x, int y)
{
	if (m_pInstance)
		m_pInstance->ProcessKeyboard(key, x, y);
}

void GameLogic::__processUpKeyboard(unsigned char key, int x, int y) {
	if (m_pInstance)
		m_pInstance->ProcessUpKeyboard(key, x, y);
}

//void GameLogic::__processSpecialFunc(int key, int x, int y) {
//	if (m_pInstance)
//		m_pInstance->ProcessSpecialFunc(key, x, y);
//}

void GameLogic::Initialize()
{
	//glutSpecialFunc(__processSpecialFunc);
	glutKeyboardFunc(__processKeyboard);
	glutKeyboardUpFunc(__processUpKeyboard);

	if (maquina.GetEstado() == Inicio)
	{
		Sprite* PantallaI = new Sprite("/img/PantallaInicialStart", 0, 0, 2, 2);
		PantallaI->SetName("PantallaI");
		m_pRenderer->AddObject(PantallaI);
	}
}


//void GameLogic::ProcessSpecialFunc(int key, int x, int y)
//{
//
//	if (key = GLUT_KEY_DOWN)
//	{
//		maquina.DefinirEstado(Instrucciones);
//		cambiarEstado(Instrucciones);
//	}
//
//	
//}

void GameLogic::ProcessKeyboard(unsigned char key, int x, int y)
{
	
	switch (key)
	{

	case 13:

		maquina.DefinirEstado(Juego);
		cambiarEstado(Juego);
		break;

	case 'c':

		maquina.DefinirEstado(Instrucciones);
		cambiarEstado(Instrucciones);
		break;

	}

	Player* player1 = (Player*)m_pRenderer->ObjectByName("Player1");
	Player* player2 = (Player*)m_pRenderer->ObjectByName("Player2");

	switch (key)
	{

	case 'w':
		w = true;
		if (CanMoveUp(player1)) 
		{
			player1->SetRotation(0);
		}
		break;
	case 'a':
		a = true;
		if (CanMoveLeft(player1))
		{
			player1->SetRotation(90);
		}
		break;
	case 'd':
		d = true;
		if (CanMoveRight(player1))
		{
			player1->SetRotation(-90);
		}
		break;
	case 's':
		s = true;
		if (CanMoveDown(player1))
		{
			player1->SetRotation(180);
		}
		break;
	case 'i':
		ar2 = true;
		if (CanMoveUp(player2))
		{
			player2->SetRotation(0);
		}
		break;

	case 'k':
		ab2 = true;
		if (CanMoveDown(player2))
		{
			player2->SetRotation(180);
		}
		break;

	case 'j':
		izq2 = true;
		if (CanMoveLeft(player2))
		{
			player2->SetRotation(90);
		}
		break;

	case 'l':
		der2 = true;
		if (CanMoveRight(player2))
		{
			player2->SetRotation(-90);
		}
		break;
	case 27:
		esc = true;
	}
	
}

void GameLogic::ProcessUpKeyboard(unsigned char key, int x, int y)
{
	Player* player1 = (Player*)m_pRenderer->ObjectByName("Player1");
	Player* player2 = (Player*)m_pRenderer->ObjectByName("Player2");
	
	switch (key)
	{
		//TODO: save the state of the key
	case 'w':
		w = false;
		break;
	case 'a':
		a = false;
		break;
	case 'd':
		d = false;
		break;
	case 's':
		s = false;
		break;
	case 'i':
		ar2 = false;
		break;

	case 'k':
		ab2 = false;
		break;

	case 'j':
		izq2 = false;
		break;

	case 'l':
		der2 = false;
		break;
	case 27:
		esc = false;
	}
}

void GameLogic::cambiarEstado(Estado e)
{
	if (e == Inicio)
	{


	}

	else if (e == Juego)
	{
		Sprite* pantalla = (Sprite*)m_pRenderer->ObjectByName("PantallaI");
		m_pRenderer->RemoveObject(pantalla);
		Sprite* PantallaJ = new Sprite("/img/notebook", 0, 0, 2, 2);
		PantallaJ->SetName("PantallaJ");

		Player* player1 = new Player("/img/PLAYER1 ROSA SMALL", -0.9, 0, 0.084, 0.2);
		player1->SetName("Player1");
		Player* player2 = new Player("/img/PLAYER2 VERDEAZUL SMALL", 0.9, 0, 0.084, 0.2);
		player2->SetName("Player2");
		Wall* wall1 = new Wall("/img/wall1", 0, 0, 0.1, 1);
		wall1->SetName("wall1");
		Wall* wall2 = new Wall("/img/wall2", -0.6, 0.3, 0.5, 0.05);
		wall2->SetName("wall2");
		Wall* wall3 = new Wall("/img/wall2", 0.6, -0.3, 0.5, 0.05);
		wall3->SetName("wall3");


		Sprite* live1P1 = new Sprite("/img/heart1", 0.7, 0.9, 0.10, 0.10);
		Sprite* live2P1 = new Sprite("/img/heart1", 0.8, 0.9, 0.10, 0.10);
		Sprite* live3P1 = new Sprite("/img/heart1", 0.9, 0.9, 0.10, 0.10);
		Sprite* live1P2 = new Sprite("/img/heart1", -0.7, 0.9, 0.10, 0.10);
		Sprite* live2P2 = new Sprite("/img/heart1", -0.8, 0.9, 0.10, 0.10);
		Sprite* live3P2 = new Sprite("/img/heart1", -0.9, 0.9, 0.10, 0.10);


		
		m_pRenderer->AddObject(player1);
		m_pRenderer->AddObject(player2);
		m_pRenderer->AddObject(wall1);
		m_pRenderer->AddObject(wall2);
		m_pRenderer->AddObject(wall3);
		m_pRenderer->AddObject(live1P1);
		m_pRenderer->AddObject(live2P1);
		m_pRenderer->AddObject(live3P1);
		m_pRenderer->AddObject(live1P2);
		m_pRenderer->AddObject(live2P2);
		m_pRenderer->AddObject(live3P2);
		m_pRenderer->AddObject(PantallaJ);


	}

	else if (e == Final)
	{
		Sprite* PantallaF = new Sprite("/img/inicio", 0, 0, 10, 10);
		PantallaF->SetName("PantallaF");
		m_pRenderer->AddObject(PantallaF);

	}

	else if (e == Instrucciones)
	{
		Sprite* pantalla = (Sprite*)m_pRenderer->ObjectByName("PantallaI");
		m_pRenderer->RemoveObject(pantalla);
		Sprite* PantallaInst = new Sprite("/img/PantallaInicialControls", 0, 0, 2, 2);
		PantallaInst->SetName("PantallaInst");
		m_pRenderer->AddObject(PantallaInst);
	}

	else if (e == Salir)
	{
		Sprite* pantalla = (Sprite*)m_pRenderer->ObjectByName("PantallaInst");
		m_pRenderer->RemoveObject(pantalla);
		Sprite* PantallaIQuit = new Sprite("/img/PantallaInicialQuitGame", 0, 0, 2, 2);
		PantallaIQuit->SetName("PantallaIQuit");
		m_pRenderer->AddObject(PantallaIQuit);
	}
}

void GameLogic::ProcessEvents() //NO funciona no es ni asi esta puesto para que no de errores de compilacion y poco mas
{
	Player* player1 = (Player*)m_pRenderer->ObjectByName("Player1");
	Player* player2 = (Player*)m_pRenderer->ObjectByName("Player2");

	if (w == true)
	{
		  if(CanMoveUp(player1))
		  {
			player1->moveUp(0.034);
		  }
	}
	if (a == true)
	{
		if (CanMoveLeft(player1)) {
			player1->moveLeft(0.034);
		}
	}
	if (d == true)
	{
		if (CanMoveRight(player1)) {
			player1->moveRight(0.034);
		}
	}
	if (s == true)
	{
		if (CanMoveDown(player1))
		{
			player1->moveDown(0.034);
		}
	}
	if (ar2 == true)
	{
		if (CanMoveUp(player2)) {

			player2->moveUp(0.034);
		}
	}
	if (ab2 == true)
	{
		if (CanMoveDown(player2))
		{
			player2->moveDown(0.034);
		}
	}
	if (izq2 == true)
	{
		if (CanMoveLeft(player2))
		{
			player2->moveLeft(0.034);
		}
	}
	if (der2 == true)
	{
		if (CanMoveRight(player2))
		{
			player2->moveRight(0.034);
		}
	}
	if (esc == true)
	{
		//'Esc' key pressed. Exit the game
		exit(0);
	}
	
	
}

bool GameLogic::IsGameEnded()
{
	Player* player1 = (Player*)m_pRenderer->ObjectByName("Player1");
	Player* player2 = (Player*)m_pRenderer->ObjectByName("Player2");
	
	if (player1 == nullptr || player2 == nullptr) 
	{
		return false;
	}
	else
	{
		if (player1 != nullptr && player1->getLives() == 0 || player2 != nullptr && player2->getLives() == 0)
		{
			//	/*Timer t; 
			//	m_pRenderer->GetFrameTimer().ElapsedSeconds(true);
			//	t = m_pRenderer->GetFrameTimer();*/
			//	

			//	if (player1->getLifes() > player2->getLifes())
			//	{
			//		auto rounded = roundoff(100.123456, 3);
			//		cout << "\n";
			//		cout << "\n\n" << "El jugador 1 ha ganado con " << player1->getLifes() << "vidas restantes" << " en " << roundoff(t.ElapsedSeconds(true), 2) << " seg." << "\n\n";
			//		cout << "\n";
			//	}
			//	else
			//	{
			//		cout << "\n";
			//		cout << "\n\n" << "El jugador 2 ha ganado con " << player2->getLifes() << "vidas restantes" << " en " << roundoff(t.ElapsedSeconds(true), 2) << " seg." << "\n\n";
			//		cout << "\n";
			//}
			return true;
		}
		else
		{
			return false;
		}
	}
	 

}



//
//float GameLogic::roundoff(float value, unsigned char prec)
//{
//	float pow_10 = pow(10.0f, (float)prec);
//	return round(value * pow_10) / pow_10;
//}


//char GameLogic::GetNextPressedKey()
//{
//	//hold the output screen for some time until the user passes a key from the keyboard to exit the console screen
//	return _getch(); //
//}
//
void GameLogic::Clear()
{

	// Get the Win32 handle representing standard output.
	// This generally only has to be done once, so we make it static.
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };

	// std::cout uses a buffer to batch writes to the underlying console.
	// We need to flush that to the console because we're circumventing
	// std::cout entirely; after we clear the console, we don't want
	// stale buffered text to randomly be written out.
	std::cout.flush();

	// Figure out the current width and height of the console window
	if (!GetConsoleScreenBufferInfo(hOut, &csbi))
	{
		// TODO: Handle failure!
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

	DWORD written;

	// Flood-fill the console with spaces to clear it
	FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

	// Reset the attributes of every character to the default.
	// This clears all background colour formatting, if any.
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

	// Move the cursor back to the top left for the next sequence of writes
	SetConsoleCursorPosition(hOut, topLeft);
}
	


	
		



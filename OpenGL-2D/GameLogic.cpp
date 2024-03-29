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
#include "playsoundapi.h" 
#include "../3rd-party/SoundManager/SoundManager.h" //relative path to the main header

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
int cont = 0;

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

void GameLogic::KnockbackDown(Player* p1, Player* p2)
{
	
	for (int i = 0; i < 25; i++) {

		p1->moveDown(0.02);
		p2->moveUp(0.02);
		glutMainLoopEvent();
		glutPostRedisplay();
		glutSwapBuffers();

	}
	
}

void GameLogic::KnockbackUp(Player* p1, Player* p2)
{
	for (int i = 0; i < 25; i++) {

		p1->moveUp(0.02);
		p2->moveDown(0.02);
		glutMainLoopEvent();
		glutPostRedisplay();
		glutSwapBuffers();

	}
	
}


void GameLogic::KnockbackRight(Player* p1, Player* p2)
{
	for (int i = 0; i < 25; i++) {

		p1->moveRight(0.02);
		p2->moveLeft(0.02);
		glutMainLoopEvent();
		glutPostRedisplay();
		glutSwapBuffers();

	}

}

void GameLogic::KnockbackLeft(Player* p1, Player* p2)
{
	for (int i = 0; i < 25; i++) {
		
		p1->moveLeft(0.02);
		p2->moveRight(0.02);
		glutMainLoopEvent();
		glutPostRedisplay();
		glutSwapBuffers();

	}
	
}


void GameLogic::Knockback() {

	Player* p1 = (Player*)m_pRenderer->ObjectByName("Player1");
	Player* p2 = (Player*)m_pRenderer->ObjectByName("Player2");

	
	if (p1->GetRotation() == 0 && CanMoveDown(p1))
	{
		KnockbackDown(p1, p2);	
	}
	else if ((p1->GetRotation() == 90) && CanMoveRight(p1)) 
	{
		KnockbackRight(p1, p2);
	}
	else if ((p1->GetRotation() == 180) && CanMoveUp(p1)) 
	{
		KnockbackUp(p1, p2);
	}
	else if ((p1->GetRotation() == 270) && CanMoveLeft(p1))
	{
		KnockbackLeft(p1, p2);
	}
	
}

bool GameLogic::CanMoveRightPlayer(Player* p) {

	double pxArrIzq = p->GetX() - (p->GetYScale() / 2);
	double pyArrIzq = p->GetY() + (p->GetXScale() / 2);
	double playerW = p->GetYScale();
	double playerH = p->GetXScale();

	bool obstacle = false;
	int n = 1;
	Player* player;
	std::string playername;

	while (n < 3 && obstacle == false) {

		if (p->GetName() == "Player1")
		{
			playername = "Player2";
			player = (Player*)m_pRenderer->ObjectByName(playername);

			double wxArrIzq = 0;
			double wyArrIzq = 0;
			double playerW2 = 0;
			double playerH2 = 0;


			if (player->GetRotation() == 0 || player->GetRotation() == 180)
			{
				wxArrIzq = player->GetX() - (player->GetXScale() / 2);
				wyArrIzq = player->GetY() + (player->GetYScale() / 2);
				playerW2 = player->GetXScale();
				playerH2 = player->GetYScale();
				//----------------
				if ((pxArrIzq + playerW < wxArrIzq) && ((pyArrIzq + playerH < wyArrIzq) || (pyArrIzq > wyArrIzq + playerH2)))
				{

					obstacle = false;

				}
				else if ((pxArrIzq + playerW < wxArrIzq) && ((pyArrIzq + playerH > wyArrIzq) || (pyArrIzq < wyArrIzq + playerH2)))
				{

					obstacle = false;

				}
				else if ((pxArrIzq + playerW >= wxArrIzq) && ((pyArrIzq - playerH <= wyArrIzq) && (pyArrIzq >= wyArrIzq - playerH2)) && (pxArrIzq < wxArrIzq - playerW2))
				{

					PlaySound(NULL, NULL, 0);
					PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);

					p->SetPosition(-0.85, 0);
					p->SetRotation(270);

					player->SetPosition(0.85, 0);
					player->SetRotation(90);
					obstacle = true;
					
					player->ReduceLives();
					Kill();

				}

			}
			else //if (player->GetRotation() == 90 || player->GetRotation() == 270)
			{
				if (player->GetRotation() == 90)
				{
					wxArrIzq = player->GetX() - (player->GetXScale() + 0.010);
					wyArrIzq = player->GetY() + (player->GetXScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetXScale();
					//------------
					if ((pxArrIzq + playerW < wxArrIzq) && ((pyArrIzq + playerH < wyArrIzq) || (pyArrIzq > wyArrIzq + playerH2)))
					{

						obstacle = false;

					}
					else if ((pxArrIzq + playerW < wxArrIzq) && ((pyArrIzq + playerH > wyArrIzq) || (pyArrIzq < wyArrIzq + playerH2)))
					{

						obstacle = false;

					}
					else if ((pxArrIzq + playerW >= wxArrIzq) && ((pyArrIzq - playerH <= wyArrIzq) && (pyArrIzq >= wyArrIzq - playerH2)) && (pxArrIzq < wxArrIzq - playerW2))
					{
						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/empate.wav"), NULL, SND_LOOP | SND_ASYNC);
						Knockback();
						obstacle = true;

					}
				}
				else
				{
					wxArrIzq = player->GetX() - (player->GetXScale() + 0.010);
					wyArrIzq = player->GetY() + (player->GetXScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetXScale();
					//--------------
					if ((pxArrIzq + playerW < wxArrIzq) && ((pyArrIzq + playerH < wyArrIzq) || (pyArrIzq > wyArrIzq + playerH2)))
					{

						obstacle = false;

					}
					else if ((pxArrIzq + playerW < wxArrIzq) && ((pyArrIzq + playerH > wyArrIzq) || (pyArrIzq < wyArrIzq + playerH2)))
					{

						obstacle = false;

					}
					else if ((pxArrIzq + playerW >= wxArrIzq) && ((pyArrIzq - playerH <= wyArrIzq) && (pyArrIzq >= wyArrIzq - playerH2)) && (pxArrIzq < wxArrIzq - playerW2))
					{
						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);

						p->SetPosition(-0.85, 0);
						p->SetRotation(270);

						player->SetPosition(0.85, 0);
						player->SetRotation(90);
						obstacle = true;
				
						player->ReduceLives();
						Kill();

					}
				}

			}


		}
		else if (p->GetName() == "Player2")
		{
			playername = "Player1";
			player = (Player*)m_pRenderer->ObjectByName(playername);

			double wxArrIzq = 0;
			double wyArrIzq = 0;
			double playerW2 = 0;
			double playerH2 = 0;


			if (player->GetRotation() == 0 || player->GetRotation() == 180)
			{
				wxArrIzq = player->GetX() - (player->GetXScale() / 2);
				wyArrIzq = player->GetY() + (player->GetYScale() / 2);
				playerW2 = player->GetXScale();
				playerH2 = player->GetYScale();
				//----------------
				if ((pxArrIzq + playerW < wxArrIzq) && ((pyArrIzq + playerH < wyArrIzq) || (pyArrIzq > wyArrIzq + playerH2)))
				{

					obstacle = false;

				}
				else if ((pxArrIzq + playerW < wxArrIzq) && ((pyArrIzq + playerH > wyArrIzq) || (pyArrIzq < wyArrIzq + playerH2)))
				{

					obstacle = false;

				}
				else if ((pxArrIzq + playerW >= wxArrIzq) && ((pyArrIzq - playerH <= wyArrIzq) && (pyArrIzq >= wyArrIzq - playerH2)) && (pxArrIzq < wxArrIzq - playerW2))
				{

					PlaySound(NULL, NULL, 0);
					PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);

					p->SetPosition(0.85, 0);
					p->SetRotation(90);

					player->SetPosition(-0.85, 0);
					player->SetRotation(270);
					obstacle = true;

					player->ReduceLives();
					Kill();

				}

			}
			else //if (player->GetRotation() == 90 || player->GetRotation() == 270)
			{
				if (player->GetRotation() == 90)
				{
					wxArrIzq = player->GetX() - (player->GetXScale() + 0.010);
					wyArrIzq = player->GetY() + (player->GetXScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetXScale();
					//------------
					if ((pxArrIzq + playerW < wxArrIzq) && ((pyArrIzq + playerH < wyArrIzq) || (pyArrIzq > wyArrIzq + playerH2)))
					{

						obstacle = false;

					}
					else if ((pxArrIzq + playerW < wxArrIzq) && ((pyArrIzq + playerH > wyArrIzq) || (pyArrIzq < wyArrIzq + playerH2)))
					{

						obstacle = false;

					}
					else if ((pxArrIzq + playerW >= wxArrIzq) && ((pyArrIzq - playerH <= wyArrIzq) && (pyArrIzq >= wyArrIzq - playerH2)) && (pxArrIzq < wxArrIzq - playerW2))
					{
						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/empate.wav"), NULL, SND_LOOP | SND_ASYNC);
						Knockback();
						obstacle = true;

					}
				}
				else
				{
					wxArrIzq = player->GetX() - (player->GetXScale() + 0.010);
					wyArrIzq = player->GetY() + (player->GetXScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetXScale();
					//--------------
					if ((pxArrIzq + playerW < wxArrIzq) && ((pyArrIzq + playerH < wyArrIzq) || (pyArrIzq > wyArrIzq + playerH2)))
					{

						obstacle = false;

					}
					else if ((pxArrIzq + playerW < wxArrIzq) && ((pyArrIzq + playerH > wyArrIzq) || (pyArrIzq < wyArrIzq + playerH2)))
					{

						obstacle = false;

					}
					else if ((pxArrIzq + playerW >= wxArrIzq) && ((pyArrIzq - playerH <= wyArrIzq) && (pyArrIzq >= wyArrIzq - playerH2)) && (pxArrIzq < wxArrIzq - playerW2))
					{
						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);
						
						p->SetPosition(0.85, 0);
						p->SetRotation(90);

						player->SetPosition(-0.85, 0);
						player->SetRotation(270);
						obstacle = true;

						player->ReduceLives();
						Kill();

					}
				}

			}

		}

		n++;

	}

	return !obstacle;
}

bool GameLogic::CanMoveLeftPlayer(Player* p) {

	double pxArrIzq = p->GetX() - (p->GetYScale() / 2);
	double pyArrIzq = p->GetY() + (p->GetXScale() / 2);
	double playerW = p->GetYScale();
	double playerH = p->GetXScale();

	bool obstacle = false;
	int n = 1;
	Player* player;
	std::string playername;

	while (n < 3 && obstacle == false) {

		if (p->GetName() == "Player1")
		{
			playername = "Player2";
			player = (Player*)m_pRenderer->ObjectByName(playername);

			double wxArrIzq = 0;
			double wyArrIzq = 0;
			double playerW2 = 0;
			double playerH2 = 0;

			if (player->GetRotation() == 0 || player->GetRotation() == 180)
			{
				wxArrIzq = player->GetX() - (player->GetYScale() / 2) - 0.05;
				wyArrIzq = player->GetY() + (player->GetXScale() / 2);
				playerW2 = player->GetYScale();
				playerH2 = player->GetXScale();

				//-------
				if ((pxArrIzq > wxArrIzq + playerW2) &&
					((pyArrIzq + playerH < wyArrIzq) || (pyArrIzq > wyArrIzq + playerH2))) {

					obstacle = false;

				}
				else if ((pxArrIzq > wxArrIzq + playerW) && ((pyArrIzq + playerH > wyArrIzq) || (pyArrIzq < wyArrIzq + playerH2)))
				{
					obstacle = false;

				}
				else if ((pxArrIzq <= wxArrIzq + playerW2) && ((pyArrIzq - playerH <= wyArrIzq) && (pyArrIzq >= wyArrIzq - playerH2)) && (pxArrIzq > wxArrIzq))
				{

					PlaySound(NULL, NULL, 0);
					PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);

					p->SetPosition(-0.85, 0);
					p->SetRotation(270);

					player->SetPosition(0.85, 0);
					player->SetRotation(90);
					obstacle = true;

					player->ReduceLives();
					Kill();
				}

			}
			else //if (player->GetRotation() == 90 || player->GetRotation() == 270)
			{

				if (player->GetRotation() == 90) {

					wxArrIzq = player->GetX() + (player->GetXScale() / 2 - 0.03);
					wyArrIzq = player->GetY() + (player->GetXScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetXScale();

					//---------
					if ((pxArrIzq > wxArrIzq + playerW2) &&
						((pyArrIzq + playerH < wyArrIzq) || (pyArrIzq > wyArrIzq + playerH2))) {

						obstacle = false;

					}
					else if ((pxArrIzq > wxArrIzq + playerW) && ((pyArrIzq + playerH > wyArrIzq) || (pyArrIzq < wyArrIzq + playerH2)))
					{
						obstacle = false;

					}
					else if ((pxArrIzq <= wxArrIzq + playerW2) && ((pyArrIzq - playerH <= wyArrIzq) && (pyArrIzq >= wyArrIzq - playerH2)) && (pxArrIzq > wxArrIzq))
					{

						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);

						p->SetPosition(-0.85, 0);
						p->SetRotation(270);

						player->SetPosition(0.85, 0);
						player->SetRotation(90);
						obstacle = true;

						player->ReduceLives();
						Kill();

					}
				}
				else
				{

					wxArrIzq = player->GetX() + (player->GetXScale() / 2 - 0.03);
					wyArrIzq = player->GetY() + (player->GetXScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetXScale();
					//--------------
					if ((pxArrIzq > wxArrIzq + playerW2) &&
						((pyArrIzq + playerH < wyArrIzq) || (pyArrIzq > wyArrIzq + playerH2))) {

						obstacle = false;

					}
					else if ((pxArrIzq > wxArrIzq + playerW) && ((pyArrIzq + playerH > wyArrIzq) || (pyArrIzq < wyArrIzq + playerH2)))
					{
						obstacle = false;

					}
					else if ((pxArrIzq <= wxArrIzq + playerW2) && ((pyArrIzq - playerH <= wyArrIzq) && (pyArrIzq >= wyArrIzq - playerH2)) && (pxArrIzq > wxArrIzq))
					{
						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/empate.wav"), NULL, SND_LOOP | SND_ASYNC);

						Knockback();
						obstacle = true;

					}
				}

			}

			n++;
		}
		else if (p->GetName() == "Player2")
		{
			playername = "Player1";
			player = (Player*)m_pRenderer->ObjectByName(playername);

			double wxArrIzq = 0;
			double wyArrIzq = 0;
			double playerW2 = 0;
			double playerH2 = 0;

			if (player->GetRotation() == 0 || player->GetRotation() == 180)
			{

				wxArrIzq = player->GetX() - (player->GetYScale() / 2) - 0.05;
				wyArrIzq = player->GetY() + (player->GetXScale() / 2);
				playerW2 = player->GetYScale();
				playerH2 = player->GetXScale();

				//-------
				if ((pxArrIzq > wxArrIzq + playerW2) &&
					((pyArrIzq + playerH < wyArrIzq) || (pyArrIzq > wyArrIzq + playerH2))) {

					obstacle = false;

				}
				else if ((pxArrIzq > wxArrIzq + playerW) && ((pyArrIzq + playerH > wyArrIzq) || (pyArrIzq < wyArrIzq + playerH2)))
				{
					obstacle = false;

				}
				else if ((pxArrIzq <= wxArrIzq + playerW2) && ((pyArrIzq - playerH <= wyArrIzq) && (pyArrIzq >= wyArrIzq - playerH2)) && (pxArrIzq > wxArrIzq))
				{


					PlaySound(NULL, NULL, 0);
					PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);

					p->SetPosition(0.85, 0);
					p->SetRotation(90);

					player->SetPosition(-0.85, 0);
					player->SetRotation(270);
					obstacle = true;


					player->ReduceLives();
					Kill();
				}

			}
			else //if (player->GetRotation() == 90 || player->GetRotation() == 270)
			{

				if (player->GetRotation() == 90) {

					wxArrIzq = player->GetX() + (player->GetXScale() / 2 - 0.03);
					wyArrIzq = player->GetY() + (player->GetXScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetXScale();

					//---------
					if ((pxArrIzq > wxArrIzq + playerW2) &&
						((pyArrIzq + playerH < wyArrIzq) || (pyArrIzq > wyArrIzq + playerH2))) {

						obstacle = false;

					}
					else if ((pxArrIzq > wxArrIzq + playerW) && ((pyArrIzq + playerH > wyArrIzq) || (pyArrIzq < wyArrIzq + playerH2)))
					{
						obstacle = false;

					}
					else if ((pxArrIzq <= wxArrIzq + playerW2) && ((pyArrIzq - playerH <= wyArrIzq) && (pyArrIzq >= wyArrIzq - playerH2)) && (pxArrIzq > wxArrIzq))
					{
						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);

						p->SetPosition(0.85, 0);
						p->SetRotation(90);

						player->SetPosition(-0.85, 0);
						player->SetRotation(270);
						obstacle = true;

						player->ReduceLives();
						Kill();

					}
				}
				else
				{
					wxArrIzq = player->GetX() + (player->GetXScale() / 2 - 0.03);
					wyArrIzq = player->GetY() + (player->GetXScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetXScale();
					//--------------
					if ((pxArrIzq > wxArrIzq + playerW2) &&
						((pyArrIzq + playerH < wyArrIzq) || (pyArrIzq > wyArrIzq + playerH2))) {

						obstacle = false;

					}
					else if ((pxArrIzq > wxArrIzq + playerW) && ((pyArrIzq + playerH > wyArrIzq) || (pyArrIzq < wyArrIzq + playerH2)))
					{
						obstacle = false;

					}
					else if ((pxArrIzq <= wxArrIzq + playerW2) && ((pyArrIzq - playerH <= wyArrIzq) && (pyArrIzq >= wyArrIzq - playerH2)) && (pxArrIzq > wxArrIzq))
					{
						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/empate.wav"), NULL, SND_LOOP | SND_ASYNC);

						Knockback();
						obstacle = true;

					}
				}

			}

			n++;
		}

	}

	return !obstacle;
}

bool GameLogic::CanMoveDownPlayer(Player* p) {

	double pxArrIzq = p->GetX() - (p->GetXScale() / 2);
	double pyArrIzq = p->GetY() + (p->GetYScale() / 2);
	double playerW = p->GetXScale();
	double playerH = p->GetYScale();

	bool obstacle = false;
	int n = 1;
	Player* player;
	std::string playername;

	while (n < 4 && obstacle == false) {

		if (p->GetName() == "Player1") {
			playername = "Player2";
			player = (Player*)m_pRenderer->ObjectByName(playername);

			double wxArrIzq = 0;
			double wyArrIzq = 0;
			double playerW2 = 0;
			double playerH2 = 0;


			if (player->GetRotation() == 0 || player->GetRotation() == 180)
			{
				if (player->GetRotation() == 180)
				{
					wxArrIzq = player->GetX() - (player->GetXScale() / 2);
					wyArrIzq = player->GetY() + (player->GetYScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetYScale();

					//************************
					if ((pyArrIzq < wyArrIzq - playerH2) &&
						((pxArrIzq + playerW < wxArrIzq) || (pxArrIzq > wxArrIzq + playerW2))) {

						obstacle = false;

					}
					else if ((pyArrIzq < wyArrIzq) && ((pxArrIzq + playerW > wxArrIzq) || (pxArrIzq < wxArrIzq + playerH2)))
					{
						obstacle = false;

					}
					else if ((pyArrIzq >= wyArrIzq - playerH2) && ((pxArrIzq + playerW >= wxArrIzq) && (pxArrIzq <= wxArrIzq + playerW2)) && (pyArrIzq - playerH <= wyArrIzq))
					{
						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);

						p->SetPosition(-0.85, 0);
						p->SetRotation(270);

						player->SetPosition(0.85, 0);
						player->SetRotation(90);
						obstacle = true;

						player->ReduceLives();
						Kill();

					}
				}
				else
				{
					wxArrIzq = player->GetX() - (player->GetXScale() / 2);
					wyArrIzq = player->GetY() + (player->GetYScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetYScale();

					//****************************************************
					if ((pyArrIzq < wyArrIzq - playerH2) &&
						((pxArrIzq + playerW < wxArrIzq) || (pxArrIzq > wxArrIzq + playerW2))) {

						obstacle = false;

					}
					else if ((pyArrIzq < wyArrIzq) && ((pxArrIzq + playerW > wxArrIzq) || (pxArrIzq < wxArrIzq + playerH2)))
					{
						obstacle = false;

					}
					else if ((pyArrIzq >= wyArrIzq - playerH2) && ((pxArrIzq + playerW >= wxArrIzq) && (pxArrIzq <= wxArrIzq + playerW2)) && (pyArrIzq - playerH <= wyArrIzq))
					{
						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/empate.wav"), NULL, SND_LOOP | SND_ASYNC);

						Knockback();
						obstacle = true;


					}
				}

			}
			else //if (player->GetRotation() == 90 || player->GetRotation() == 270)
			{
				if (player->GetRotation() == 90)
				{
					wxArrIzq = player->GetX() - (player->GetXScale() / 2);
					wyArrIzq = player->GetY() + (player->GetXScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetXScale();
					//-----------------------------
					if ((pyArrIzq < wyArrIzq - playerH2) &&
						((pxArrIzq + playerW < wxArrIzq) || (pxArrIzq > wxArrIzq + playerW2))) {

						obstacle = false;

					}
					else if ((pyArrIzq < wyArrIzq) &&
						((pxArrIzq + playerW > wxArrIzq) || (pxArrIzq < wxArrIzq + playerH2)))
					{
						obstacle = false;

					}
					else if ((pyArrIzq >= wyArrIzq - playerH2) &&
						((pxArrIzq + playerW >= wxArrIzq) && (pxArrIzq <= wxArrIzq + playerW2)) && (pyArrIzq - playerH <= wyArrIzq)) {

						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);

						p->SetPosition(-0.85, 0);
						p->SetRotation(270);

						player->SetPosition(0.85, 0);
						player->SetRotation(90);
						obstacle = true;

						player->ReduceLives();
						Kill();
					}
				}
				else
				{
					wxArrIzq = player->GetX() - (player->GetXScale() / 2);
					wyArrIzq = player->GetY() + (player->GetXScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetXScale();
					//-----------------------------------
					if ((pyArrIzq < wyArrIzq - playerH2) &&
						((pxArrIzq + playerW < wxArrIzq) || (pxArrIzq > wxArrIzq + playerW2))) {

						obstacle = false;

					}
					else if ((pyArrIzq < wyArrIzq) &&
						((pxArrIzq + playerW > wxArrIzq) || (pxArrIzq < wxArrIzq + playerH2)))
					{
						obstacle = false;

					}
					else if ((pyArrIzq >= wyArrIzq - playerH2) &&
						((pxArrIzq + playerW >= wxArrIzq) && (pxArrIzq <= wxArrIzq + playerW2)) && (pyArrIzq - playerH <= wyArrIzq)) {

						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);

						p->SetPosition(-0.85, 0);
						p->SetRotation(270);

						player->SetPosition(0.85, 0);
						player->SetRotation(90);
						obstacle = true;

						player->ReduceLives();
						Kill();
					}

				}

			}

			n++;

		}
		else if (p->GetName() == "Player2")
		{
			playername = "Player1";
			player = (Player*)m_pRenderer->ObjectByName(playername);

			double wxArrIzq = 0;
			double wyArrIzq = 0;
			double playerW2 = 0;
			double playerH2 = 0;


			if (player->GetRotation() == 0 || player->GetRotation() == 180)
			{

				if (player->GetRotation() == 180)
				{
					wxArrIzq = player->GetX() - (player->GetXScale() / 2);
					wyArrIzq = player->GetY() + (player->GetYScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetYScale();

					//***************************************************
					if ((pyArrIzq < wyArrIzq - playerH2) &&
						((pxArrIzq + playerW < wxArrIzq) || (pxArrIzq > wxArrIzq + playerW2))) {

						obstacle = false;

					}
					else if ((pyArrIzq < wyArrIzq) &&
						((pxArrIzq + playerW > wxArrIzq) || (pxArrIzq < wxArrIzq + playerH2)))
					{
						obstacle = false;

					}
					else if ((pyArrIzq >= wyArrIzq - playerH2) &&
						((pxArrIzq + playerW >= wxArrIzq) && (pxArrIzq <= wxArrIzq + playerW2)) && (pyArrIzq - playerH <= wyArrIzq)) {

						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);

						p->SetPosition(0.85, 0);
						p->SetRotation(90);

						player->SetPosition(-0.85, 0);
						player->SetRotation(270);
						obstacle = true;

						player->ReduceLives();
						Kill();
					}
				}
				else
				{

					wxArrIzq = player->GetX() - (player->GetXScale() / 2);
					wyArrIzq = player->GetY() + (player->GetYScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetYScale();

					//**********************************************************************
					if ((pyArrIzq < wyArrIzq - playerH2) &&
						((pxArrIzq + playerW < wxArrIzq) || (pxArrIzq > wxArrIzq + playerW2))) {

						obstacle = false;

					}
					else if ((pyArrIzq < wyArrIzq) && ((pxArrIzq + playerW > wxArrIzq) || (pxArrIzq < wxArrIzq + playerH2)))
					{
						obstacle = false;

					}
					else if ((pyArrIzq >= wyArrIzq - playerH2) && ((pxArrIzq + playerW >= wxArrIzq) && (pxArrIzq <= wxArrIzq + playerW2)) && (pyArrIzq - playerH <= wyArrIzq))
					{
						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/empate.wav"), NULL, SND_LOOP | SND_ASYNC);

						Knockback();
						obstacle = true;


					}
				}





			}
			else //if (player->GetRotation() == 90 || player->GetRotation() == 270)
			{
				if (player->GetRotation() == 90)
				{
					wxArrIzq = player->GetX() - (player->GetXScale() / 2);
					wyArrIzq = player->GetY() + (player->GetXScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetXScale();
					//-----------------------------
					if ((pyArrIzq < wyArrIzq - playerH2) &&
						((pxArrIzq + playerW < wxArrIzq) || (pxArrIzq > wxArrIzq + playerW2))) {

						obstacle = false;

					}
					else if ((pyArrIzq < wyArrIzq) &&
						((pxArrIzq + playerW > wxArrIzq) || (pxArrIzq < wxArrIzq + playerH2)))
					{
						obstacle = false;

					}
					else if ((pyArrIzq >= wyArrIzq - playerH2) &&
						((pxArrIzq + playerW >= wxArrIzq) && (pxArrIzq <= wxArrIzq + playerW2)) && (pyArrIzq - playerH <= wyArrIzq)) {


						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);

						p->SetPosition(0.85, 0);
						p->SetRotation(90);

						player->SetPosition(-0.85, 0);
						player->SetRotation(270);
						obstacle = true;

						player->ReduceLives();
						Kill();
					}
				}
				else
				{
					wxArrIzq = player->GetX() - (player->GetXScale() / 2);
					wyArrIzq = player->GetY() + (player->GetXScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetXScale();
					//-----------------------------------
					if ((pyArrIzq < wyArrIzq - playerH2) &&
						((pxArrIzq + playerW < wxArrIzq) || (pxArrIzq > wxArrIzq + playerW2))) {

						obstacle = false;

					}
					else if ((pyArrIzq < wyArrIzq) &&
						((pxArrIzq + playerW > wxArrIzq) || (pxArrIzq < wxArrIzq + playerH2)))
					{
						obstacle = false;

					}
					else if ((pyArrIzq >= wyArrIzq - playerH2) &&
						((pxArrIzq + playerW >= wxArrIzq) && (pxArrIzq <= wxArrIzq + playerW2)) && (pyArrIzq - playerH <= wyArrIzq)) {

						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);

						p->SetPosition(0.85, 0);
						p->SetRotation(90);

						player->SetPosition(-0.85, 0);
						player->SetRotation(270);
						obstacle = true;

						player->ReduceLives();
						Kill();
					}

				}

			}

			n++;
		}

	}


	return !obstacle;
}

bool GameLogic::CanMoveUpPlayer(Player* p) {

	double pxArrIzq = p->GetX() - (p->GetXScale() / 2);
	double pyArrIzq = p->GetY() + (p->GetYScale() / 2);
	double playerW = p->GetXScale();
	double playerH = p->GetYScale();

	bool obstacle = false;
	int n = 1;
	Player* player;
	std::string playername;


	while (n < 3 && obstacle == false) {

		if (p->GetName() == "Player1")
		{
			playername = "Player2";
			player = (Player*)m_pRenderer->ObjectByName(playername);

			double wxArrIzq = 0;
			double wyArrIzq = 0;
			double playerW2 = 0;
			double playerH2 = 0;


			if (player->GetRotation() == 0 || player->GetRotation() == 180)
			{
				if (player->GetRotation() == 180)
				{
					wxArrIzq = player->GetX() - (player->GetXScale() / 2);
					wyArrIzq = player->GetY() + (player->GetYScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetYScale();

					//***************************************************
					if ((pyArrIzq < wyArrIzq - playerH2) &&
						((pxArrIzq + playerW < wxArrIzq) || (pxArrIzq > wxArrIzq + playerW2))) {

						obstacle = false;

					}
					else if ((pyArrIzq > wyArrIzq) &&
						((pxArrIzq + playerW > wxArrIzq) || (pxArrIzq < wxArrIzq + playerW2)))
					{
						obstacle = false;

					}
					else if ((pyArrIzq >= wyArrIzq - playerH2) &&
						((pxArrIzq + playerW >= wxArrIzq) && (pxArrIzq <= wxArrIzq + playerW2)) && (pyArrIzq - playerH < wyArrIzq))
					{
						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);
						Knockback();
						obstacle = true;

					}
				}
				else
				{
					wxArrIzq = player->GetX() - (player->GetXScale() / 2);
					wyArrIzq = player->GetY() + (player->GetYScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetYScale();
					//****************************************************************
					if ((pyArrIzq < wyArrIzq - playerH2) &&
						((pxArrIzq + playerW < wxArrIzq) || (pxArrIzq > wxArrIzq + playerW2))) {

						obstacle = false;

					}
					else if ((pyArrIzq > wyArrIzq) &&
						((pxArrIzq + playerW > wxArrIzq) || (pxArrIzq < wxArrIzq + playerW2)))
					{
						obstacle = false;

					}
					else if ((pyArrIzq >= wyArrIzq - playerH2) &&
						((pxArrIzq + playerW >= wxArrIzq) && (pxArrIzq <= wxArrIzq + playerW2)) && (pyArrIzq - playerH < wyArrIzq))
					{
						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);

						p->SetPosition(-0.85, 0);
						p->SetRotation(270);

						player->SetPosition(0.85, 0);
						player->SetRotation(90);
						obstacle = true;

						player->ReduceLives();
						Kill();

					}
				}

			}
			else //if (player->GetRotation() == 90 || player->GetRotation() == 270)
			{
				if (player->GetRotation() == 90)
				{
					wxArrIzq = player->GetX() - (player->GetXScale() / 2);
					wyArrIzq = player->GetY() + (player->GetXScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetXScale();
					//--------------
					if ((pyArrIzq < wyArrIzq - playerH2) &&
						((pxArrIzq + playerW < wxArrIzq) || (pxArrIzq > wxArrIzq + playerW2))) {

						obstacle = false;

					}
					else if ((pyArrIzq > wyArrIzq) &&
						((pxArrIzq + playerW > wxArrIzq) || (pxArrIzq < wxArrIzq + playerW2)))
					{
						obstacle = false;

					}
					else if ((pyArrIzq >= wyArrIzq - playerH2) &&
						((pxArrIzq + playerW >= wxArrIzq) && (pxArrIzq <= wxArrIzq + playerW2)) && (pyArrIzq - playerH < wyArrIzq))
					{
						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);

						p->SetPosition(-0.85, 0);
						p->SetRotation(270);

						player->SetPosition(0.85, 0);
						player->SetRotation(90);
						obstacle = true;

						player->ReduceLives();
						Kill();
					}
				}
				else
				{
					wxArrIzq = player->GetX() - (player->GetXScale() / 2);
					wyArrIzq = player->GetY() + (player->GetXScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetXScale();
					//----------------------
					if ((pyArrIzq < wyArrIzq - playerH2) &&
						((pxArrIzq + playerW < wxArrIzq) || (pxArrIzq > wxArrIzq + playerW2))) {

						obstacle = false;

					}
					else if ((pyArrIzq > wyArrIzq) &&
						((pxArrIzq + playerW > wxArrIzq) || (pxArrIzq < wxArrIzq + playerW2)))
					{
						obstacle = false;

					}
					else if ((pyArrIzq >= wyArrIzq - playerH2) &&
						((pxArrIzq + playerW >= wxArrIzq) && (pxArrIzq <= wxArrIzq + playerW2)) && (pyArrIzq - playerH < wyArrIzq))
					{
						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);

						p->SetPosition(-0.85, 0);
						p->SetRotation(270);

						player->SetPosition(0.85, 0);
						player->SetRotation(90);
						obstacle = true;

						player->ReduceLives();
						Kill();
					}
				}

			}

			n++;
		}
		if (p->GetName() == "Player2") {
			playername = "Player1";
			player = (Player*)m_pRenderer->ObjectByName(playername);

			double wxArrIzq = 0;
			double wyArrIzq = 0;
			double playerW2 = 0;
			double playerH2 = 0;


			if (player->GetRotation() == 0 || player->GetRotation() == 180)
			{

				if (player->GetRotation() == 180)
				{
					wxArrIzq = player->GetX() - (player->GetXScale() / 2);
					wyArrIzq = player->GetY() + (player->GetYScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetYScale();

					//*****************************

					if ((pyArrIzq < wyArrIzq - playerH2) &&
						((pxArrIzq + playerW < wxArrIzq) || (pxArrIzq > wxArrIzq + playerW2))) {

						obstacle = false;

					}
					else if ((pyArrIzq > wyArrIzq) &&
						((pxArrIzq + playerW > wxArrIzq) || (pxArrIzq < wxArrIzq + playerW2)))
					{
						obstacle = false;

					}
					else if ((pyArrIzq >= wyArrIzq - playerH2) &&
						((pxArrIzq + playerW >= wxArrIzq) && (pxArrIzq <= wxArrIzq + playerW2)) && (pyArrIzq - playerH < wyArrIzq))
					{
						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/empate.wav"), NULL, SND_LOOP | SND_ASYNC);
						Knockback();
						obstacle = true;


					}
				}
				else
				{
					wxArrIzq = player->GetX() - (player->GetXScale() / 2);
					wyArrIzq = player->GetY() + (player->GetYScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetYScale();

					//*****************************

					if ((pyArrIzq < wyArrIzq - playerH2) &&
						((pxArrIzq + playerW < wxArrIzq) || (pxArrIzq > wxArrIzq + playerW2))) {

						obstacle = false;

					}
					else if ((pyArrIzq > wyArrIzq) &&
						((pxArrIzq + playerW > wxArrIzq) || (pxArrIzq < wxArrIzq + playerW2)))
					{
						obstacle = false;

					}
					else if ((pyArrIzq >= wyArrIzq - playerH2) &&
						((pxArrIzq + playerW >= wxArrIzq) && (pxArrIzq <= wxArrIzq + playerW2)) && (pyArrIzq - playerH < wyArrIzq))
					{
						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);

						p->SetPosition(0.85, 0);
						p->SetRotation(90);

						player->SetPosition(-0.85, 0);
						player->SetRotation(270);
						obstacle = true;

						player->ReduceLives();
						Kill();



					}
				}
			}
			else //if (player->GetRotation() == 90 || player->GetRotation() == 270)
			{
				if (player->GetRotation() == 90)
				{
					wxArrIzq = player->GetX() - (player->GetXScale() / 2);
					wyArrIzq = player->GetY() + (player->GetXScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetXScale();
					//--------------
					if ((pyArrIzq < wyArrIzq - playerH2) &&
						((pxArrIzq + playerW < wxArrIzq) || (pxArrIzq > wxArrIzq + playerW2))) {

						obstacle = false;

					}
					else if ((pyArrIzq > wyArrIzq) &&
						((pxArrIzq + playerW > wxArrIzq) || (pxArrIzq < wxArrIzq + playerW2)))
					{
						obstacle = false;

					}
					else if ((pyArrIzq >= wyArrIzq - playerH2) &&
						((pxArrIzq + playerW >= wxArrIzq) && (pxArrIzq <= wxArrIzq + playerW2)) && (pyArrIzq - playerH < wyArrIzq))
					{
						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);

						p->SetPosition(0.85, 0);
						p->SetRotation(90);

						player->SetPosition(-0.85, 0);
						player->SetRotation(270);
						obstacle = true;

						player->ReduceLives();
						Kill();
					}
				}
				else
				{
					wxArrIzq = player->GetX() - (player->GetXScale() / 2);
					wyArrIzq = player->GetY() + (player->GetXScale() / 2);
					playerW2 = player->GetXScale();
					playerH2 = player->GetXScale();
					//----------------------
					if ((pyArrIzq < wyArrIzq - playerH2) &&
						((pxArrIzq + playerW < wxArrIzq) || (pxArrIzq > wxArrIzq + playerW2))) {

						obstacle = false;

					}
					else if ((pyArrIzq > wyArrIzq) &&
						((pxArrIzq + playerW > wxArrIzq) || (pxArrIzq < wxArrIzq + playerW2)))
					{
						obstacle = false;

					}
					else if ((pyArrIzq >= wyArrIzq - playerH2) &&
						((pxArrIzq + playerW >= wxArrIzq) && (pxArrIzq <= wxArrIzq + playerW2)) && (pyArrIzq - playerH < wyArrIzq))
					{
						PlaySound(NULL, NULL, 0);
						PlaySound(TEXT("snd/kill.wav"), NULL, SND_LOOP | SND_ASYNC);

						p->SetPosition(0.85, 0);
						p->SetRotation(90);

						player->SetPosition(-0.85, 0);
						player->SetRotation(270);
						obstacle = true;

						player->ReduceLives();
						Kill();
					}
				}

			}

			n++;
		}
	}
	return !obstacle;
}


//--------------------------------------------------------------------------------------------
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

void GameLogic::__processSpecialUpKeyboard(int key, int x, int y) {
	if (m_pInstance)
		m_pInstance->ProcessSpecialUpKeyboard(key, x, y);
}

void GameLogic::__processSpecialFunc(int key, int x, int y) {
	if (m_pInstance)
		m_pInstance->ProcessSpecialFunc(key, x, y);
}

void GameLogic::Initialize()
{
	glutSpecialFunc(__processSpecialFunc);
	glutKeyboardFunc(__processKeyboard);
	glutKeyboardUpFunc(__processUpKeyboard);
	glutSpecialUpFunc(__processSpecialUpKeyboard);

	
	Sprite* PantallaI = new Sprite("/img/PantallaInicialStart", 0, 0, 2, 2);
	PantallaI->SetName("PantallaI");
	m_pRenderer->AddObject(PantallaI);

	
}


void GameLogic::ProcessSpecialFunc(int key, int x, int y)
{

	switch (key)
	{

	case GLUT_KEY_DOWN:
		if (maquina.GetEstado() == Inicio)
		{
			maquina.DefinirEstado(Instrucciones);
			cambiarEstado(Instrucciones);
		}


		else if (maquina.GetEstado() == Instrucciones)
		{
			maquina.DefinirEstado(Salir);
			cambiarEstado(Salir);
		}

		else if (maquina.GetEstado() == FinalRestart)
		{
			maquina.DefinirEstado(FinalQuit);
			cambiarEstado(FinalQuit);
		}


		else if (maquina.GetEstado() == Juego)
		{
			ab2 = true;
			Player* player2 = (Player*)m_pRenderer->ObjectByName("Player2");

			if (CanMoveDown(player2))
			{
				player2->SetRotation(180);
			}
		}
		break;

	case GLUT_KEY_UP:

		if (maquina.GetEstado() == Instrucciones)
		{
			maquina.DefinirEstado(Inicio);
			cambiarEstado(Inicio);
		}

		else if (maquina.GetEstado() == Salir)
		{
			maquina.DefinirEstado(Instrucciones);
			cambiarEstado(Instrucciones);
		}

		else if (maquina.GetEstado() == FinalQuit)
		{
			maquina.DefinirEstado(FinalRestart);
			cambiarEstado(FinalRestart);
		}


		else if (maquina.GetEstado() == Juego)
		{
			ar2 = true;
			Player* player2 = (Player*)m_pRenderer->ObjectByName("Player2");
			if (CanMoveUp(player2))
			{
				player2->SetRotation(0);
			}
			
		}
		break;

		case GLUT_KEY_RIGHT:
		if (maquina.GetEstado() == P1Elige1)
		{
			maquina.DefinirEstado(P1Elige2);
			cambiarEstado(P1Elige2);
		}

		else if (maquina.GetEstado() == P1Elige2)
		{
			maquina.DefinirEstado(P1Elige3);
			cambiarEstado(P1Elige3);
		}

		else if (maquina.GetEstado() == P1Elige3)
		{
			maquina.DefinirEstado(P1Elige4);
			cambiarEstado(P1Elige4);
		}

		else if (maquina.GetEstado() == P1Elige4)
		{
			maquina.DefinirEstado(P1Elige5);
			cambiarEstado(P1Elige5);
		}

		else if (maquina.GetEstado() == P1Elige5)
		{
			maquina.DefinirEstado(P1Elige6);
			cambiarEstado(P1Elige6);
		}

		else if (maquina.GetEstado() == P1Elige6)
		{
			maquina.DefinirEstado(P1Elige7);
			cambiarEstado(P1Elige7);
		}

		else if (maquina.GetEstado() == P2Elige1)
		{
			maquina.DefinirEstado(P2Elige2);
			cambiarEstado(P2Elige2);
		}

		else if (maquina.GetEstado() == P2Elige2)
		{
			maquina.DefinirEstado(P2Elige3);
			cambiarEstado(P2Elige3);
		}

		else if (maquina.GetEstado() == P2Elige3)
		{
			maquina.DefinirEstado(P2Elige4);
			cambiarEstado(P2Elige4);
		}

		else if (maquina.GetEstado() == P2Elige4)
		{
			maquina.DefinirEstado(P2Elige5);
			cambiarEstado(P2Elige5);
		}

		else if (maquina.GetEstado() == P2Elige5)
		{
			maquina.DefinirEstado(P2Elige6);
			cambiarEstado(P2Elige6);
		}

		else if (maquina.GetEstado() == P2Elige6)
		{
			maquina.DefinirEstado(P2Elige7);
			cambiarEstado(P2Elige7);
		}

		else if (maquina.GetEstado() == Juego)
		{
			der2 = true;
			Player* player2 = (Player*)m_pRenderer->ObjectByName("Player2");

			if (CanMoveRight(player2))
			{
				player2->SetRotation(270);
			}
			break;
		}

		break;

		case GLUT_KEY_LEFT:

		if (maquina.GetEstado() == P1Elige7)
		{
			maquina.DefinirEstado(P1Elige6);
			cambiarEstado(P1Elige6);
		}

		else if (maquina.GetEstado() == P1Elige6)
		{
			maquina.DefinirEstado(P1Elige5);
			cambiarEstado(P1Elige5);
		}

		else if (maquina.GetEstado() == P1Elige5)
		{
			maquina.DefinirEstado(P1Elige4);
			cambiarEstado(P1Elige4);
		}

		else if (maquina.GetEstado() == P1Elige4)
		{
			maquina.DefinirEstado(P1Elige3);
			cambiarEstado(P1Elige3);
		}

		else if (maquina.GetEstado() == P1Elige3)
		{
			maquina.DefinirEstado(P1Elige2);
			cambiarEstado(P1Elige2);
		}

		else if (maquina.GetEstado() == P1Elige2)
		{
			maquina.DefinirEstado(P1Elige1);
			cambiarEstado(P1Elige1);
		}

		else if (maquina.GetEstado() == P2Elige7)
		{
			maquina.DefinirEstado(P2Elige6);
			cambiarEstado(P2Elige6);
		}

		else if (maquina.GetEstado() == P2Elige6)
		{
			maquina.DefinirEstado(P2Elige5);
			cambiarEstado(P2Elige5);
		}

		else if (maquina.GetEstado() == P2Elige5)
		{
			maquina.DefinirEstado(P2Elige4);
			cambiarEstado(P2Elige4);
		}

		else if (maquina.GetEstado() == P2Elige4)
		{
			maquina.DefinirEstado(P2Elige3);
			cambiarEstado(P2Elige3);
		}

		else if (maquina.GetEstado() == P2Elige3)
		{
			maquina.DefinirEstado(P2Elige2);
			cambiarEstado(P2Elige2);
		}

		else if (maquina.GetEstado() == P2Elige2)
		{
			maquina.DefinirEstado(P2Elige1);
			cambiarEstado(P2Elige1);
		}

		else if (maquina.GetEstado() == Juego)
		{
			izq2 = true;
			Player* player2 = (Player*)m_pRenderer->ObjectByName("Player2");

			if (CanMoveLeft(player2))
			{
				player2->SetRotation(90);
			}
			break;
		}

		break;
	}
	
}

void GameLogic::ProcessKeyboard(unsigned char key, int x, int y)
{

		switch (key)
		{


		case 13:

			if (maquina.GetEstado() == Inicio)
			{
				maquina.DefinirEstado(P1Elige1);
				cambiarEstado(P1Elige1);
			}

			else if (maquina.GetEstado() == Instrucciones)
			{
				maquina.DefinirEstado(Controls);
				cambiarEstado(Controls);
			}

			else if (maquina.GetEstado() == Salir)
			{
				exit(0);
			}

			else if (maquina.GetEstado() == Controls)
			{
				maquina.DefinirEstado(Instrucciones);
				cambiarEstado(Instrucciones);
			}

			else if (maquina.GetEstado() == GanadorP1)
			{
				maquina.DefinirEstado(FinalRestart);
				cambiarEstado(FinalRestart);
			}

			else if (maquina.GetEstado() == GanadorP2)
			{
				maquina.DefinirEstado(FinalRestart);
				cambiarEstado(FinalRestart);
			}

			else if (maquina.GetEstado() == FinalRestart)
			{
				maquina.DefinirEstado(Restart);
				cambiarEstado(Restart);
			}

			else if (maquina.GetEstado() == FinalQuit)
			{
				exit(0);
			}

			else if (maquina.GetEstado() == P1Elige1)
			{
				maquina.DefinirEstado(P2Elige1);
				cambiarEstado(P2Elige1);
			}

			else if (maquina.GetEstado() == P1Elige2)
			{
				maquina.DefinirEstado(P2Elige1);
				cambiarEstado(P2Elige1);
			}

			else if (maquina.GetEstado() == P1Elige3)
			{
				maquina.DefinirEstado(P2Elige1);
				cambiarEstado(P2Elige1);
			}

			else if (maquina.GetEstado() == P1Elige4)
			{
				maquina.DefinirEstado(P2Elige1);
				cambiarEstado(P2Elige1);
			}

			else if (maquina.GetEstado() == P1Elige5)
			{
				maquina.DefinirEstado(P2Elige1);
				cambiarEstado(P2Elige1);
			}

			else if (maquina.GetEstado() == P1Elige6)
			{
				maquina.DefinirEstado(P2Elige1);
				cambiarEstado(P2Elige1);
			}

			else if (maquina.GetEstado() == P1Elige7)
			{
				maquina.DefinirEstado(P2Elige1);
				cambiarEstado(P2Elige1);
			}

			else if (maquina.GetEstado() == P2Elige1)
			{
				maquina.DefinirEstado(Cuenta1);
				cambiarEstado(Cuenta1);
			}

			else if (maquina.GetEstado() == P2Elige2)
			{
				maquina.DefinirEstado(Cuenta1);
				cambiarEstado(Cuenta1);
			}

			else if (maquina.GetEstado() == P2Elige3)
			{
				maquina.DefinirEstado(Cuenta1);
				cambiarEstado(Cuenta1);
			}

			else if (maquina.GetEstado() == P2Elige4)
			{
				maquina.DefinirEstado(Cuenta1);
				cambiarEstado(Cuenta1);
			}

			else if (maquina.GetEstado() == P2Elige5)
			{
				maquina.DefinirEstado(Cuenta1);
				cambiarEstado(Cuenta1);
			}

			else if (maquina.GetEstado() == P2Elige6)
			{
				maquina.DefinirEstado(Cuenta1);
				cambiarEstado(Cuenta1);
			}

			else if (maquina.GetEstado() == P2Elige7)
			{
				maquina.DefinirEstado(Cuenta1);
				cambiarEstado(Cuenta1);
			}

			break;



		}
	

	if ((Player*)m_pRenderer->ObjectByName("Player1") != nullptr || (Player*)m_pRenderer->ObjectByName("Player2") != nullptr)
	{

		
		Player* player1 = (Player*)m_pRenderer->ObjectByName("Player1");

	
		switch (key)
		{

		case 'w':
			w = true;

			if (CanMoveUp(player1) )
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
				player1->SetRotation(270);
			}
			break;

		case 's':
			s = true;

			if (CanMoveDown(player1))
			{
				player1->SetRotation(180);
			}
			break;

		case 27:
			esc = true;
		}
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

	case 27:
		esc = false;
	
	}
}

void GameLogic::ProcessSpecialUpKeyboard(int key, int x, int y)
{
	Player* player1 = (Player*)m_pRenderer->ObjectByName("Player1");
	Player* player2 = (Player*)m_pRenderer->ObjectByName("Player2");

	switch (key)
	{
	case GLUT_KEY_UP:
		ar2 = false;
		break;

	case GLUT_KEY_DOWN:
		ab2 = false;
		break;

	case GLUT_KEY_LEFT:
		izq2 = false;
		break;

	case GLUT_KEY_RIGHT:
		der2 = false;
		break;
	}
}


void GameLogic::cambiarEstado(Estado e)
{
	
		if (e == Inicio)
		{
			Sprite* pantalla = nullptr;

			if ((Sprite*)m_pRenderer->ObjectByName("PantallaInst") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("PantallaInst");
			}

			m_pRenderer->RemoveObject(pantalla);
			Sprite* PantallaI = new Sprite("/img/PantallaInicialStart", 0, 0, 2, 2);
			PantallaI->SetName("PantallaI");
			m_pRenderer->AddObject(PantallaI);
		}

		else if (e == P1Elige1)
		{
			
			Sprite* pantalla = nullptr;

			if ((Sprite*)m_pRenderer->ObjectByName("PantallaI") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("PantallaI");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("P1Choose2") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P1Choose2");
			}
			m_pRenderer->RemoveObject(pantalla);

			Sprite* P1Choose1 = new Sprite("/img/player1choose1", 0, 0, 2, 2);
			P1Choose1->SetName("P1Choose1");
			m_pRenderer->AddObject(P1Choose1);
			color1 = "/img/PLAYER1 NARANJA SMALL";
			
			

		}

		else if (e == P1Elige2)
		{
			Sprite* pantalla = nullptr;

			if ((Sprite*)m_pRenderer->ObjectByName("P1Choose1") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P1Choose1");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("P1Choose3") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P1Choose3");
			}
			m_pRenderer->RemoveObject(pantalla);
			
			Sprite* P1Choose2 = new Sprite("/img/player1choose2", 0, 0, 2, 2);
			P1Choose2->SetName("P1Choose2");
			m_pRenderer->AddObject(P1Choose2);
			color1 = "/img/PLAYER1 AMARILLO SMALL";

		}

		else if (e == P1Elige3)
		{
			Sprite* pantalla = nullptr;

			if ((Sprite*)m_pRenderer->ObjectByName("P1Choose2") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P1Choose2");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("P1Choose4") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P1Choose4");
			}
			m_pRenderer->RemoveObject(pantalla);
		
			Sprite* P1Choose3 = new Sprite("/img/player1choose3", 0, 0, 2, 2);
			P1Choose3->SetName("P1Choose3");
			m_pRenderer->AddObject(P1Choose3);
			color1 = "/img/PLAYER1 AZUL SMALL";
		}

		else if (e == P1Elige4)
		{
			Sprite* pantalla = nullptr;

			if ((Sprite*)m_pRenderer->ObjectByName("P1Choose3") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P1Choose3");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("P1Choose5") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P1Choose5");
			}
			m_pRenderer->RemoveObject(pantalla);

			Sprite* P1Choose4 = new Sprite("/img/player1choose4", 0, 0, 2, 2);
			P1Choose4->SetName("P1Choose4");
			m_pRenderer->AddObject(P1Choose4);
			color1 = "/img/PLAYER1 LILA SMALL";
		}

		else if (e == P1Elige5)
		{
			Sprite* pantalla = nullptr;

			if ((Sprite*)m_pRenderer->ObjectByName("P1Choose4") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P1Choose4");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("P1Choose6") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P1Choose6");
			}
			m_pRenderer->RemoveObject(pantalla);

			Sprite* P1Choose5 = new Sprite("/img/player1choose5", 0, 0, 2, 2);
			P1Choose5->SetName("P1Choose5");
			m_pRenderer->AddObject(P1Choose5);
			color1 = "/img/PLAYER1 ROSA SMALL";
		}

		else if (e == P1Elige6)
		{
			Sprite* pantalla = nullptr;

			if ((Sprite*)m_pRenderer->ObjectByName("P1Choose5") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P1Choose5");
			}

			else if((Sprite*)m_pRenderer->ObjectByName("P1Choose7") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P1Choose7");
			}
			m_pRenderer->RemoveObject(pantalla);

			Sprite* P1Choose6 = new Sprite("/img/player1choose6", 0, 0, 2, 2);
			P1Choose6->SetName("P1Choose6");
			m_pRenderer->AddObject(P1Choose6);
			color1 = "/img/PLAYER1 VERDE SMALL";
		}

		else if (e == P1Elige7)
		{
			Sprite* pantalla = (Sprite*)m_pRenderer->ObjectByName("P1Choose6");
			m_pRenderer->RemoveObject(pantalla);

			Sprite* P1Choose7 = new Sprite("/img/player1choose7", 0, 0, 2, 2);
			P1Choose7->SetName("P1Choose7");
			m_pRenderer->AddObject(P1Choose7);
			color1 = "/img/PLAYER1 VERDEAZUL SMALL";
		}

		else if (e == P2Elige1)
		{
		Sprite* pantalla = nullptr;

		if ((Sprite*)m_pRenderer->ObjectByName("P1Choose1") != nullptr)
		{
			pantalla = (Sprite*)m_pRenderer->ObjectByName("P1Choose1");
		}

		else if ((Sprite*)m_pRenderer->ObjectByName("P1Choose2") != nullptr)
		{
			pantalla = (Sprite*)m_pRenderer->ObjectByName("P1Choose2");
		}

		else if ((Sprite*)m_pRenderer->ObjectByName("P1Choose3") != nullptr)
		{
			pantalla = (Sprite*)m_pRenderer->ObjectByName("P1Choose3");
		}

		else if ((Sprite*)m_pRenderer->ObjectByName("P1Choose4") != nullptr)
		{
			pantalla = (Sprite*)m_pRenderer->ObjectByName("P1Choose4");
		}

		else if ((Sprite*)m_pRenderer->ObjectByName("P1Choose5") != nullptr)
		{
			pantalla = (Sprite*)m_pRenderer->ObjectByName("P1Choose5");
		}

		else if ((Sprite*)m_pRenderer->ObjectByName("P1Choose6") != nullptr)
		{
			pantalla = (Sprite*)m_pRenderer->ObjectByName("P1Choose6");
		}

		else if ((Sprite*)m_pRenderer->ObjectByName("P1Choose7") != nullptr)
		{
			pantalla = (Sprite*)m_pRenderer->ObjectByName("P1Choose7");
		}

		else if ((Sprite*)m_pRenderer->ObjectByName("P2Choose2") != nullptr)
		{
			pantalla = (Sprite*)m_pRenderer->ObjectByName("P2Choose2");
		}
		PlaySound(TEXT("snd/player.wav"), NULL, SND_LOOP | SND_ASYNC);


		m_pRenderer->RemoveObject(pantalla);

		Sprite* P2Choose1 = new Sprite("/img/player2choose1", 0, 0, 2, 2);
		P2Choose1->SetName("P2Choose1");
		m_pRenderer->AddObject(P2Choose1);
		color2 = "/img/PLAYER2 NARANJA SMALL";

		}
		else if (e == P2Elige2)
		{
			Sprite* pantalla = nullptr;

			if ((Sprite*)m_pRenderer->ObjectByName("P2Choose1") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P2Choose1");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("P2Choose3") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P2Choose3");
			}
			m_pRenderer->RemoveObject(pantalla);

			Sprite* P2Choose2 = new Sprite("/img/player2choose2", 0, 0, 2, 2);
			P2Choose2->SetName("P2Choose2");
			m_pRenderer->AddObject(P2Choose2);
			color2 = "/img/PLAYER2 AMARILLO SMALL";

		}

		else if (e == P2Elige3)
		{
			Sprite* pantalla = nullptr;

			if ((Sprite*)m_pRenderer->ObjectByName("P2Choose2") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P2Choose2");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("P2Choose4") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P2Choose4");
			}
			m_pRenderer->RemoveObject(pantalla);

			Sprite* P2Choose3 = new Sprite("/img/player2choose3", 0, 0, 2, 2);
			P2Choose3->SetName("P2Choose3");
			m_pRenderer->AddObject(P2Choose3);
			color2 = "/img/PLAYER2 AZUL SMALL";

		}

		else if (e == P2Elige4)
		{
			Sprite* pantalla = nullptr;

			if ((Sprite*)m_pRenderer->ObjectByName("P2Choose3") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P2Choose3");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("P2Choose5") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P2Choose5");
			}
			m_pRenderer->RemoveObject(pantalla);

			Sprite* P2Choose4 = new Sprite("/img/player2choose4", 0, 0, 2, 2);
			P2Choose4->SetName("P2Choose4");
			m_pRenderer->AddObject(P2Choose4);
			color2 = "/img/PLAYER2 LILA SMALL";

		}

		else if (e == P2Elige5)
		{
			Sprite* pantalla = nullptr;

			if ((Sprite*)m_pRenderer->ObjectByName("P2Choose4") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P2Choose4");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("P2Choose6") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P2Choose6");
			}
			m_pRenderer->RemoveObject(pantalla);

			Sprite* P2Choose5 = new Sprite("/img/player2choose5", 0, 0, 2, 2);
			P2Choose5->SetName("P2Choose5");
			m_pRenderer->AddObject(P2Choose5);
			color2 = "/img/PLAYER2 ROSA SMALL";

		}

		else if (e == P2Elige6)
		{
			Sprite* pantalla = nullptr;

			if ((Sprite*)m_pRenderer->ObjectByName("P2Choose5") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P2Choose5");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("P2Choose7") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P2Choose7");
			}
			m_pRenderer->RemoveObject(pantalla);

			Sprite* P2Choose6 = new Sprite("/img/player2choose6", 0, 0, 2, 2);
			P2Choose6->SetName("P2Choose6");
			m_pRenderer->AddObject(P2Choose6);
			color2 = "/img/PLAYER2 VERDE SMALL";

		}

		else if (e == P2Elige7)
		{
			Sprite* pantalla = (Sprite*)m_pRenderer->ObjectByName("P2Choose6");
			m_pRenderer->RemoveObject(pantalla);

			Sprite* P2Choose7 = new Sprite("/img/player2choose7", 0, 0, 2, 2);
			P2Choose7->SetName("P2Choose7");
			m_pRenderer->AddObject(P2Choose7);
			color2 = "/img/PLAYER2 VERDEAZUL SMALL";

		}

		else if (e == Cuenta1)
		{
		PlaySound(TEXT("snd/player.wav"), NULL, SND_LOOP | SND_ASYNC);

			
			Sprite* pantalla = nullptr;

			if ((Sprite*)m_pRenderer->ObjectByName("P2Choose1") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P2Choose1");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("P2Choose2") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P2Choose2");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("P2Choose3") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P2Choose3");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("P2Choose4") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P2Choose4");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("P2Choose5") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P2Choose5");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("P2Choose6") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P2Choose6");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("P2Choose7") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("P2Choose7");
			}
			m_pRenderer->RemoveObject(pantalla);

			Sprite* PantallaCuenta3 = new Sprite("/img/pantalla3", 0, 0, 2, 2);
			PantallaCuenta3->SetName("PantallaCuenta3");
			m_pRenderer->AddObject(PantallaCuenta3);

			glutMainLoopEvent();


			glutPostRedisplay();
			glutSwapBuffers();

			maquina.DefinirEstado(Cuenta2);
			cambiarEstado(Cuenta2);
			
		}

		else if (e == Cuenta2)
		{
			Sleep(1000);

				m_pRenderer->RemoveObject(m_pRenderer->ObjectByName("PantallaCuenta3"));
				Sprite* PantallaCuenta2 = new Sprite("/img/pantalla2", 0, 0, 2, 2);
				PantallaCuenta2->SetName("PantallaCuenta2");
				m_pRenderer->AddObject(PantallaCuenta2);
			
				glutMainLoopEvent();


				glutPostRedisplay();
				glutSwapBuffers();

				
	
			maquina.DefinirEstado(Cuenta3);
			cambiarEstado(Cuenta3);
		}


		else if (e == Cuenta3)
		{
			
			Sleep(1000);
				m_pRenderer->RemoveObject(m_pRenderer->ObjectByName("PantallaCuenta2"));
				Sprite* PantallaCuenta1 = new Sprite("/img/pantalla1", 0, 0, 2, 2);
				PantallaCuenta1->SetName("PantallaCuenta1");
				m_pRenderer->AddObject(PantallaCuenta1);
			
				glutMainLoopEvent();


				glutPostRedisplay();
				glutSwapBuffers();

			maquina.DefinirEstado(Juego);
			cambiarEstado(Juego);
		}

		else if (e == Juego)
		{


			Sleep(1000);
				Sprite* pantalla = (Sprite*)m_pRenderer->ObjectByName("PantallaCuenta1");
				m_pRenderer->RemoveObject(pantalla);
				//PlaySound(NULL, 0, 0);
				PlaySound(TEXT("snd/sonic.wav"), NULL, SND_LOOP | SND_ASYNC);
				Sprite* PantallaJ = new Sprite("/img/notebook", 0, 0, 2, 2);
				PantallaJ->SetName("PantallaJ");

				Player* player1 = new Player(color1, -0.9, 0, 0.084, 0.2);
				player1->SetName("Player1");
				Player* player2 = new Player(color2, 0.9, 0, 0.084, 0.2);
				player2->SetName("Player2");
				Wall* wall1 = new Wall("/img/wall1", 0, 0, 0.1, 1);
				wall1->SetName("wall1");
				Wall* wall2 = new Wall("/img/wall2", -0.6, 0.3, 0.5, 0.05);
				wall2->SetName("wall2");
				Wall* wall3 = new Wall("/img/wall2", 0.6, -0.3, 0.5, 0.05);
				wall3->SetName("wall3");


				Sprite* live1P1 = new Sprite("/img/heart2", -0.6, 0.9, 0.10, 0.10);
				live1P1->SetName("live1P1");

				Sprite* live2P1 = new Sprite("/img/heart2", -0.5, 0.9, 0.10, 0.10);
				live2P1->SetName("live2P1");

				Sprite* live3P1 = new Sprite("/img/heart2", -0.4, 0.9, 0.10, 0.10);
				live3P1->SetName("live3P1");

				Sprite* live1P2 = new Sprite("/img/heart2", 0.6, 0.9, 0.10, 0.10);
				live1P2->SetName("live1P2");

				Sprite* live2P2 = new Sprite("/img/heart2", 0.5, 0.9, 0.10, 0.10);
				live2P2->SetName("live2P2");

				Sprite* live3P2 = new Sprite("/img/heart2", 0.4, 0.9, 0.10, 0.10);
				live3P2->SetName("live3P2");



				Sprite* P2Heart1 = new Sprite("/img/heart1", 0.4, 0.9, 0.10, 0.10);
				P2Heart1->SetName("P2Heart1");
				Sprite* P2Heart2 = new Sprite("/img/heart1", 0.5, 0.9, 0.10, 0.10);
				P2Heart2->SetName("P2Heart2");
				Sprite* P2Heart3 = new Sprite("/img/heart1", 0.6, 0.9, 0.10, 0.10);
				P2Heart3->SetName("P2Heart3");
				Sprite* P1Heart1 = new Sprite("/img/heart1", -0.4, 0.9, 0.10, 0.10);
				P1Heart1->SetName("P1Heart1");
				Sprite* P1Heart2 = new Sprite("/img/heart1", -0.5, 0.9, 0.10, 0.10);
				P1Heart2->SetName("P1Heart2");
				Sprite* P1Heart3 = new Sprite("/img/heart1", -0.6, 0.9, 0.10, 0.10);
				P1Heart3->SetName("P1Heart3");

				Sprite* LogoPlayer1 = new Sprite("/img/p1", -0.8, 0.9, 0.10, 0.10);

				LogoPlayer1->SetName("LogoPlayer1");
				Sprite* LogoPlayer2 = new Sprite("/img/p2", 0.8, 0.9, 0.10, 0.10);
				LogoPlayer2->SetName("LogoPlayer2");

				m_pRenderer->AddObject(P1Heart1);
				m_pRenderer->AddObject(P1Heart2);
				m_pRenderer->AddObject(P1Heart3);
				m_pRenderer->AddObject(P2Heart1);
				m_pRenderer->AddObject(P2Heart2);
				m_pRenderer->AddObject(P2Heart3);

				m_pRenderer->AddObject(LogoPlayer1);
				m_pRenderer->AddObject(LogoPlayer2);

				m_pRenderer->AddObject(live1P1);
				m_pRenderer->AddObject(live1P2);
				m_pRenderer->AddObject(live2P2);
				m_pRenderer->AddObject(live3P2);
				m_pRenderer->AddObject(live2P1);
				m_pRenderer->AddObject(live3P1);



				m_pRenderer->AddObject(player1);
				m_pRenderer->AddObject(player2);
				m_pRenderer->AddObject(wall1);
				m_pRenderer->AddObject(wall2);
				m_pRenderer->AddObject(wall3);
				m_pRenderer->AddObject(PantallaJ);
			
			


		}

		else if (e == GanadorP2)
		{

			Sprite* pantalla = (Sprite*)m_pRenderer->ObjectByName("PantallaJ");
			m_pRenderer->RemoveObject(pantalla);
			Sprite* player1 = (Sprite*)m_pRenderer->ObjectByName("Player1");
			m_pRenderer->RemoveObject(player1);
			Sprite* player2 = (Sprite*)m_pRenderer->ObjectByName("Player2");
			m_pRenderer->RemoveObject(player2);
			Sprite* wall1 = (Sprite*)m_pRenderer->ObjectByName("wall1");
			m_pRenderer->RemoveObject(wall1);
			Sprite* wall2 = (Sprite*)m_pRenderer->ObjectByName("wall2");
			m_pRenderer->RemoveObject(wall2);
			Sprite* wall3 = (Sprite*)m_pRenderer->ObjectByName("wall3");
			m_pRenderer->RemoveObject(wall3);
			Sprite* P1Heart1 = (Sprite*)m_pRenderer->ObjectByName("P1Heart1");
			m_pRenderer->RemoveObject(P1Heart1);
			Sprite* P1Heart2 = (Sprite*)m_pRenderer->ObjectByName("P1Heart2");
			m_pRenderer->RemoveObject(P1Heart2);
			Sprite* P1Heart3 = (Sprite*)m_pRenderer->ObjectByName("P1Heart3");
			m_pRenderer->RemoveObject(P1Heart3);
			Sprite* P2Heart1 = (Sprite*)m_pRenderer->ObjectByName("P2Heart1");
			m_pRenderer->RemoveObject(P2Heart1);
			Sprite* P2Heart2 = (Sprite*)m_pRenderer->ObjectByName("P2Heart2");
			m_pRenderer->RemoveObject(P2Heart2);
			Sprite* P2Heart3 = (Sprite*)m_pRenderer->ObjectByName("P2Heart3");
			m_pRenderer->RemoveObject(P2Heart3);

			Sprite* live1P1 = (Sprite*)m_pRenderer->ObjectByName("live1P1");
			m_pRenderer->RemoveObject(live1P1);
			Sprite* live1P2 = (Sprite*)m_pRenderer->ObjectByName("live1P2");
			m_pRenderer->RemoveObject(live1P2);
			Sprite* live2P2 = (Sprite*)m_pRenderer->ObjectByName("live2P2");
			m_pRenderer->RemoveObject(live2P2);
			Sprite* live3P2 = (Sprite*)m_pRenderer->ObjectByName("live3P2");
			m_pRenderer->RemoveObject(live3P2);
			Sprite* live2P1 = (Sprite*)m_pRenderer->ObjectByName("live2P1");
			m_pRenderer->RemoveObject(live2P1);
			Sprite* live3P1 = (Sprite*)m_pRenderer->ObjectByName("live3P1");
			m_pRenderer->RemoveObject(live3P1);
			Sprite* LogoPlayer1 = (Sprite*)m_pRenderer->ObjectByName("LogoPlayer1");
			m_pRenderer->RemoveObject(LogoPlayer1);
			Sprite* LogoPlayer2 = (Sprite*)m_pRenderer->ObjectByName("LogoPlayer2");
			m_pRenderer->RemoveObject(LogoPlayer2);

			Sprite* pantallaP2Wins = new Sprite("/img/Player2Wins", 0, 0, 2, 2);
			pantallaP2Wins->SetName("pantallaP2Wins");
			m_pRenderer->AddObject(pantallaP2Wins);

		}

		else if (e == GanadorP1)
		{
			Sprite* pantalla = (Sprite*)m_pRenderer->ObjectByName("PantallaJ");
			m_pRenderer->RemoveObject(pantalla);
			Sprite* player1 = (Sprite*)m_pRenderer->ObjectByName("Player1");
			m_pRenderer->RemoveObject(player1);
			Sprite* player2 = (Sprite*)m_pRenderer->ObjectByName("Player2");
			m_pRenderer->RemoveObject(player2);
			Sprite* wall1 = (Sprite*)m_pRenderer->ObjectByName("wall1");
			m_pRenderer->RemoveObject(wall1);
			Sprite* wall2 = (Sprite*)m_pRenderer->ObjectByName("wall2");
			m_pRenderer->RemoveObject(wall2);
			Sprite* wall3 = (Sprite*)m_pRenderer->ObjectByName("wall3");
			m_pRenderer->RemoveObject(wall3);
			Sprite* P1Heart1 = (Sprite*)m_pRenderer->ObjectByName("P1Heart1");
			m_pRenderer->RemoveObject(P1Heart1);
			Sprite* P1Heart2 = (Sprite*)m_pRenderer->ObjectByName("P1Heart2");
			m_pRenderer->RemoveObject(P1Heart2);
			Sprite* P1Heart3 = (Sprite*)m_pRenderer->ObjectByName("P1Heart3");
			m_pRenderer->RemoveObject(P1Heart3);
			Sprite* P2Heart1 = (Sprite*)m_pRenderer->ObjectByName("P2Heart1");
			m_pRenderer->RemoveObject(P2Heart1);
			Sprite* P2Heart2 = (Sprite*)m_pRenderer->ObjectByName("P2Heart2");
			m_pRenderer->RemoveObject(P2Heart2);
			Sprite* P2Heart3 = (Sprite*)m_pRenderer->ObjectByName("P2Heart3");
			m_pRenderer->RemoveObject(P2Heart3);

			Sprite* live1P1 = (Sprite*)m_pRenderer->ObjectByName("live1P1");
			m_pRenderer->RemoveObject(live1P1);
			Sprite* live1P2 = (Sprite*)m_pRenderer->ObjectByName("live1P2");
			m_pRenderer->RemoveObject(live1P2);
			Sprite* live2P2 = (Sprite*)m_pRenderer->ObjectByName("live2P2");
			m_pRenderer->RemoveObject(live2P2);
			Sprite* live3P2 = (Sprite*)m_pRenderer->ObjectByName("live3P2");
			m_pRenderer->RemoveObject(live3P2);
			Sprite* live2P1 = (Sprite*)m_pRenderer->ObjectByName("live2P1");
			m_pRenderer->RemoveObject(live2P1);
			Sprite* live3P1 = (Sprite*)m_pRenderer->ObjectByName("live3P1");
			m_pRenderer->RemoveObject(live3P1);
			Sprite* LogoPlayer1 = (Sprite*)m_pRenderer->ObjectByName("LogoPlayer1");
			m_pRenderer->RemoveObject(LogoPlayer1);
			Sprite* LogoPlayer2 = (Sprite*)m_pRenderer->ObjectByName("LogoPlayer2");
			m_pRenderer->RemoveObject(LogoPlayer2);


			Sprite* pantallaP1Wins = new Sprite("/img/Player1Wins", 0, 0, 2, 2);
			pantallaP1Wins->SetName("pantallaP1Wins");
			m_pRenderer->AddObject(pantallaP1Wins);

		}

		else if (e == Instrucciones)
		{
			Sprite* pantalla = nullptr;

			if ((Sprite*)m_pRenderer->ObjectByName("PantallaI") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("PantallaI");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("PantallaIQuit") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("PantallaIQuit");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("PantallaC") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("PantallaC");
			}

			m_pRenderer->RemoveObject(pantalla);
			Sprite* PantallaInst = new Sprite("/img/PantallaInicialControls", 0, 0, 2, 2);
			PantallaInst->SetName("PantallaInst");
			m_pRenderer->AddObject(PantallaInst);
		}


		else if (e == Controls)
		{
			Sprite* pantalla = (Sprite*)m_pRenderer->ObjectByName("PantallaInst");
			m_pRenderer->RemoveObject(pantalla);
			Sprite* PantallaC = new Sprite("/img/Controls", 0, 0, 2, 2);
			PantallaC->SetName("PantallaC");
			m_pRenderer->AddObject(PantallaC);
		}


		else if (e == Salir)
		{
			Sprite* pantalla = (Sprite*)m_pRenderer->ObjectByName("PantallaInst");
			m_pRenderer->RemoveObject(pantalla);
			Sprite* PantallaIQuit = new Sprite("/img/PantallaInicialQuitGame", 0, 0, 2, 2);
			PantallaIQuit->SetName("PantallaIQuit");
			m_pRenderer->AddObject(PantallaIQuit);
		}

		else if (e == FinalRestart)
		{
			Sprite* pantalla = nullptr;

			if ((Sprite*)m_pRenderer->ObjectByName("pantallaP1Wins") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("pantallaP1Wins");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("pantallaP2Wins") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("pantallaP2Wins");
			}

			else if ((Sprite*)m_pRenderer->ObjectByName("PantallaFQuit") != nullptr)
			{
				pantalla = (Sprite*)m_pRenderer->ObjectByName("PantallaFQuit");
			}

			m_pRenderer->RemoveObject(pantalla);
			Sprite* PantallaFRestart = new Sprite("/img/PantallaFinalRestart", 0, 0, 2, 2);
			PantallaFRestart->SetName("PantallaFRestart");
			m_pRenderer->AddObject(PantallaFRestart);
		}

		else if (e == FinalQuit)
		{
			Sprite* pantalla = (Sprite*)m_pRenderer->ObjectByName("PantallaFRestart");
			m_pRenderer->RemoveObject(pantalla);
			Sprite* PantallaFQuit = new Sprite("/img/PantallaFinalQuitGame", 0, 0, 2, 2);
			PantallaFQuit->SetName("PantallaFQuit");
			m_pRenderer->AddObject(PantallaFQuit);
		}

		else if (e == Restart)
		{
			Sprite* pantalla = (Sprite*)m_pRenderer->ObjectByName("PantallaFRestart");
			m_pRenderer->RemoveObject(pantalla);
			Initialize();
			maquina.DefinirEstado(Inicio);
		}

	}

	void GameLogic::ProcessEvents() 
	{
		if ((Player*)m_pRenderer->ObjectByName("Player1") != nullptr && (Player*)m_pRenderer->ObjectByName("Player2") != nullptr)
		{

			Player* player1 = (Player*)m_pRenderer->ObjectByName("Player1");
			Player* player2 = (Player*)m_pRenderer->ObjectByName("Player2");

		
		if (w == true)
		{
			if (CanMoveUp(player1) && CanMoveUpPlayer(player1))
			{
				player1->moveUp(0.034);
			}
		}
		if (a == true)
		{
			if (CanMoveLeft(player1) && CanMoveLeftPlayer(player1))
			{
				player1->moveLeft(0.034);
			}
		}
		if (d == true)
		{
			if (CanMoveRight(player1) && CanMoveRightPlayer(player1))
			{
				player1->moveRight(0.034);
			}

		}
		if (s == true)
		{
			if (CanMoveDown(player1) && CanMoveDownPlayer(player1))
			{
				player1->moveDown(0.034);
			}
		}
		if (ar2 == true)
		{
			if (CanMoveUp(player2) && CanMoveUpPlayer(player2)) {

				player2->moveUp(0.034);
			}
		}
		if (ab2 == true)
		{
			if (CanMoveDown(player2) && CanMoveDownPlayer(player2))
			{
				player2->moveDown(0.034);
			}
		}
		if (izq2 == true)
		{
			if (CanMoveLeft(player2) && CanMoveLeftPlayer(player2))
			{
				player2->moveLeft(0.034);
			}
		}
		if (der2 == true)
		{
			if (CanMoveRight(player2) && CanMoveRightPlayer(player2))
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

	}

	void GameLogic::Kill() {

		Player* player1 = (Player*)m_pRenderer->ObjectByName("Player1");
		Player* player2 = (Player*)m_pRenderer->ObjectByName("Player2");



		int livesJ1 = player1->getLives();
		int livesJ2 = player2->getLives();


		if (livesJ2 == 2) {

			Sprite* P2Heart1 = (Sprite*)m_pRenderer->ObjectByName("P2Heart1");
			m_pRenderer->RemoveObject(P2Heart1);



		}
		else if (livesJ2 == 1) {

			Sprite* P2Heart2 = (Sprite*)m_pRenderer->ObjectByName("P2Heart2");
			m_pRenderer->RemoveObject(P2Heart2);



		}
		else if (livesJ2 == 0) {

			Sprite* P2Heart3 = (Sprite*)m_pRenderer->ObjectByName("P2Heart3");
			m_pRenderer->RemoveObject(P2Heart3);



		}
		else if (livesJ1 == 2) {

			Sprite* P1Heart3 = (Sprite*)m_pRenderer->ObjectByName("P1Heart3");
			m_pRenderer->RemoveObject(P1Heart3);


		}
		else if (livesJ1 == 1) {


			Sprite* P1Heart2 = (Sprite*)m_pRenderer->ObjectByName("P1Heart2");
			m_pRenderer->RemoveObject(P1Heart2);


		}
		else if (livesJ1 == 0) {

			Sprite* P1Heart1 = (Sprite*)m_pRenderer->ObjectByName("P1Heart1");
			m_pRenderer->RemoveObject(P1Heart1);


		}






	}

	bool GameLogic::IsGameEnded()
	{
		if ((Player*)m_pRenderer->ObjectByName("Player1") == nullptr || (Player*)m_pRenderer->ObjectByName("Player2") == nullptr)
		{

			return false;

		}
		else
		{
			Player* player1 = (Player*)m_pRenderer->ObjectByName("Player1");
			Player* player2 = (Player*)m_pRenderer->ObjectByName("Player2");

			if (player1->getLives() == 0) {
				Sprite* P1Heart1 = (Sprite*)m_pRenderer->ObjectByName("P1Heart1");
				m_pRenderer->RemoveObject(P1Heart1);
				//return true;
				MostrarGanador();

			}
			if (player2->getLives() == 0) {

				Sprite* P2Heart3 = (Sprite*)m_pRenderer->ObjectByName("P2Heart3");
				m_pRenderer->RemoveObject(P2Heart3);
				//return true;
				MostrarGanador();
			}


			if (player1->getLives() == 0 || player2->getLives() == 0)
			{

				if (cont != 0)
				{
					//MostrarGanador();
					return false;
				}
				else
				{

					cont++;
					return false;

				}

			}
		}

		return false;

	}

	
	void GameLogic::MostrarGanador()
	{
		Player* player1 = (Player*)m_pRenderer->ObjectByName("Player1");
		Player* player2 = (Player*)m_pRenderer->ObjectByName("Player2");

		if (player1->getLives() == 0)
		{
			PlaySound(NULL, NULL, 0);
			PlaySound(TEXT("snd/victoria.wav"), NULL, SND_LOOP | SND_ASYNC);
			maquina.DefinirEstado(GanadorP2);
			cambiarEstado(GanadorP2);
		}

		else if (player2->getLives() == 0)
		{
			PlaySound(NULL, NULL, 0);
			PlaySound(TEXT("snd/victoria.wav"), NULL, SND_LOOP | SND_ASYNC);
			maquina.DefinirEstado(GanadorP1);
			cambiarEstado(GanadorP1);
		}
	}
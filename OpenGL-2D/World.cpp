#include "stdafx.h"
#include "World.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <chrono>
#include <thread>
#include <fstream>
#include "stdafx.h"
#include <stdio.h>
#include <istream>
#include <fstream>
#include "Player.h"
#include "World.h"
#include "Renderer.h"
using namespace std;

World* World::m_pInstance = nullptr;


World::World(Renderer renderer) {
	m_pInstance = this;

	//initialize the timer. We want to display the time elapsed since the game began in draw()
	m_timer.start();

	//TODO: initalize everything else
	//test objects
	pPlayer1 = new Player();
	pPlayer1->setColor(255, 0, 0);
	pPlayer1->setPosition(-0.75, 0.0);
	pPlayer1->setRotation(0.0);
	pPlayer1->setSize(0.2);
	pPlayer1->setDepth(1.5);
	renderer.addObject(pPlayer1);

	pPlayer2 = new Player();
	pPlayer2->setColor(0, 255, 0);
	pPlayer2->setPosition(0.75, 0.0);
	pPlayer2->setRotation(0.0);
	pPlayer2->setSize(0.2);
	pPlayer2->setDepth(1.3);
	renderer.addObject(pPlayer2);
}


World::~World() {
}

Player& World::getPlayer(int p)
{
	if (p == 1)
		return *pPlayer1;
	else if (p == 2)
		return *pPlayer2;
}

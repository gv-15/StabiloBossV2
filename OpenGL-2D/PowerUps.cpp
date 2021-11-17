#include "stdafx.h"
#include "PowerUps.h"
#include "World.h"
#include "Sprite.h"

PowerUps::PowerUps(string imgagedir)
:Sprite(imgagedir, m_posx, m_posy)
{
	tipo = nullptr;
}

PowerUps::~PowerUps()
{
}


void PowerUps::setType(string tipo)
{
    if (tipo._Equal ("fast"))
    {
        movefaster();
    }
    else if (tipo._Equal("slow"))
    {
        moveslower();
    }
    else if (tipo._Equal("die"))
    {
        youdie();
    }
    else if (tipo._Equal("teleport"))
    {
        teleport();
    }
    else if (tipo._Equal("ignore"))
    {
        ignoreObstacle();
    }
};


void PowerUps::movefaster()
{

}


void PowerUps::moveslower()
{

}


void PowerUps::youdie()
{

}


void PowerUps::teleport()
{

}


void PowerUps::ignoreObstacle()
{

}


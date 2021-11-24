#include "stdafx.h"
#include "PowerUp.h"
#include "World.h"
#include "Sprite.h"

PowerUp::PowerUp(string dirimg, double m_posx1, double m_posy1, double x1, double y2)
:Sprite(dirimg, m_posx1, m_posy1, x1, y2)
{
	tipo = nullptr;
}

PowerUp::~PowerUp()
{
}

string PowerUp::GetType()
{
    return tipo;
};

void PowerUp::setActivated(bool b)
{
    Activated = b;
};

void PowerUp::Activate(string tipo)
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


void PowerUp::movefaster()
{
    //Player->Velocidad *= 1.2;
}


void PowerUp::moveslower()
{

}


void PowerUp::youdie()
{

}


void PowerUp::teleport()
{

}


void PowerUp::ignoreObstacle()
{

}


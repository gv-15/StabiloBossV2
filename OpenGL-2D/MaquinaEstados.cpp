#include "MaquinaEstados.h"
#include "../3rd-party/glew-2.0.0/src/glew.h"
#include "../3rd-party/SOIL/src/SOIL.h"
#include <iostream>
#include "Renderer.h"
#include "Wall.h"
#include "Player.h"

MaquinaEstados::MaquinaEstados(Renderer* pRenderer)
{
    m_Renderer = pRenderer;
}

void MaquinaEstados::DefinirEstado(Estado e)
{

    if (e == Inicio)
    { 
        Sprite* PantallaI = new Sprite("/img/inicio", 0, 0, 10, 10);
        PantallaI->SetName("PantallaI");
        m_Renderer->AddObject(PantallaI);
    }
    
    else if (e == Juego)
    {
        Sprite* PantallaJ = new Sprite("/img/notebook", 0, 0, 10, 10);
        PantallaJ->SetName("PantallaJ");
       
        Player* player1 = new Player("/img/PLAYER1 ROSA SMALL", 0.9, 0, 0.084, 0.2);
        player1->SetName("Player1");
        Player* player2 = new Player("/img/PLAYER2 VERDEAZUL SMALL", -0.9, 0, 0.084, 0.2);
        player2->SetName("Player2");
        Wall* wall1 = new Wall("/img/wall1", 0, 0, 1, 1);
        wall1->SetName("wall1");
        Wall* wall2 = new Wall("/img/wall2", -0.6, 0.4, 0.5, 0.3);
        wall2->SetName("wall2");
        Wall* wall3 = new Wall("/img/wall3", 0.7, 0.3, 0.6, 0.4);
        wall3->SetName("wall3");
        Timer* timer = new Timer("/img/timer", 0.2, 0.2, 0.6, 0.4);

        m_Renderer->AddObject(PantallaJ);
        m_Renderer->AddObject(player1);
        m_Renderer->AddObject(player2);
        m_Renderer->AddObject(wall1);
        m_Renderer->AddObject(wall2);
        m_Renderer->AddObject(wall3);
        ////renderer.AddObject(&timer);

        timer->Start();
    }

    else if (e == Final)
    {
        Sprite* PantallaF = new Sprite("/img/inicio", 0, 0, 10, 10);
        PantallaF->SetName("PantallaF");
        m_Renderer->AddObject(PantallaF);

    }

    else if (e == Instrucciones)
    {
      
        Sprite* PantallaInst = new Sprite("/img/inicio", 0, 0, 10, 10);
        PantallaInst->SetName("PantallaInstrucciones");
        m_Renderer->AddObject(PantallaInst);
    }
}
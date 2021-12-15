#include "MaquinaEstados.h"
#include "../3rd-party/glew-2.0.0/src/glew.h"
#include "../3rd-party/SOIL/src/SOIL.h"
#include <iostream>
#include "Renderer.h"
#include "Wall.h"
#include "Player.h"
#include "../3rd-party/freeglut3/include/GL/freeglut_std.h"

MaquinaEstados* MaquinaEstados::m_pInstance = nullptr;

MaquinaEstados::MaquinaEstados()
{
    estado = Inicio;
    // m_pInstance = this;
}


void MaquinaEstados::Initialize()
{
    glutKeyboardFunc(__processKeyboard);
    glutKeyboardUpFunc(__processUpKeyboard);

}

void MaquinaEstados::__processKeyboard(unsigned char key, int x, int y)
{
    if (m_pInstance)
        m_pInstance->ProcessKeyboard(key, x, y);
}

void MaquinaEstados::__processUpKeyboard(unsigned char key, int x, int y) {
    if (m_pInstance)
        m_pInstance->ProcessUpKeyboard(key, x, y);
}

void MaquinaEstados::ProcessKeyboard(unsigned char key, int x, int y)
{

}

void MaquinaEstados::ProcessUpKeyboard(unsigned char key, int x, int y)
{

}

Estado MaquinaEstados::GetEstado()
{
    return estado;
}

void MaquinaEstados::DefinirEstado(Estado e)
{

    if (e == Inicio)

        estado = Inicio;

    else if (e == Instrucciones)

        estado = Instrucciones;

    else if (e == Controls)

        estado = Controls;


    else if (e == Juego)

        estado = Juego;

    else if (e == Salir)

        estado = Salir;

    else if (e == GanadorP2)

        estado = GanadorP2;

    else if (e == GanadorP1)

        estado = GanadorP1;

    else if (e == FinalRestart)

        estado = FinalRestart;

    else if (e == Restart)

        estado = Restart;

    else if (e == FinalQuit)

        estado = FinalQuit;
}
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

    else if (e == Cuenta1)

        estado = Cuenta1;

    else if (e == Cuenta2)

        estado = Cuenta2;

    else if (e == Cuenta3)

        estado = Cuenta3;

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

    else if (e == P1Elige1)

        estado = P1Elige1;

    else if (e == P1Elige2)

        estado = P1Elige2;

    else if (e == P1Elige3)

        estado = P1Elige3;

    else if (e == P1Elige4)

        estado = P1Elige4;

    else if (e == P1Elige5)

        estado = P1Elige5;

    else if (e == P1Elige6)

        estado = P1Elige6;

    else if (e == P1Elige7)

        estado = P1Elige7;

    else if (e == P2Elige1)

        estado = P2Elige1;

    else if (e == P2Elige2)

        estado = P2Elige2;

    else if (e == P2Elige3)

        estado = P2Elige3;

    else if (e == P2Elige4)

        estado = P2Elige4;

    else if (e == P2Elige5)

        estado = P2Elige5;

    else if (e == P2Elige6)

        estado = P2Elige6;
    
    else if (e == P2Elige7)

        estado = P2Elige7;
}
#pragma once

enum Estado { Inicio, Juego, FinalRestart, Instrucciones, Controls, Salir, GanadorP2, GanadorP1, Restart, FinalQuit,
    Cuenta1 ,Cuenta2, Cuenta3, P1Elige1, P1Elige2, P1Elige3, P1Elige4, P1Elige5, P1Elige6, P1Elige7,
    P2Elige1, P2Elige2, P2Elige3, P2Elige4, P2Elige5, P2Elige6, P2Elige7};

class Renderer;

class MaquinaEstados
{
    static MaquinaEstados* m_pInstance;

    Renderer* m_pRenderer;

    static void __processKeyboard(unsigned char key, int x, int y);
    static void __processUpKeyboard(unsigned char key, int x, int y);
    void ProcessKeyboard(unsigned char key, int x, int y);
    void ProcessUpKeyboard(unsigned char key, int x, int y);

    Estado estado;

public:

    MaquinaEstados();

    void Initialize();

    void DefinirEstado(Estado estado);

    Estado GetEstado();

};

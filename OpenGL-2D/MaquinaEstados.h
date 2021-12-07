#pragma once

enum Estado { Inicio, Juego, Final1, Final2, Instrucciones, Controls, Salir };

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


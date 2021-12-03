#pragma once

enum Estado { Inicio, Juego, Final, Instrucciones, Salir };

class Renderer;

class MaquinaEstados
{
    Renderer* m_Renderer;

    Estado estado;

    public:

    MaquinaEstados(Renderer* pRenderer);

    void DefinirEstado(Estado estado);
   
};


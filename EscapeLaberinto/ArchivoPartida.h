#pragma once
#include "GuardarPartida.h"


class ArchivoPartida
{

    private:
        char nombreArchivo[30];

    public:
        ArchivoPartida(const char* nombre = "partida_guardada.dat");
        bool guardarPartida(GuardarPartida partida);
        GuardarPartida cargarPartida();
        
        bool existePartidaGuardada();
        bool eliminarPartidaGuardada();
    };

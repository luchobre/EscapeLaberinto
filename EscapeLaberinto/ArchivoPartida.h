#pragma once
#include "GuardarPartida.h"
#include <string>

class ArchivoPartida {
private:
    std::string nombreArchivo;

public:
    ArchivoPartida(const std::string& nombre);

    bool guardarPartida(const GuardarPartida& partida);
    GuardarPartida cargarPartida();
    bool existePartidaGuardada() const;
    void eliminarPartidaGuardada();
};


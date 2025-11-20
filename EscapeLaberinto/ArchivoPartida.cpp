#include "ArchivoPartida.h"
#include <fstream>
#include <cstdio>

ArchivoPartida::ArchivoPartida(const std::string& nombre) : nombreArchivo(nombre) {}

bool ArchivoPartida::guardarPartida(const GuardarPartida& partida) {
    std::ofstream file(nombreArchivo, std::ios::binary);
    if (!file.is_open()) return false;
    file.write(reinterpret_cast<const char*>(&partida), sizeof(GuardarPartida));
    file.close();
    return true;
}
GuardarPartida ArchivoPartida::cargarPartida() {
    GuardarPartida partida;
    std::ifstream file(nombreArchivo, std::ios::binary);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&partida), sizeof(GuardarPartida));
        file.close();
    }
    return partida;
}

bool ArchivoPartida::existePartidaGuardada() const {
    std::ifstream file(nombreArchivo);
    return file.good();
}

void ArchivoPartida::eliminarPartidaGuardada() {
    std::remove(nombreArchivo.c_str());
}

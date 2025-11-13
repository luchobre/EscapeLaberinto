#define _CRT_SECURE_NO_WARNINGS //PARA QUE VISUAL STUDIO TRABAJE BIEN CON LAS FUNCIONES DE ARCHIVO Y NO DE ERROR DE SEGURIDAD
#include <iostream>
#include <cstring>
#include "ArchivoPartida.h"

using namespace std;

ArchivoPartida::ArchivoPartida(const char* nombre) {
    strcpy(nombreArchivo, nombre);
}

bool ArchivoPartida::guardarPartida(GuardarPartida partida) {
    FILE* archivo = fopen(nombreArchivo, "wb");
    if (archivo == nullptr) {
        cout << "No se pudo abrir el archivo" << endl;
        return false;
    }
    bool exito = fwrite(&partida, sizeof(GuardarPartida), 1, archivo);
    fclose(archivo);

    return exito;
}

GuardarPartida ArchivoPartida::cargarPartida() {
    GuardarPartida partida;
    FILE* archivo = fopen(nombreArchivo, "rb");

    if (archivo == nullptr) {
        cout << "No se pudo abrir el archivo" << endl;
        return partida;
    }

    fread(&partida, sizeof(GuardarPartida), 1, archivo);
    fclose(archivo);

    return partida;
}

bool ArchivoPartida::existePartidaGuardada() {
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (archivo == nullptr) {
        return false;
    }
    fclose(archivo);
    return true;
}

bool ArchivoPartida::eliminarPartidaGuardada() {
    return remove(nombreArchivo) == 0;
}
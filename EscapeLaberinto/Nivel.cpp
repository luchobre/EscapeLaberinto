#include "Nivel.h"

Nivel::Nivel() {
    nivelActual = 1;
    puntajeActual = 0;
    puntajeNecesario = 8;  // Para pasar a nivel 2
}

void Nivel::agregarPuntos(int p) {
    puntajeActual += p;
}

bool Nivel::checkSubirNivel() {
    if (puntajeActual >= puntajeNecesario) {
        nivelActual++;

        // Reset puntos
        puntajeActual = 0;

        // Nuevo requisito según nivel
        if (nivelActual == 2) {
            puntajeNecesario = 3;  // Para pasar del 2 al 3
        }
        else if (nivelActual == 3) {
            puntajeNecesario = 999999; // Último nivel, no sube más
        }

        return true; // Indicamos que hubo subida de nivel
    }

    return false;
}

int Nivel::getNivelActual() const { return nivelActual; }
int Nivel::getPuntajeActual() const { return puntajeActual; }
int Nivel::getPuntajeNecesario() const { return puntajeNecesario; }



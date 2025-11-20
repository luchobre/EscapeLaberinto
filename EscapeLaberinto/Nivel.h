#pragma once

class Nivel {
private:
    int nivelActual;
    int puntajeActual;
    int puntajeNecesario;

public:
    Nivel();

    void agregarPuntos(int p);
    bool checkSubirNivel();

    int getNivelActual() const;
    int getPuntajeActual() const;
    int getPuntajeNecesario() const;
};




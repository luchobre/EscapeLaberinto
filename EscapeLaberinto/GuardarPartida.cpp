#include "GuardarPartida.h"

GuardarPartida::GuardarPartida() {
    //VALORES "POR DEFECTO" PARA EVITAR BASURA
    pjX = 50.0f;
    pjY = 50.0f;
    pjVelocidadX = 2.0f;  
    pjVelocidadY = 2.0f;

      
    enemigoX = 740.0f;
    enemigoY = 500.0f;
    enemigoDirX = 1.0f;  
    enemigoDirY = 0.0f;
    enemigoVelocidad = 3.3f; 

    itemX = 0.0f;
    itemY = 0.0f;
    itemPowerUpX = 0.0f;
    itemPowerUpY = 0.0f;

    puntuacion = 0;
    muertes = 0;
    timerPowerUp = 60 * 5;
    gameOver = false;
}

//SETTER PARA GUARDAR DATOS EN EL OBJETO DESDE EL JUEGO
void GuardarPartida::setDatosPersonaje(float x, float y, float velX, float velY) {
    pjX = x;
    pjY = y;
    pjVelocidadX = velX;
    pjVelocidadY = velY;
}

void GuardarPartida::setDatosEnemigo(float x, float y, float dirX, float dirY, float vel) {
    enemigoX = x;
    enemigoY = y;
    enemigoDirX = dirX;
    enemigoDirY = dirY;
    enemigoVelocidad = vel;
}

void GuardarPartida::setDatosItemNormal(float x, float y) {
    itemX = x;
    itemY = y;
}

void GuardarPartida::setDatosItemPowerUp(float x, float y) {
    itemPowerUpX = x;
    itemPowerUpY = y;
}

void GuardarPartida::setEstadoJuego(int pts, int mts, int timer, bool go) {
    puntuacion = pts;
    muertes = mts;
    timerPowerUp = timer;
    gameOver = go;
}

//GETTERS PARA DARLE LOS DATOS A LOS OBJETOS DEL JUEGO

void GuardarPartida::getDatosPersonaje(float& x, float& y, float& velX, float& velY) {
    x = pjX;
    y = pjY;
    velX = pjVelocidadX;
    velY = pjVelocidadY;
}

void GuardarPartida::getDatosEnemigo(float& x, float& y, float& dirX, float& dirY, float& vel) {
    x = enemigoX;
    y = enemigoY;
    dirX = enemigoDirX;
    dirY = enemigoDirY;
    vel = enemigoVelocidad;
}

void GuardarPartida::getDatosItemNormal(float& x, float& y) {
    x = itemX;
    y = itemY;
}

void GuardarPartida::getDatosItemPowerUp(float& x, float& y) {
    x = itemPowerUpX;
    y = itemPowerUpY;
}

void GuardarPartida::getEstadoJuego(int& pts, int& mts, int& timer, bool& go) {
    pts = puntuacion;
    mts = muertes;
    timer = timerPowerUp;
    go = gameOver;
}
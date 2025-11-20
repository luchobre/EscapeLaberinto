#include "GuardarPartida.h"

GuardarPartida::GuardarPartida() :
    pjX(0), pjY(0), pjVelocidadX(0), pjVelocidadY(0),
    enemigoX(0), enemigoY(0), enemigoDirX(0), enemigoDirY(0), enemigoVelocidad(0),
    itemX(0), itemY(0), itemPowerUpX(0), itemPowerUpY(0),
    puntuacion(0), muertes(0), timerPowerUp(0), gameOver(false)
{
}

void GuardarPartida::setDatosPersonaje(float x, float y, float velX, float velY) {
    pjX = x; pjY = y;
    pjVelocidadX = velX; pjVelocidadY = velY;
}

void GuardarPartida::setDatosEnemigo(float x, float y, float dirX, float dirY, float vel) {
    enemigoX = x; enemigoY = y;
    enemigoDirX = dirX; enemigoDirY = dirY;
    enemigoVelocidad = vel;
}

void GuardarPartida::setDatosItemNormal(float x, float y) {
    itemX = x; itemY = y;
}

void GuardarPartida::setDatosItemPowerUp(float x, float y) {
    itemPowerUpX = x; itemPowerUpY = y;
}

void GuardarPartida::setEstadoJuego(int pts, int mts, int timer, bool estado) {
    puntuacion = pts;
    muertes = mts;
    timerPowerUp = timer;
    gameOver = estado;
}

void GuardarPartida::getDatosPersonaje(float& x, float& y, float& velX, float& velY) {
    x = pjX; y = pjY;
    velX = pjVelocidadX; velY = pjVelocidadY;
}

void GuardarPartida::getDatosEnemigo(float& x, float& y, float& dirX, float& dirY, float& vel) {
    x = enemigoX; y = enemigoY;
    dirX = enemigoDirX; dirY = enemigoDirY;
    vel = enemigoVelocidad;
}

void GuardarPartida::getDatosItemNormal(float& x, float& y) {
    x = itemX; y = itemY;
}

void GuardarPartida::getDatosItemPowerUp(float& x, float& y) {
    x = itemPowerUpX; y = itemPowerUpY;
}

void GuardarPartida::getEstadoJuego(int& pts, int& mts, int& timer, bool& estado) {
    pts = puntuacion;
    mts = muertes;
    timer = timerPowerUp;
    estado = gameOver;
}

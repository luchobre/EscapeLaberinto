#include "Enemigo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Laberinto.h"

Enemigo::Enemigo()
{
    _texture.loadFromFile("swish_crocman.png");
    _sprite.setTexture(_texture);
    _sprite.setScale(0.7f, 0.7f);

    sf::FloatRect bounds = _sprite.getLocalBounds();
    _sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    _velocidad = 3.3f;
    _velocidad = 3.3f;

    _resIzqX = 0;
    _resDerX = 800;
    _resSupY = 0;
    _resInfY = 600;

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    cambiarDireccion(); 
}


void Enemigo::update(const Laberinto& laberinto)
{
    float halfW = _sprite.getGlobalBounds().width / 2.f;
    float halfH = _sprite.getGlobalBounds().height / 2.f;

    sf::Vector2f posActual = _sprite.getPosition();
    sf::Vector2f nuevaPos = posActual + _direccion * _velocidad;

    if (nuevaPos.x - halfW < _resIzqX ||
        nuevaPos.x + halfW > _resDerX ||
        nuevaPos.y - halfH < _resSupY ||
        nuevaPos.y + halfH > _resInfY)
    {
        cambiarDireccion();
        return;
    }

    sf::FloatRect bounds;
    bounds.left = nuevaPos.x - halfW;
    bounds.top = nuevaPos.y - halfH;
    bounds.width = halfW * 2.f;
    bounds.height = halfH * 2.f;

    bool puede = laberinto.esCaminable(bounds, laberinto.getTileSize());

    if (puede)
        _sprite.setPosition(nuevaPos);
    else
        cambiarDireccion();
}

void Enemigo::cambiarDireccion()
{
    int d = std::rand() % 4;

    switch (d)
    {
    case 0: _direccion = { 1, 0 }; break;
    case 1: _direccion = { -1, 0 }; break;
    case 2: _direccion = { 0, 1 }; break;
    case 3: _direccion = { 0, -1 }; break;
    }
}


void Enemigo::respawn(const Laberinto& laberinto)
{
    sf::Vector2u tileSize = laberinto.getTileSize();
    unsigned int w = laberinto.getWidth();
    unsigned int h = laberinto.getHeight();

    while (true)
    {
        int col = std::rand() % w;
        int row = std::rand() % h;

        int tile = laberinto.getTile(row, col);

        if (tile == 0) {
            float x = col * tileSize.x + tileSize.x / 2;
            float y = row * tileSize.y + tileSize.y / 2;
            _sprite.setPosition(x, y);
            return;
        }
    }
}


void Enemigo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

sf::FloatRect Enemigo::getBounds() const
{
    return _sprite.getGlobalBounds();
}

sf::Vector2f Enemigo::getDireccion() const { return _direccion; }
float Enemigo::getVelocidad() const { return _velocidad; }
sf::Vector2f Enemigo::getPosition() const { return _sprite.getPosition(); }

void Enemigo::setDireccion(float dx, float dy) { _direccion = { dx, dy }; }
void Enemigo::setVelocidad(float v) { _velocidad = v; }
void Enemigo::setPosition(float x, float y) { _sprite.setPosition(x, y); }

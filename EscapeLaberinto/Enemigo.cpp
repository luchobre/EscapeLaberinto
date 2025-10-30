#include "Enemigo.h"
#include <cstdlib>
#include <ctime>

Enemigo::Enemigo()
{
    _texture.loadFromFile("swish_crocman.png");
    _sprite.setTexture(_texture);
    _sprite.setScale(0.8f, 0.8f);
    _sprite.setPosition(740.f, 500.f);
    
    _velocidad = 5.5f;
    _tileSize = 32;
    _resIzqX = 0;
    _resDerX = 800;
    _resSupY = 0;
    _resInfY = 600;

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    int dir = std::rand() % 4;
    if (dir == 0) {
        _direccion = { 1,0 };
    }
    else if (dir == 1) {
        _direccion = { -1,0 };
    }
    else if (dir == 2) {
        _direccion = { 0,1 };
    }
    else {
        _direccion = { 0,-1 };
    }

}


void Enemigo::update(const Laberinto& laberinto)
{

    sf::Vector2f nuevaPosicion = _sprite.getPosition() + _direccion * _velocidad;

    if (nuevaPosicion.x< _resIzqX || nuevaPosicion.y < _resSupY || nuevaPosicion.x + _sprite.getGlobalBounds().width > _resDerX || nuevaPosicion.y + _sprite.getGlobalBounds().height > _resInfY) {
        int nuevaDir = std::rand() % 4;
        if (nuevaDir == 0) {
            _direccion = { 1,0 };
        }
        else if (nuevaDir == 1) {
            _direccion = { -1,0 };
        }
        else if (nuevaDir == 2) {
            _direccion = { 0,1 };
        }
        else {
            _direccion = { 0,-1 };
        }
    }


    sf::FloatRect bounds = _sprite.getGlobalBounds();
    bounds.left = nuevaPosicion.x;
    bounds.top = nuevaPosicion.y;

    bool puedeMoverse = laberinto.esCaminable(bounds, sf::Vector2u(_tileSize, _tileSize));
   
    if (puedeMoverse) {
        _sprite.setPosition(nuevaPosicion);
    }
    else {
        int nuevaDir = std::rand() % 4;
        if (nuevaDir == 0) {
            _direccion = { 1,0 };
        }
        else if (nuevaDir == 1) {
            _direccion = { -1,0 };
        }
        else if (nuevaDir == 2) {
            _direccion = { 0,1 };
        }
        else {
            _direccion = { 0,-1 };
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


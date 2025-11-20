#include "Enemigo2.h"
#include <cstdlib>  // para rand
#include <ctime>    // para time
#include <iostream>

Enemigo2::Enemigo2()
    : _velocidad(1.0f), _tileSize(32)
{
    // Cargar textura (modificar con tu archivo)
    if (!_texture.loadFromFile("enemigo2.png"))
        std::cout << "Error al cargar enemigo2.png\n";
    _sprite.setTexture(_texture);

    // Dirección inicial aleatoria
    _direccion = sf::Vector2f(1.f, 0.f);

    // Inicializar resolución de colisiones
    _resIzqX = _resDerX = _resSupY = _resInfY = 0;
}

void Enemigo2::update(const Laberinto& laberinto)
{
    // Movimiento simple
    _sprite.move(_direccion * _velocidad);

   
    // if(laberinto.esBloque(_sprite.getPosition())) cambiarDireccion();
}

void Enemigo2::respawn(const Laberinto& laberinto)
{
    // Posición aleatoria válida dentro del laberinto
    int cols = laberinto.getWidth();
    int rows = laberinto.getHeight();

    int x, y;
    sf::FloatRect bounds;
    sf::Vector2u tileSize = laberinto.getTileSize();

    do {
        x = rand() % cols;
        y = rand() % rows;

        bounds = sf::FloatRect(
            static_cast<float>(x * _tileSize),
            static_cast<float>(y * _tileSize),
            static_cast<float>(_tileSize),
            static_cast<float>(_tileSize)
        );
    } while (!laberinto.esCaminable(bounds, tileSize));

    _sprite.setPosition(static_cast<float>(x * _tileSize), static_cast<float>(y * _tileSize));

    // Dirección aleatoria inicial
    _direccion = sf::Vector2f((rand() % 2 ? 1.f : -1.f), (rand() % 2 ? 1.f : -1.f));
}

void Enemigo2::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

sf::FloatRect Enemigo2::getBounds() const
{
    return _sprite.getGlobalBounds();
}
#include "Enemigo2.h"
#include <cstdlib>

Enemigo2::Enemigo2()
{
    _texture.loadFromFile("swish_skele_abomination1.png");
    _sprite.setTexture(_texture);
    //_sprite.setScale(0.9f, 0.9f);
    _sprite.setScale(0.1f, 0.1f);
    _sprite.setPosition(350.f, 320.f);

    _velocidad = 0;
    _tileSize = 32;
    _resIzqX = 0;
    _resDerX = 800;
    _resSupY = 0;
    _resInfY = 600;
}

void Enemigo2::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

sf::FloatRect Enemigo2::getBounds() const
{
    return _sprite.getGlobalBounds();
}

sf::Vector2f Enemigo2::getPosition() const {
    return _sprite.getPosition();
}

void Enemigo2::setPosition(float x, float y) {
    _sprite.setPosition(x, y);
}
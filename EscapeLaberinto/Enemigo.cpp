#include "Enemigo.h"

Enemigo::Enemigo()
{
    _velocity = {3,3};
    _texture.loadFromFile("enemyIcon1.png");
    _sprite.setTexture(_texture);
    _resIzqX = 0;
    _resDerX = 800;
    _resSupY = 0;
    _resInfY = 600;
}

void Enemigo::update()
{

    _sprite.move(_velocity);

    //Evitar que salga de la ventana
    if (_sprite.getPosition().x < _resIzqX) {
        _velocity.x = -_velocity.x;
    }
    if (_sprite.getPosition().y < 0) {
        _velocity.y = -_velocity.y;
    }
    if (_sprite.getPosition().x + _sprite.getGlobalBounds().width > _resDerX) {
        _velocity.x = -_velocity.x;
    }
    if (_sprite.getPosition().y + _sprite.getGlobalBounds().height > _resInfY) {
        _velocity.y = -_velocity.y;
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


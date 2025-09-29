#include "Personaje.h"

Personaje::Personaje()
{
    _velocity = { 2,2 };
    _texture.loadFromFile("playerIcon3.png");
    _sprite.setTexture(_texture);
    _resIzqX = 0;
    _resDerX = 800;
    _resSupY = 0;
    _resInfY = 600;
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
}

void Personaje::update()
{
    sf::Vector2f velocity = { 0,0 };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        velocity.y = -_velocity.y;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        velocity.y = _velocity.y;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        velocity.x = _velocity.x;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        velocity.x = -_velocity.y;
    }

    _sprite.move(velocity);

    if (velocity.x < 0) {
        _sprite.setScale(-1, 1);
    }

    if (velocity.x > 0) {
        _sprite.setScale(1, 1);
    }

    //Evitar que salga de la ventana
    if (_sprite.getGlobalBounds().left < _resIzqX) {
        _sprite.setPosition(_sprite.getOrigin().x, _sprite.getPosition().y);
    }
    if (_sprite.getGlobalBounds().top < 0) {
        _sprite.setPosition(_sprite.getPosition().x, _sprite.getOrigin().y);
    }

    if (_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > _resDerX) {
        _sprite.setPosition(_resDerX - (_sprite.getGlobalBounds().width - _sprite.getOrigin().x), _sprite.getPosition().y);
    }

    if (_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height > _resInfY) {
        _sprite.setPosition(_sprite.getPosition().x, _resInfY +(_sprite.getGlobalBounds().height - _sprite.getOrigin().y));
    }

}

void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

void Personaje::respawnPj()
{
    return _sprite.setPosition(50, 50);
}

void Personaje::addVelocity(float velocity)
{
    _velocity.x += velocity;
    _velocity.y += velocity;
}

void Personaje::restartVelocity()
{
    _velocity.x=2;
    _velocity.y = 2;
}

sf::FloatRect Personaje::getBounds() const
{
    return _sprite.getGlobalBounds();
}

#include "Personaje.h"
#include "Laberinto.h"

Personaje::Personaje()
{
    _velocity = { 2,2 };
    _texture.loadFromFile("playerIcon.png");
    _sprite.setTexture(_texture);
    _sprite.setScale(0.5f, 0.5f);
    sf::FloatRect bounds = _sprite.getLocalBounds();
    _sprite.setOrigin(_sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height);


    _resIzqX = 0;
    _resDerX = 800;
    _resSupY = 0;
    _resInfY = 600;
}

void Personaje::update(const Laberinto& laberinto)
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
        velocity.x = -_velocity.x;
    }

    if (velocity.x == 0 && velocity.y == 0) {
        return;
    }

    sf::FloatRect newBounds = _sprite.getGlobalBounds();
    newBounds.left += velocity.x;
    newBounds.top += velocity.y;

    sf::Vector2u tileSize = laberinto.getTileSize();

    bool puedeMoverse = laberinto.esCaminable(newBounds, tileSize);

    if (puedeMoverse) {
        _sprite.move(velocity);
    }

    if (velocity.x < 0) {
        _sprite.setScale(-0.5f, 0.5f);
    }
    else if (velocity.x > 0) {
        _sprite.setScale(0.5f, 0.5f);
    }

    if (_sprite.getPosition().x < _resIzqX + _sprite.getGlobalBounds().width / 2)
        _sprite.setPosition(_resIzqX + _sprite.getGlobalBounds().width / 2, _sprite.getPosition().y);

    if (_sprite.getPosition().x > _resDerX - _sprite.getGlobalBounds().width / 2)
        _sprite.setPosition(_resDerX - _sprite.getGlobalBounds().width / 2, _sprite.getPosition().y);

    if (_sprite.getPosition().y < _resSupY + _sprite.getGlobalBounds().height / 2)
        _sprite.setPosition(_sprite.getPosition().x, _resSupY + _sprite.getGlobalBounds().height / 2);

    if (_sprite.getPosition().y > _resInfY - _sprite.getGlobalBounds().height / 2)
        _sprite.setPosition(_sprite.getPosition().x, _resInfY - _sprite.getGlobalBounds().height / 2);



}

void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

void Personaje::respawnPj()
{
    _sprite.setPosition(50, 50);
}

void Personaje::addVelocity(float velocity)
{
    _velocity.x += velocity;
    _velocity.y += velocity;
}

void Personaje::restartVelocity()
{
    _velocity.x = 2;
    _velocity.y = 2;
}

sf::FloatRect Personaje::getBounds() const
{
    return _sprite.getGlobalBounds();
}

//PARA GUARDAR Y CARGAR
sf::Vector2f Personaje::getVelocity() const {
    return _velocity;
}

sf::Vector2f Personaje::getPosition() const {
    return _sprite.getPosition();
}

void Personaje::setVelocity(float velX, float velY) {
    _velocity.x = velX;
    _velocity.y = velY;
}

void Personaje::setPosition(float x, float y) {
    _sprite.setPosition(x, y);
}
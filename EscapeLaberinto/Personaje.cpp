#include "Personaje.h"
#include "Laberinto.h"

Personaje::Personaje()
{
    _velocity = { 1,1 };
    _texture.loadFromFile("playerIcon.png");
    _sprite.setTexture(_texture);
    _resIzqX = 0;
    _resDerX = 800;
    _resSupY = 0;
    _resInfY = 600;
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
    _sprite.setScale(0.5f, 0.5f);
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


    //para ver si es caminable 
    sf::Vector2f nuevaPos = _sprite.getPosition() + velocity; 
    if (laberinto.esCaminable(nuevaPos, { 32, 30 })) { 
        _sprite.move(velocity); 
    }

    //
    _sprite.move(velocity); 
    if (velocity.x < 0) { 
        _sprite.setScale(-0.5f, 0.5f);
    } 
    if (velocity.x > 0) { 
        _sprite.setScale(0.5f, 0.5f);
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
        _sprite.setPosition(_sprite.getPosition().x, _resInfY + (_sprite.getGlobalBounds().height - _sprite.getOrigin().y));
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
    _velocity.x = 1;
    _velocity.y = 1;
}

sf::FloatRect Personaje::getBounds() const
{
    return _sprite.getGlobalBounds();
}
#include <stdlib.h>
#include "ItemPowerUp.h"

ItemPowerUp::ItemPowerUp()
{
    _texture.loadFromFile("yodaIcon.png");
    _sprite.setTexture(_texture);
}

void ItemPowerUp::update()
{

   
}

void ItemPowerUp::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

void ItemPowerUp::respawn()
{
    _sprite.setPosition(std::rand() % 700 + _sprite.getGlobalBounds().width, std::rand() % 500 + _sprite.getGlobalBounds().height);
}

sf::FloatRect ItemPowerUp::getBounds() const
{
    return _sprite.getGlobalBounds();
}
//PARA GUARDAR Y CARGAR
sf::Vector2f ItemPowerUp::getPosition() const {
    return _sprite.getPosition(); 
}

void ItemPowerUp::setPosition(float x, float y) {
    _sprite.setPosition(x, y);
}

sf::Sprite& ItemPowerUp::getSprite() {
    return _sprite;  
}
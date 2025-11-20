#include <stdlib.h>
#include "ItemPowerUp.h"
#include "Laberinto.h"

ItemPowerUp::ItemPowerUp()
{
    _texture.loadFromFile("pulight.png");
    _sprite.setTexture(_texture);
}

void ItemPowerUp::update()
{

   
}

void ItemPowerUp::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

void ItemPowerUp::respawn(const Laberinto& laberinto)
{
    sf::Vector2u tileSize = laberinto.getTileSize();
    unsigned int mapWidth = laberinto.getWidth();
    unsigned int mapHeight = laberinto.getHeight();

    while (true)
    {
        int maxX = static_cast<int>(mapWidth * tileSize.x - _sprite.getGlobalBounds().width);
        int maxY = static_cast<int>(mapHeight * tileSize.y - _sprite.getGlobalBounds().height);

        float x = std::rand() % maxX;
        float y = std::rand() % maxY;

        _sprite.setPosition(x, y);

        if (laberinto.esCaminable(_sprite.getGlobalBounds(), tileSize))
            return;
    }
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
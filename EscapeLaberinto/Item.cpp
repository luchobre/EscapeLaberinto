#include <stdlib.h>
#include "Item.h"
#include "Laberinto.h"


Item::Item()
{
    _texture.loadFromFile("star.png");
    _sprite.setTexture(_texture);
}

void Item::update()
{


}

void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

void Item::respawn(const Laberinto& laberinto)
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

sf::FloatRect Item::getBounds() const
{
    return _sprite.getGlobalBounds();
}
//PARA GUARDAR Y CARGAR
sf::Vector2f Item::getPosition() const {
    return _sprite.getPosition(); 
}

void Item::setPosition(float x, float y) {
    _sprite.setPosition(x, y); 
}

sf::Sprite& Item::getSprite() {
    return _sprite; 
}

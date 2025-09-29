#include <stdlib.h>
#include "Item.h"


Item::Item()
{
    _texture.loadFromFile("item.png");
    _sprite.setTexture(_texture);
}

void Item::update()
{


}

void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

void Item::respawn()
{
    _sprite.setPosition(std::rand() % 700 + _sprite.getGlobalBounds().width, std::rand() % 500 + _sprite.getGlobalBounds().height);
}

sf::FloatRect Item::getBounds() const
{
    return _sprite.getGlobalBounds();
}

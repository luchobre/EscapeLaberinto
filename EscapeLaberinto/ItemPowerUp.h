#pragma once
#include <SFML/Graphics.hpp>
#include "Colisionable.h"
#include "Laberinto.h"

class ItemPowerUp : public sf::Drawable, public Colisionable
{
private:
    sf::Sprite _sprite;
    sf::Texture _texture;

public:
    ItemPowerUp();

    void update(); 
    void respawn(const Laberinto& laberinto);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;

    // Para guardar y cargar
    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);
    sf::Sprite& getSprite();
};




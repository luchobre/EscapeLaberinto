#pragma once
#include <SFML/Graphics.hpp>
#include "Colisionable.h"
class Item :public sf::Drawable, public Colisionable
{
	sf::Sprite _sprite;
	sf::Texture _texture;

public:
	Item();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	void respawn();
	sf::FloatRect getBounds() const override;
};



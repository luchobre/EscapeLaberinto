#pragma once
#include <SFML/Graphics.hpp>
#include "Colisionable.h"

class Enemigo :public sf::Drawable, public Colisionable
{
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _velocity;
	//Resolucion
	int _resIzqX;
	int _resDerX;
	int _resSupY;
	int _resInfY;
public:
	Enemigo();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	sf::FloatRect getBounds() const override;
};


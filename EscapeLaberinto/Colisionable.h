#pragma once
#include <SFML/Graphics.hpp>

class Colisionable 
{
public:
	virtual sf::FloatRect getBounds() const = 0;
	bool isColisionable(Colisionable& col) const;

};
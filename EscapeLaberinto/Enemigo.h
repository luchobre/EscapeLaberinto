#pragma once
#include <SFML/Graphics.hpp>
#include "Colisionable.h"
#include "Laberinto.h";

class Enemigo :public sf::Drawable, public Colisionable
{
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _direccion;
	float _velocidad;
	int _tileSize;

	//Resolucion
	int _resIzqX;
	int _resDerX;
	int _resSupY;
	int _resInfY;
public:
	Enemigo();
	void update(const Laberinto& laberinto);
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	sf::FloatRect getBounds() const override;
};


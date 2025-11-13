#pragma once
#include <SFML/Graphics.hpp>
#include "Colisionable.h"
#include "Laberinto.h"

class Personaje :public sf::Drawable, public Colisionable
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
	Personaje();
	void update(const Laberinto& laberinto);
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	void respawnPj(); //prueba
	sf::FloatRect getBounds() const override;
	void addVelocity(float velocity);
	void restartVelocity();
	//METODOS PARA GUARDAR Y CARGAR
	sf::Vector2f getVelocity() const;
	sf::Vector2f getPosition() const;     
	void setVelocity(float velX, float velY);
	void setPosition(float x, float y);
};
#pragma once
#include <SFML/Graphics.hpp>
#include "Colisionable.h"
#include "Laberinto.h"
#include "Nivel.h"


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

	// --- NUEVO: SISTEMA DE NIVELES ---
	Nivel nivel;
	bool _subioNivel = false;

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

	// --- NUEVOS MÉTODOS ---
	void recolectarItem(int valorItem);  // suma puntos y detecta nivel
	bool subioNivel();                   // para el main
	int getNivelActual() const;          // devuelve 1, 2 o 3
};

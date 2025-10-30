#pragma once
#include <SFML/Graphics.hpp>

#define ITEMS_MENU 3

class Menu
{
public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void drawCreditos(sf::RenderWindow& window); // ? nueva función
    void MoveUp();
    void MoveDown();
    int GetPressedItem();

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[ITEMS_MENU];
    sf::Text textoVolver;     // texto “Presiona ESC…”
    sf::Text tituloCreditos;  // título de créditos
    sf::Text contenidoCreditos; // contenido de créditos
};
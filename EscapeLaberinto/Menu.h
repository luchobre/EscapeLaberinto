#pragma once
#include <SFML/Graphics.hpp>

constexpr int ITEMS_MENU = 4;
constexpr int ITEMS_MENUPAUSA = 4;


class Menu
{
public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void drawCreditos(sf::RenderWindow& window); // ? nueva función
    void MoveUp();
    void MoveDown();
    int GetPressedItem();
    //METODOS PARA MENU DE PAUSA
    void drawPausa(sf::RenderWindow& window);
    void MoveUpPausa();
    void MoveDownPausa();
    int GetPressedItemPausa();

private:
    int selectedItemIndex;
    int selectedItemIndexPausa;
    sf::Font font;
    sf::Text menu[ITEMS_MENU];
    sf::Text menuPausa[ITEMS_MENUPAUSA];
    sf::Text textoVolver;     // texto “Presiona ESC…”
    sf::Text tituloCreditos;  // título de créditos
    sf::Text contenidoCreditos; // contenido de créditos
};
#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("PixelPurl.ttf"))
    {
        std::cout << "HUBO UN PROBLEMA AL CARGAR LA FUENTE" << std::endl;
    }

    // ====== MENÚ PRINCIPAL ======
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Jugar");
    menu[0].setPosition(sf::Vector2f(width / 2, height / (ITEMS_MENU + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Creditos");
    menu[1].setPosition(sf::Vector2f(width / 2, height / (ITEMS_MENU + 1) * 2));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Salir");
    menu[2].setPosition(sf::Vector2f(width / 2, height / (ITEMS_MENU + 1) * 3));

    selectedItemIndex = 0;

    // ====== CONTENIDO DE CRÉDITOS ======
    contenidoCreditos.setFont(font);
    contenidoCreditos.setCharacterSize(50);   // tamaño más grande
    contenidoCreditos.setFillColor(sf::Color::Green );
    contenidoCreditos.setString("Grupo 9 de Programacion 2\nUTN FRGP");
    contenidoCreditos.setPosition(width / 2 - 250.f, height / 2 - 100.f);

    textoVolver.setFont(font);
    textoVolver.setString("Presiona ESC para volver al menu");
    textoVolver.setCharacterSize(15);
    textoVolver.setFillColor(sf::Color::White);
    textoVolver.setPosition(30.f, height - 40.f);
}

void Menu::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < ITEMS_MENU; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::drawCreditos(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);
    window.draw(contenidoCreditos);
    window.draw(textoVolver);
}

void Menu::MoveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::MoveDown()
{
    if (selectedItemIndex + 1 < ITEMS_MENU)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

int Menu::GetPressedItem()
{
    return selectedItemIndex;
}
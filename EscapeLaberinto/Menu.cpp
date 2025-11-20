#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("PixelPurl.ttf"))
    {
        std::cout << "HUBO UN PROBLEMA AL CARGAR LA FUENTE" << std::endl;
    }

    //MENÚ PRINCIPAL
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Continuar partida");
    menu[0].setPosition(sf::Vector2f(width / 2, height / (ITEMS_MENU + 1) * 1));

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

    // MENU PAUSA 
    menuPausa[0].setFont(font);
    menuPausa[0].setFillColor(sf::Color::Red);
    menuPausa[0].setString("Continuar");
    menuPausa[0].setPosition(sf::Vector2f(width / 2, height / (ITEMS_MENUPAUSA + 1) * 1));

    menuPausa[1].setFont(font);
    menuPausa[1].setFillColor(sf::Color::White);
    menuPausa[1].setString("Guardar Partida");
    menuPausa[1].setPosition(sf::Vector2f(width / 2, height / (ITEMS_MENUPAUSA + 1) * 2));

    menuPausa[2].setFont(font);
    menuPausa[2].setFillColor(sf::Color::White);
    menuPausa[2].setString("Reiniciar partida");
    menuPausa[2].setPosition(sf::Vector2f(width / 2, height / (ITEMS_MENUPAUSA + 1) * 3));

    menuPausa[3].setFont(font);
    menuPausa[3].setFillColor(sf::Color::White);
    menuPausa[3].setString("Salir al menu principal");
    menuPausa[3].setPosition(sf::Vector2f(width / 2, height / (ITEMS_MENUPAUSA + 1) * 4));


    selectedItemIndexPausa = 0;

    //CRÉDITOS
    contenidoCreditos.setFont(font);
    contenidoCreditos.setCharacterSize(50);   // tamaño más grande
    contenidoCreditos.setFillColor(sf::Color::Green);
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

//METODOS PARA MENU DE PAUSA
void Menu::drawPausa(sf::RenderWindow& window)
{
    //RECTANGULO NEGRO SEMITRANSPARENTE PARA QUE SE VEA COOL
    sf::RectangleShape fondo;
    fondo.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    fondo.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(fondo);


    for (int i = 0; i < ITEMS_MENUPAUSA; i++)
    {
        window.draw(menuPausa[i]);
    }

}


void Menu::MoveUpPausa()
{
    if (selectedItemIndexPausa - 1 >= 0)
    {
        menuPausa[selectedItemIndexPausa].setFillColor(sf::Color::White);
        selectedItemIndexPausa--;
        menuPausa[selectedItemIndexPausa].setFillColor(sf::Color::Red);
    }
}

void Menu::MoveDownPausa()
{
    if (selectedItemIndexPausa + 1 < ITEMS_MENUPAUSA)
    {
        menuPausa[selectedItemIndexPausa].setFillColor(sf::Color::White);
        selectedItemIndexPausa++;
        menuPausa[selectedItemIndexPausa].setFillColor(sf::Color::Red);
    }
}

int Menu::GetPressedItemPausa()
{
    return selectedItemIndexPausa;
}
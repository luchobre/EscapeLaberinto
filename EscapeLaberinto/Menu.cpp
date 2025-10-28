#include "Menu.h"
#include <iostream>


Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("PixelPurl.ttf"))
	{
		std::cout << "HUBO UN PROBLEMA AL CARGAR LA FUENTE" << std::endl;
	}

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
}



void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < ITEMS_MENU; i++)
	{
		window.draw(menu[i]);
	}
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
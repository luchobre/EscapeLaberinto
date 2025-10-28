#pragma once
#include "SFML/Graphics.hpp"

#define ITEMS_MENU 3

class Menu
{
public:
	Menu(float width, float height);
	//~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[ITEMS_MENU];

};
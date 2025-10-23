#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <array>
#include "Personaje.h"
#include "Enemigo.h"
#include "Item.h"
#include "Colisionable.h"
#include "ItemPowerUp.h"
#include "Laberinto.h"


int main()
{
    //Semilla para el random
    std::srand((unsigned)std::time(0));
    //Inicialización de la ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "Escape del Laberinto");
    window.setFramerateLimit(60);

    //Fuente y carga de fuente

    sf::Font font;
    font.loadFromFile("8bitFont.ttf");
    sf::Text text;

    text.setFont(font);

    Personaje guerrero;
    Enemigo monstruo;
    Item item;
    item.respawn();

    ItemPowerUp itemPu;
    itemPu.respawn();
    int timer = 60 * 5;


    int puntos = 0;


    //Laberinto

    constexpr std::array level = {
    3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
    3,0,0,0,0,0,3,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,3,
    3,0,3,3,3,0,3,0,3,0,3,0,3,0,3,0,3,3,3,3,3,3,0,0,3,
    3,0,3,0,0,0,3,0,3,0,3,0,3,0,3,0,0,0,0,0,0,3,0,0,3,
    3,0,3,0,3,3,3,0,3,0,3,0,3,0,3,3,3,3,3,3,0,3,0,0,3,
    3,0,0,0,3,0,0,0,3,0,0,0,3,0,0,0,0,0,0,3,0,3,0,0,3,
    3,0,3,0,3,0,3,3,3,3,3,0,3,3,3,3,3,3,0,3,0,3,3,3,3,
    3,0,3,0,0,0,3,0,0,0,3,0,0,0,3,0,0,3,0,3,0,0,0,0,3,
    3,0,3,3,3,0,3,0,3,0,3,3,3,0,3,0,3,3,0,3,3,3,3,0,3,
    3,0,0,0,3,0,3,0,3,0,0,0,0,0,3,0,0,0,0,3,0,0,3,0,3,
    3,3,3,0,3,0,3,0,3,3,3,3,3,0,3,0,3,3,3,3,0,3,3,0,3,
    3,0,0,0,3,0,0,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,3,0,3,
    3,0,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,0,3,0,3,
    3,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,3,0,3,
    3,0,3,3,3,3,3,2,2,2,1,1,1,2,2,2,3,3,3,3,3,0,3,0,3,
    3,0,3,0,0,0,0,2,1,1,1,1,1,1,1,2,0,0,0,0,3,0,3,0,3,
    3,0,3,0,3,3,3,2,2,2,1,1,1,2,2,2,3,3,3,0,3,0,3,0,3,
    3,0,3,0,3,0,0,0,0,0,0,0,0,0,0,0,3,0,3,0,3,0,3,0,3,
    3,0,0,0,3,0,3,3,3,3,3,3,3,3,3,0,3,0,0,0,3,0,0,0,3,
    3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
    };

    Laberinto laberinto;
    if (!laberinto.load("tileset.png", { 32, 30 }, level.data(), 25, 20)) {
        return -1;
    }


    //Game Loop

    while (window.isOpen())
    {
        //Read Input Actualizar los estados de los perifericos de entrada
        //Leer cola ed mensajes

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //CMD (Lo que se apretó)-Joystick



        //Update - Actualiza estados del juego
        if (timer > 0) {
            timer--;
        }

        guerrero.update(laberinto);
        monstruo.update();

        if (guerrero.isColisionable(item)) {
            item.respawn();
            puntos++;
        }


        if (guerrero.isColisionable(monstruo)) {
            guerrero.respawnPj();
            puntos = 0;
            guerrero.restartVelocity();
        }

        if (timer == 0 && guerrero.isColisionable(itemPu)) {
            guerrero.addVelocity(1);
            timer = 60 * 5;
            itemPu.respawn();
        }

        text.setString(std::to_string(puntos));

        window.clear();

        //Draw
        window.draw(laberinto);
        window.draw(guerrero);
        window.draw(monstruo);
        window.draw(item);
        window.draw(text);

        if (timer == 0) {
            window.draw(itemPu);
        }

        //Display-Flip

        window.display();
    }

    //Liberacion del juego

    return 0;
}
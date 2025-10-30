#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <array>
#include "Personaje.h"
#include "Enemigo.h"
#include "Item.h"
#include "Colisionable.h"
#include "ItemPowerUp.h"
#include "Laberinto.h"
#include "Menu.h"


int main()
{
    //Semilla para el random
    std::srand((unsigned)std::time(0));
    //Inicialización de la ventana
    sf::RenderWindow window(sf::VideoMode(800, 640), "Escape del Laberinto");
    window.setFramerateLimit(60);

    //Menu
    Menu menu(window.getSize().x, window.getSize().y);

    enum EstadoJuego { EN_MENU, EN_CREDITOS, EN_JUEGO };
    EstadoJuego estado = EN_MENU;


    //Fuente y carga de fuente

    sf::Font font;
    font.loadFromFile("8bitFont.ttf");
    sf::Text text;

    text.setFont(font);

    //Texto de creditos
    sf::Text creditos;
    creditos.setFont(font);
    creditos.setString("Grupo 9 de Programacion 2\nUTN FRGP");
    creditos.setCharacterSize(20);
    creditos.setFillColor(sf::Color::White);
    creditos.setPosition(100.f, 200.f);

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
    0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
    0,0,0,0,0,0,3,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,3,
    3,0,3,3,3,0,3,0,3,0,4,0,3,0,3,0,3,3,4,3,3,3,0,0,3,
    3,0,3,0,0,0,3,0,3,0,3,0,3,0,3,0,0,0,0,0,0,3,0,0,3,
    3,0,3,0,3,3,3,0,3,0,0,0,3,0,3,3,3,3,3,3,0,3,0,0,3,
    3,0,0,0,3,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,3,0,0,3,
    3,0,0,0,3,0,3,3,3,3,3,0,3,3,3,3,3,3,0,3,0,3,3,0,3,
    3,0,3,0,0,0,3,0,0,0,3,0,0,0,3,0,0,3,0,3,0,0,0,0,3,
    3,0,3,3,3,0,3,0,4,0,3,3,3,0,3,0,3,4,0,3,0,3,3,0,3,
    3,0,0,0,3,0,3,0,3,0,0,0,0,0,3,0,0,0,0,3,0,0,3,0,3,
    3,3,3,0,3,0,3,0,3,3,3,3,3,0,3,0,3,3,3,3,0,3,3,0,3,
    3,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,3,0,3,
    3,0,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,0,3,0,3,
    3,0,0,0,0,0,0,0,2,2,1,0,1,2,2,0,0,0,0,0,0,0,3,0,3,
    3,0,3,3,3,3,3,0,2,1,1,0,1,1,2,0,3,3,3,3,3,0,3,0,3,
    3,0,3,0,0,0,0,0,2,1,1,0,1,1,2,0,0,0,0,0,3,0,3,0,3,
    3,0,3,0,3,3,3,0,2,2,1,0,1,2,2,0,3,3,3,0,3,0,3,0,3,
    3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
    3,0,0,0,0,0,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,3,
    3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
    };

    Laberinto laberinto;
    if (!laberinto.load("tileset1.png", { 32, 32 }, level.data(), 25, 20)) {
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

            if (estado == EN_MENU)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Up)
                        menu.MoveUp();
                    else if (event.key.code == sf::Keyboard::Down)
                        menu.MoveDown();
                    else if (event.key.code == sf::Keyboard::Enter)
                    {
                        int opcion = menu.GetPressedItem();

                        if (opcion == 0) // Jugar
                        {
                            estado = EN_JUEGO;
                        }
                        else if (opcion == 1) // Créditos
                        {
                            estado = EN_CREDITOS;
                        }
                        else if (opcion == 2) // Salir
                        {
                            window.close();
                        }
                    }
                }
            }
            if (estado == EN_CREDITOS)
            {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                    estado = EN_MENU;
            }
        }


        window.clear();

        if (estado == EN_MENU)
        {
            menu.draw(window);
        }
        else if (estado == EN_JUEGO)
        {
            //CMD (Lo que se apretó)-Joystick

            //Update - Actualiza estados del juego
            if (timer > 0) {
                timer--;
            }

            guerrero.update(laberinto);
            monstruo.update(laberinto);

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

            text.setString("Puntaje: " + std::to_string(puntos));
            text.setCharacterSize(15);
            text.setFillColor(sf::Color::Red);
            text.setLetterSpacing(3);


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
        }
        else if(estado == EN_CREDITOS) {
            window.draw(creditos);
        }


        //Display-Flip

        window.display();
    }

    //Liberacion del juego

    return 0;
}
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
    int muertes = 0;
    bool gameover = false;

    std::srand((unsigned)std::time(0));

    sf::RenderWindow window(sf::VideoMode(800, 640), "Escape del Laberinto");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);

    enum EstadoJuego { EN_MENU, EN_CREDITOS, EN_JUEGO, EN_PAUSA };
    EstadoJuego estado = EN_MENU;

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
    if (!laberinto.load("tileset1.png", { 32, 32 }, level.data(), 25, 20))
        return -1;

    while (window.isOpen())
    {
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
                        if (opcion == 0) estado = EN_JUEGO;
                        else if (opcion == 1) estado = EN_CREDITOS;
                        else if (opcion == 2) window.close();
                    }
                }
            }
            else if (estado == EN_CREDITOS)
            {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                    estado = EN_MENU;
            }
            else if (estado == EN_PAUSA)  // MENU DE PAUSA
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Up)
                        menu.MoveUpPausa();
                    else if (event.key.code == sf::Keyboard::Down)
                        menu.MoveDownPausa();
                    else if (event.key.code == sf::Keyboard::Enter)
                    {
                        int opcion = menu.GetPressedItemPausa();
                        if (opcion == 0) {
                            estado = EN_JUEGO;
                        }
                        else if (opcion == 1) {                    
                            estado = EN_JUEGO;
                            muertes = 0;
                            puntos = 0;
                            guerrero.respawnPj();
                            gameover = false;
                        }
                        else if (opcion == 2) {                    
                            estado = EN_MENU;
                            muertes = 0;
                            puntos = 0;
                            guerrero.respawnPj();
                            gameover = false;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Escape) {
                        estado = EN_JUEGO;  // PARA PODER VOLVER AL JUEGO CON ESC
                    }
                }
                
            }
            else if (estado == EN_JUEGO && gameover) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        muertes = 0;
                        puntos = 0;
                        guerrero.respawnPj();
                        gameover = false;
                    }
                    else if (event.key.code == sf::Keyboard::Escape) {
                        estado = EN_MENU;
                        muertes = 0;
                        puntos = 0;
                        guerrero.respawnPj();
                        gameover = false;
                    }
                }
            }
        }
        
            
        window.clear();

        if (estado == EN_MENU)
        {
            menu.draw(window);
        }
        else if (estado == EN_JUEGO)
        {
            if (gameover) {
                sf::Text titulo, pregunta, opciones;
                titulo.setFont(font);
                titulo.setString(" GAME OVER ");
                titulo.setCharacterSize(35);
                titulo.setFillColor(sf::Color::Red);
                titulo.setPosition(250.f, 200.f);

                pregunta.setFont(font);
                pregunta.setString(" Has perdido las 3 vidas ");
                pregunta.setCharacterSize(20);
                pregunta.setFillColor(sf::Color::White);
                pregunta.setPosition(250.f, 260.f);

                opciones.setFont(font);
                opciones.setString(" [ENTER] Continuar      [ESC] Menu Principal ");
                opciones.setCharacterSize(18);
                opciones.setFillColor(sf::Color::White);
                opciones.setPosition(80.f, 320.f);

                window.draw(titulo);
                window.draw(pregunta);
                window.draw(opciones);

                //control solo en game over
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        // reinicia el juego
                        muertes = 0;
                        puntos = 0;
                        guerrero.respawnPj();
                        gameover = false;
                    }
                    else if (event.key.code == sf::Keyboard::Escape) {
                        // vuelve al menu
                        estado = EN_MENU;
                        muertes = 0;
                        puntos = 0;
                        guerrero.respawnPj();
                        gameover = false;
                    }
                }
            }
            else
            {
                // VERIFICAR SI SE PRESIONA ESC PARA PAUSAR  NUEVO
                static bool escPresionado = false; 
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !escPresionado) {
                    estado = EN_PAUSA;
                    escPresionado = true;
                }
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    escPresionado = false;
                }
            
                if (timer > 0) timer--;

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
                    muertes++;
                    if (muertes >= 3)
                        gameover = true;
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

                window.draw(laberinto);
                window.draw(guerrero);
                window.draw(monstruo);
                window.draw(item);
                window.draw(text);

                if (timer == 0)
                    window.draw(itemPu);
            }
        }
        else if (estado == EN_PAUSA)
        {
            //ACA SE CONGELA EL JUEGO DE FONDO
            window.draw(laberinto);
            window.draw(guerrero);
            window.draw(monstruo);
            window.draw(item);
            window.draw(text);

            if (timer == 0)
                window.draw(itemPu);

            menu.drawPausa(window); //MENU DE PAUSA ENCIMA
        }

            
        else if (estado == EN_CREDITOS)
        {
            menu.drawCreditos(window);
        }

        window.display();
    }

    return 0;
}
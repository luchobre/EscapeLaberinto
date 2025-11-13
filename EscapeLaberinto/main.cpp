#define _CRT_SECURE_NO_WARNINGS //PARA QUE VISUAL STUDIO TRABAJE BIEN CON LAS FUNCIONES DE ARCHIVO Y NO DE ERROR DE SEGURIDAD
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
#include "GuardarPartida.h"
#include "ArchivoPartida.h"

//VER SI ANDA BIEN ACA, SINO CAMBIARLO
ArchivoPartida archivoPartidas("partida_guardada.dat");

bool guardarPartidaActual(Personaje& guerrero, Enemigo& monstruo, Item& item,
    ItemPowerUp& itemPu, int puntos, int muertes, int timer, bool gameover) {

    GuardarPartida partida;

    //DATOS DEL JUEGO
    sf::Vector2f posPj = guerrero.getPosition();
    sf::Vector2f velPj = guerrero.getVelocity();
    partida.setDatosPersonaje(posPj.x, posPj.y, velPj.x, velPj.y);

    sf::Vector2f posEnemigo = monstruo.getPosition();
    sf::Vector2f dirEnemigo = monstruo.getDireccion();
    float velEnemigo = monstruo.getVelocidad();
    partida.setDatosEnemigo(posEnemigo.x, posEnemigo.y, dirEnemigo.x, dirEnemigo.y, velEnemigo);


    sf::Vector2f posItem = item.getPosition();
    partida.setDatosItemNormal(posItem.x, posItem.y);

    sf::Vector2f posItemPu = itemPu.getPosition();
    partida.setDatosItemPowerUp(posItemPu.x, posItemPu.y);

    partida.setEstadoJuego(puntos, muertes, timer, gameover);

    return archivoPartidas.guardarPartida(partida);
}

void cargarPartidaGuardada(Personaje& guerrero, Enemigo& monstruo, Item& item,
    ItemPowerUp& itemPu, int& puntos, int& muertes, int& timer, bool& gameover) {

    GuardarPartida partida = archivoPartidas.cargarPartida();

    float x, y, velX, velY, dirX, dirY, velocidad;

    partida.getDatosPersonaje(x, y, velX, velY);
    guerrero.setPosition(x, y);
    guerrero.setVelocity(velX, velY);

    partida.getDatosEnemigo(x, y, dirX, dirY, velocidad);
    monstruo.setPosition(x, y);
    monstruo.setDireccion(dirX, dirY);
    monstruo.setVelocidad(velocidad);

    partida.getDatosItemNormal(x, y);
    item.setPosition(x, y);

    partida.getDatosItemPowerUp(x, y);
    itemPu.setPosition(x, y);

    partida.getEstadoJuego(puntos, muertes, timer, gameover);
}


int main()
{
    int muertes = 0;
    bool gameover = false;

    std::srand((unsigned)std::time(0));

    sf::RenderWindow window(sf::VideoMode(800, 640), "Escape del Laberinto");
    window.setFramerateLimit(60);

    // -- Carga de corazones para la vida 

    sf::Texture texCorazonLleno, texCorazonVacio;
    if (!texCorazonLleno.loadFromFile("corazonRojo.png"))
        std::cout << "Error: no se pudo cargar corazonRojo.png";
    if (!texCorazonVacio.loadFromFile("corazonVacio.png"))
        std::cout << "Error: no se pudo cargar corazonVacio.png";

     int NUM_VIDAS = 3;
    std::vector<sf::Sprite> corazones(NUM_VIDAS);
    for (int i = 0; i < NUM_VIDAS; ++i) {
        corazones[i].setTexture(texCorazonLleno); // textura por defecto
        corazones[i].setOrigin(0.f, 0.f);         // origen en esquina
    }

    //  altura  para los corazones
     float targetHeight = 40.f;
    float scaleLleno = targetHeight / static_cast<float>(texCorazonLleno.getSize().y);
    float scaleVacio = targetHeight / static_cast<float>(texCorazonVacio.getSize().y);
    
    float espacio = 4.f;      // espacio entre corazones
    float margenDerecho = 10.f; // distancia al borde derecho

    // anchos escalados según si el sprite estará lleno o vacío
    std::vector<float> scaledWidths(NUM_VIDAS);
    for (int i = 0; i < NUM_VIDAS; ++i) {
        bool seraLleno = (i < NUM_VIDAS - muertes); // true si esta vida todavía existe
        if (seraLleno) {
            corazones[i].setTexture(texCorazonLleno);          // textura llena
            corazones[i].setScale(scaleLleno, scaleLleno);     // escala para igualar alto
            scaledWidths[i] = texCorazonLleno.getSize().x * scaleLleno;
        }
        else {
            corazones[i].setTexture(texCorazonVacio);          // textura vacía
            corazones[i].setScale(scaleVacio, scaleVacio);     // escala para igualar alto
            scaledWidths[i] = texCorazonVacio.getSize().x * scaleVacio;
        }
    }

    //  ancho + espacios entre ellos
    float totalWidth = 0.f;
    for (int i = 0; i < NUM_VIDAS; ++i) {
        totalWidth += scaledWidths[i];
        if (i < NUM_VIDAS - 1) totalWidth += espacio;
    }

    // Posición inicial 
    float startX = static_cast<float>(window.getSize().x) - margenDerecho - totalWidth;
    float y = 10.f; // altura fija desde arriba 

    // Posicionamos y dibujamos
    float x = startX;
    for (int i = 0; i < NUM_VIDAS; ++i) {
        corazones[i].setPosition(x, y);
        window.draw(corazones[i]);
        x += scaledWidths[i] + espacio;
    }

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
                        if (opcion == 0) {
                            // FALTA MODIFICAR OPCIONES PARA VER SI QUERES CONTINUAR O INICIAR UNA NUEVA
                            if (archivoPartidas.existePartidaGuardada()) {
                                // CARGAR PARTIDA EXISTENTE
                                cargarPartidaGuardada(guerrero, monstruo, item, itemPu, puntos, muertes, timer, gameover);
                                estado = EN_JUEGO;
                                std::cout << "Partida cargada exitosamente!" << std::endl; //MJ EN CONSOLA PARA VER SI FUNCIONA
                            }
                            else {
                                // NUEVA PARTIDA - RESETEAR EL JUEGO A ESTADO INICIAL
                                archivoPartidas.eliminarPartidaGuardada();
                                
                                guerrero.respawnPj();
                                monstruo = Enemigo();
                                item.respawn();
                                itemPu.respawn();
                                puntos = 0;
                                muertes = 0;
                                timer = 60 * 5;
                                gameover = false;
                                estado = EN_JUEGO;
                            }
                        }
                        else if (opcion == 1)
                            estado = EN_CREDITOS;
                        else if (opcion == 2)
                            window.close();
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
                        else if (opcion == 1) {  // NUEVA OPCIÓN: GUARDAR PARTIDA
                            if (guardarPartidaActual(guerrero, monstruo, item, itemPu, puntos, muertes, timer, gameover)) {
                                std::cout << "Partida guardada exitosamente!" << std::endl;
                            }
                            else {
                                std::cout << "Error al guardar la partida" << std::endl;
                            }
                        }
                        else if (opcion == 2) {
                            estado = EN_JUEGO;
                            muertes = 0;
                            puntos = 0;
                            guerrero.respawnPj();
                            gameover = false;
                        }
                        else if (opcion == 3) {
                            estado = EN_MENU;
                            muertes = 0;
                            puntos = 0;
                            guerrero.respawnPj();
                            gameover = false;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Escape) {
                        estado = EN_JUEGO;
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

                // --- Muestra corazones 
                for (int i = 0; i < 3; i++) {
                    if (i < 3 - muertes) 

                        corazones[i].setTexture(texCorazonLleno);
                        
                    else 
                        corazones[i].setTexture(texCorazonVacio);
                        

                        window.draw(corazones[i]);
                };

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
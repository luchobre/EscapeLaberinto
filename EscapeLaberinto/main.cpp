#define _CRT_SECURE_NO_WARNINGS //PARA QUE VISUAL STUDIO TRABAJE BIEN CON LAS FUNCIONES DE ARCHIVO Y NO DE ERROR DE SEGURIDAD
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <array>
#include "Personaje.h"
#include "Enemigo.h"
#include "Enemigo2.h"
#include "Enemigo3.h"
#include "Item.h"
#include "Colisionable.h"
#include "ItemPowerUp.h"
#include "Laberinto.h"
#include "Menu.h"
#include "GuardarPartida.h"
#include "ArchivoPartida.h"

//VER SI ANDA BIEN ACA, SINO CAMBIARLO
ArchivoPartida archivoPartidas("partida_guardada.dat");

bool guardarPartidaActual(Personaje& guerrero, Enemigo& monstruo, Enemigo3& monstruo3, Item& item,
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

    sf::Vector2f posEnemigo3 = monstruo3.getPosition();
    sf::Vector2f dirEnemigo3 = monstruo3.getDireccion();
    float velEnemigo3 = monstruo3.getVelocidad();
    partida.setDatosEnemigo3(posEnemigo3.x, posEnemigo3.y, dirEnemigo3.x, dirEnemigo3.y, velEnemigo3);

    sf::Vector2f posItem = item.getPosition();
    partida.setDatosItemNormal(posItem.x, posItem.y);

    sf::Vector2f posItemPu = itemPu.getPosition();
    partida.setDatosItemPowerUp(posItemPu.x, posItemPu.y);

    partida.setEstadoJuego(puntos, muertes, timer, gameover);

    return archivoPartidas.guardarPartida(partida);
}

void cargarPartidaGuardada(Personaje& guerrero, Enemigo& monstruo, Enemigo3& monstruo3, Item& item,
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

    partida.getDatosEnemigo3(x, y, dirX, dirY, velocidad);
    monstruo3.setPosition(x, y);
    monstruo3.setDireccion(dirX, dirY);
    monstruo3.setVelocidad(velocidad);

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
    int nivelActual = 1;

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

    // anchos escalados segun si el sprite estara lleno o vacio
    std::vector<float> scaledWidths(NUM_VIDAS);
    for (int i = 0; i < NUM_VIDAS; ++i) {
        bool seraLleno = (i < NUM_VIDAS - muertes); // true si esta vida todavia existe
        if (seraLleno) {
            corazones[i].setTexture(texCorazonLleno);          // textura llena
            corazones[i].setScale(scaleLleno, scaleLleno);     // escala para igualar alto
            scaledWidths[i] = texCorazonLleno.getSize().x * scaleLleno;
        }
        else {
            corazones[i].setTexture(texCorazonVacio);          // textura vacia
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

    // Posicion inicial 
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

    //MUSICA 
    //MENU
    sf::Music musicaMenu;
    bool musicaMenuCargada = false; //BANDERA POR SI FALLA LA CARGA DEL ARCHIVO
    if (!musicaMenu.openFromFile("loop-thriller.wav")) {
        std::cout << "Error cargando musica" << std::endl;
    }
    else {
        musicaMenuCargada = true;
        musicaMenu.setLoop(true);
        musicaMenu.setVolume(35);
    }


    //MUSICA NIVEL
    sf::Music musicaNivel;
    bool musicaNivelCargada = false; //BANDERA POR SI FALLA LA CARGA DEL ARCHIVO
    if (!musicaNivel.openFromFile("spaceloop.wav")) {
        std::cout << "Error cargando musica" << std::endl;
    }
    else {
        musicaNivelCargada = true;
        musicaNivel.setLoop(true);
        musicaNivel.setVolume(30);
    }

    //EFECTOS DE SONIDO
    //RECIBIENDO DAÑO
    sf::SoundBuffer bufferDanio;
    bufferDanio.loadFromFile("damage-sound.wav");

    sf::Sound sonidoDanio;
    sonidoDanio.setBuffer(bufferDanio);
    sonidoDanio.setVolume(80);

    //AGARRANDO ITEMS
    sf::SoundBuffer bufferItem;
    bufferItem.loadFromFile("item-sound.wav");

    sf::Sound sonidoItem;
    sonidoItem.setBuffer(bufferItem);
    sonidoItem.setVolume(100);

    sf::SoundBuffer bufferItemPu;
    bufferItemPu.loadFromFile("powerup-sound.wav");

    sf::Sound sonidoItemPu;
    sonidoItemPu.setBuffer(bufferItemPu);
    sonidoItemPu.setVolume(100);


    //WIN GAME
    sf::SoundBuffer bufferWinGame;
    bufferWinGame.loadFromFile("victory-fanfarre.wav");

    sf::Sound sonidoWinGame;
    sonidoWinGame.setBuffer(bufferWinGame);
    sonidoWinGame.setVolume(50);

    //GAME OVER
    sf::SoundBuffer bufferGameOver;
    bufferGameOver.loadFromFile("game-over.wav");

    sf::Sound sonidoGameOver;
    sonidoGameOver.setBuffer(bufferGameOver);
    sonidoGameOver.setVolume(90);

    enum EstadoJuego { EN_MENU, EN_CREDITOS, EN_JUEGO, EN_PAUSA, CARGANDO_PARTIDA, WIN };
    EstadoJuego estado = EN_MENU;

    sf::Font font;
    font.loadFromFile("8bitFont.ttf");

    sf::Text text;
    text.setFont(font);


    Personaje guerrero;
    Enemigo monstruo;
    Enemigo2 monstruo2;
    Enemigo3 monstruo3;

    constexpr std::array level1 = {
        3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
        3,0,3,3,3,3,3,0,3,3,3,3,3,0,3,3,3,3,3,3,3,3,0,0,3,
        3,0,0,0,0,0,3,0,0,0,0,0,3,0,0,0,0,3,0,0,0,3,0,0,3,
        3,3,3,3,0,0,3,3,3,3,3,0,3,3,3,3,0,3,0,3,0,3,3,0,3,
        3,0,0,3,0,0,0,0,0,0,3,0,0,0,0,3,0,0,0,3,0,0,3,0,3,
        3,0,0,3,3,3,3,3,3,0,3,3,3,3,0,3,3,3,0,3,3,0,3,0,3,
        3,0,0,0,0,0,0,0,3,0,0,0,0,3,0,0,0,3,0,0,0,0,3,0,3,
        3,0,3,3,3,3,3,0,3,3,3,3,0,3,3,3,0,3,3,3,3,0,3,0,3,
        3,0,0,0,0,0,3,0,0,0,0,3,0,0,0,3,0,0,0,0,3,0,0,0,3,
        3,3,3,3,0,0,3,3,3,3,0,0,0,3,0,3,3,3,3,0,3,3,3,0,3,
        3,0,0,3,0,0,0,0,0,3,0,0,0,3,0,0,0,0,3,0,0,0,3,3,3,
        3,0,0,3,0,3,3,3,0,3,3,3,0,3,3,3,0,3,3,3,0,3,0,0,3,
        3,0,0,0,0,0,0,3,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,3,
        3,3,3,3,3,3,0,3,3,3,0,3,3,3,0,3,3,3,3,3,3,3,3,0,3,
        3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
        3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,
        3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
        3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
    };

    constexpr std::array level2 = {
        3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
        3,0,3,3,3,3,3,0,3,3,3,0,3,3,0,3,3,3,3,3,3,3,0,0,3,
        3,0,0,0,0,0,3,0,0,0,3,0,3,0,0,0,0,0,0,3,0,3,0,0,3,
        3,3,3,3,0,0,3,3,3,0,3,0,3,3,3,3,0,3,0,3,0,3,3,0,3,
        3,0,0,3,0,0,0,0,3,0,0,0,0,0,2,3,0,0,0,3,0,0,3,0,3,
        3,0,0,3,3,3,3,0,3,3,3,3,3,0,2,3,3,3,0,3,3,0,3,0,3,
        3,0,0,0,0,0,0,0,3,0,0,0,3,0,1,0,0,3,0,0,0,0,3,0,3,
        3,0,3,3,3,3,3,0,3,3,3,0,3,0,1,0,3,3,3,3,3,0,3,0,3,
        3,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,3,0,0,3,0,3,
        3,3,3,3,0,0,3,3,3,0,0,0,0,3,0,3,3,3,3,3,0,3,3,0,3,
        3,0,0,3,0,0,0,0,3,0,0,0,0,3,0,0,0,0,3,0,0,0,3,3,3,
        3,0,0,3,0,3,3,3,3,0,3,0,3,3,3,3,0,3,3,3,0,3,0,0,3,
        3,0,0,0,0,0,0,3,0,0,3,0,0,0,0,3,0,0,0,0,0,0,0,0,3,
        3,3,3,3,3,3,0,3,3,0,3,3,3,3,0,3,3,3,3,3,3,3,3,0,3,
        3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
        3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,
        3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
        3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
    };

    constexpr std::array level3 = {
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
        3,3,3,0,3,0,3,0,3,3,0,0,0,0,3,0,3,3,3,3,0,3,3,0,3,
        3,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,3,3,3,
        3,0,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,0,3,0,3,
        3,0,0,0,0,0,0,0,2,2,1,0,1,2,2,0,0,0,0,0,0,0,3,0,3,
        3,0,3,3,3,3,3,0,2,1,1,0,1,1,2,0,3,3,3,3,3,0,3,0,3,
        3,0,3,0,0,0,0,0,2,1,1,0,1,1,2,0,0,0,0,0,3,0,3,0,3,
        3,0,3,0,3,3,3,0,2,2,1,0,1,2,2,0,3,3,3,0,3,0,3,0,3,
        3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
        3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
        3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
    };

    constexpr std::array level4 = {
        0
    };

    Laberinto laberinto;
    if (nivelActual == 1)
        laberinto.load("tileset1.png", { 32,32 }, level1.data(), 25, 20);
    else if (nivelActual == 2)
        laberinto.load("tileset1.png", { 32,32 }, level2.data(), 25, 20);
    else if (nivelActual == 3)
        laberinto.load("tileset1.png", { 32,32 }, level3.data(), 25, 20);

    Item item;
    item.respawn(laberinto);

    ItemPowerUp itemPu;
    itemPu.respawn(laberinto);

    monstruo.respawn(laberinto);
    monstruo3.respawn(laberinto);

    int timer = 60 * 5;
    int puntos = 0;


    while (window.isOpen())
    {
        if (musicaMenuCargada) {
            if ((estado == EN_MENU || estado == CARGANDO_PARTIDA || estado == EN_CREDITOS) &&
                musicaMenu.getStatus() != sf::Music::Playing) {
                musicaMenu.play();
            }
            else if (estado == EN_JUEGO && musicaMenu.getStatus() == sf::Music::Playing) {
                musicaMenu.pause();
            }
        }
        if (musicaNivelCargada) {
            if ((estado == EN_JUEGO || estado == EN_PAUSA) &&
                musicaNivel.getStatus() != sf::Music::Playing) {
                musicaNivel.play();
            }
            else if (estado == EN_MENU || estado == CARGANDO_PARTIDA || estado == EN_CREDITOS &&
                musicaNivel.getStatus() == sf::Music::Playing) {
                musicaNivel.pause();
            }
        }

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
                            if (archivoPartidas.existePartidaGuardada()) {
                                estado = CARGANDO_PARTIDA;
                            }
                            else {
                                guerrero.respawnPj();
                                monstruo.respawn(laberinto);
                                monstruo3.respawn(laberinto);
                                item.respawn(laberinto);
                                itemPu.respawn(laberinto);
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
                        else if (opcion == 1) {  // NUEVA OPCION: GUARDAR PARTIDA
                            if (guardarPartidaActual(guerrero, monstruo, monstruo3, item, itemPu, puntos, muertes, timer, gameover)) {
                                std::cout << "Partida guardada exitosamente!" << std::endl;
                            }
                            else {
                                std::cout << "Error al guardar la partida" << std::endl;
                            }
                        }
                        else if (opcion == 2) {
                            estado = EN_JUEGO;
                            nivelActual = 1;
                            laberinto.load("tileset1.png", { 32,32 }, level1.data(), 25, 20);
                            muertes = 0;
                            puntos = 0;
                            guerrero.respawnPj();
                            item.respawn(laberinto);
                            itemPu.respawn(laberinto);
                            monstruo.respawn(laberinto);
                            monstruo3.respawn(laberinto);
                            gameover = false;
                        }
                        else if (opcion == 3) {
                            estado = EN_MENU;
                            nivelActual = 1;
                            laberinto.load("tileset1.png", { 32,32 }, level1.data(), 25, 20);
                            muertes = 0;
                            puntos = 0;
                            guerrero.respawnPj();
                            item.respawn(laberinto);
                            itemPu.respawn(laberinto);
                            monstruo.respawn(laberinto);
                            monstruo3.respawn(laberinto);
                            gameover = false;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Escape) {
                        estado = EN_JUEGO;
                    }
                }
            }
            else if (estado == CARGANDO_PARTIDA) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::N) {
                        cargarPartidaGuardada(guerrero, monstruo, monstruo3, item, itemPu, puntos, muertes, timer, gameover);
                        estado = EN_JUEGO;
                    }
                    else if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::M) {
                        archivoPartidas.eliminarPartidaGuardada();
                        guerrero.respawnPj();
                        item.respawn(laberinto);
                        itemPu.respawn(laberinto);
                        monstruo.respawn(laberinto);
                        monstruo3.respawn(laberinto);
                        puntos = 0;
                        muertes = 0;
                        timer = 60 * 5;
                        gameover = false;
                        estado = EN_JUEGO;
                    }
                    else if (event.key.code == sf::Keyboard::Escape) {
                        estado = EN_MENU;
                    }
                }
            }
            else if (estado == EN_JUEGO && gameover) {
                static bool sonoGameOver = false;//BANDERA PARA REPRODUCIR UNA SOLA VEZ
                if (!sonoGameOver) {
                    sonidoGameOver.play();
                    sonoGameOver = true;
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        nivelActual = 1;
                        laberinto.load("tileset1.png", { 32,32 }, level1.data(), 25, 20);
                        muertes = 0;
                        puntos = 0;
                        guerrero.respawnPj();
                        monstruo.respawn(laberinto);
                        monstruo3.respawn(laberinto);
                        item.respawn(laberinto);
                        itemPu.respawn(laberinto);
                        gameover = false;
                        sonoGameOver = false;
                    }
                    else if (event.key.code == sf::Keyboard::Escape) {
                        estado = EN_MENU;
                        muertes = 0;
                        puntos = 0;
                        guerrero.respawnPj();
                        monstruo.respawn(laberinto);
                        monstruo3.respawn(laberinto);
                        item.respawn(laberinto);
                        itemPu.respawn(laberinto);
                        gameover = false;
                        sonoGameOver = false;
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
                opciones.setString(" [ENTER] Reiniciar    [ESC] Menu Principal ");
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
                        nivelActual = 1;
                        laberinto.load("tileset1.png", { 32,32 }, level1.data(), 25, 20);
                        muertes = 0;
                        puntos = 0;
                        guerrero.respawnPj();
                        monstruo.respawn(laberinto);
                        monstruo3.respawn(laberinto);
                        item.respawn(laberinto);
                        itemPu.respawn(laberinto);
                        gameover = false;
                    }
                    else if (event.key.code == sf::Keyboard::Escape) {
                        // vuelve al menu
                        estado = EN_MENU;
                        nivelActual = 1;
                        laberinto.load("tileset1.png", { 32,32 }, level1.data(), 25, 20);
                        muertes = 0;
                        puntos = 0;
                        guerrero.respawnPj();
                        monstruo.respawn(laberinto);
                        monstruo3.respawn(laberinto);
                        item.respawn(laberinto);
                        itemPu.respawn(laberinto);
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
                monstruo3.update(laberinto);

                if (guerrero.isColisionable(item)) {
                    item.respawn(laberinto);
                    puntos++;
                    sonidoItem.play();


                    // --- Cambio de nivel correcto ---
                    if (puntos >= 1 && nivelActual == 1) {
                        nivelActual = 2;
                        laberinto.load("tileset1.png", { 32,32 }, level2.data(), 25, 20);
                        guerrero.respawnPj();
                        monstruo.respawn(laberinto);
                        monstruo3.respawn(laberinto);
                        item.respawn(laberinto);
                        itemPu.respawn(laberinto);

                        std::cout << "Nivel 2 cargado!" << std::endl;
                    }
                    else if (puntos >= 2 && nivelActual == 2) {
                        nivelActual = 3;
                        laberinto.load("tileset1.png", { 32,32 }, level3.data(), 25, 20);
                        guerrero.respawnPj();
                        monstruo.respawn(laberinto);
                        monstruo3.respawn(laberinto);
                        item.respawn(laberinto);
                        itemPu.respawn(laberinto);

                        std::cout << "Nivel 3 cargado!" << std::endl;
                    }
                    else if (puntos == 3 && nivelActual == 3) {
                        estado = WIN;
                    }
                }

                if (guerrero.isColisionable(monstruo)) {
                    guerrero.respawnPj();
                    //puntos = 0;
                    guerrero.restartVelocity();
                    muertes++;
                    if (muertes >= 3)
                        gameover = true;
                    sonidoDanio.play();
                }

                if (guerrero.isColisionable(monstruo2)) {
                    sonidoDanio.play();
                    guerrero.respawnPj();
                    //puntos = 0;
                    guerrero.restartVelocity();
                    muertes++;
                    if (muertes >= 3)
                        gameover = true;
                }

                if (guerrero.isColisionable(monstruo3)) {
                    sonidoDanio.play();
                    guerrero.respawnPj();
                    //puntos = 0;
                    guerrero.restartVelocity();
                    muertes++;
                    if (muertes >= 3)
                        gameover = true;
                }

                if (guerrero.isColisionable(monstruo3)) {
                    sonidoDanio.play();
                    guerrero.respawnPj();
                    //puntos = 0;
                    guerrero.restartVelocity();
                    muertes++;
                    if (muertes >= 3)
                        gameover = true;
                }

                if (timer == 0 && guerrero.isColisionable(itemPu)) {
                    guerrero.addVelocity(1);
                    timer = 60 * 5;
                    itemPu.respawn(laberinto);
                    sonidoItemPu.play();
                }

                text.setString("Puntaje: " + std::to_string(puntos));
                text.setCharacterSize(15);
                text.setFillColor(sf::Color::Red);
                text.setLetterSpacing(3);

                window.draw(laberinto);
                window.draw(guerrero);
                window.draw(monstruo);
                window.draw(monstruo2);
                window.draw(monstruo3);
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
            window.draw(monstruo2);
            window.draw(monstruo3);
            window.draw(item);
            window.draw(text);

            if (timer == 0)
                window.draw(itemPu);

            menu.drawPausa(window); //MENU DE PAUSA ENCIMA
        }

        else if (estado == CARGANDO_PARTIDA) {
            menu.draw(window);

            sf::RectangleShape fondoEmergente(sf::Vector2f(500, 250));
            fondoEmergente.setFillColor(sf::Color(0, 0, 0, 220));
            fondoEmergente.setPosition(150, 180);
            window.draw(fondoEmergente);

            sf::Text mensaje;
            mensaje.setFont(font);
            mensaje.setString("Partida guardada encontrada\n\n\n[1] Continuar partida guardada\n\n[2] Iniciar nueva partida\n\n[ESC] Volver al menu");
            mensaje.setCharacterSize(18);
            mensaje.setFillColor(sf::Color::White);
            mensaje.setPosition(170, 220);
            window.draw(mensaje);
        }

        else if (estado == EN_CREDITOS)
        {
            menu.drawCreditos(window);
        }
        else if (estado == WIN)
        {
            static sf::Texture texWin;
            static bool cargada = false;
            static bool sonoWinGame = false;
            if (!sonoWinGame) {
                musicaNivel.stop();
                sonidoWinGame.play();
                sonoWinGame = true;
            }
            if (!cargada) {
                if (!texWin.loadFromFile("youwin.png")) {
                    std::cout << "Error cargando youwin.png";
                }
                cargada = true;
            }

            sf::Sprite winSprite(texWin);
            winSprite.setPosition(0, 0);
            window.draw(winSprite);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                puntos = 0;
                nivelActual = 1;
                estado = EN_MENU;
            }
        }
        window.display();
    }

    return 0;
}
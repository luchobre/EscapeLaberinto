#define _CRT_SECURE_NO_WARNINGS //PARA QUE VISUAL STUDIO TRABAJE BIEN CON LAS FUNCIONES DE ARCHIVO Y NO DE ERROR DE SEGURIDAD
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <array>
#include "Personaje.h"
#include "Enemigo.h"
#include "Enemigo2.h"
#include "Item.h"
#include "Colisionable.h"
#include "ItemPowerUp.h"
#include "Laberinto.h"
#include "Menu.h"
#include "GuardarPartida.h"
#include "ArchivoPartida.h"

constexpr int NUM_VIDAS = 3;

// Archivo de partida global
ArchivoPartida archivoPartidas("partida_guardada.dat");

// Función para guardar partida
static bool guardarPartidaActual(Personaje& guerrero, Enemigo& monstruo, Item& item,
    ItemPowerUp& itemPu, int puntos, int muertes, int timer, bool gameover)
{
    GuardarPartida partida;

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
// Función para cargar partida
static void cargarPartidaGuardada(Personaje& guerrero, Enemigo& monstruo, Item& item,
    ItemPowerUp& itemPu, int& puntos, int& muertes, int& timer, bool& gameover)
{
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
    int muertes = 0, puntos = 0, timer = 60 * 5;
    bool gameover = false;

    sf::Clock relojJuego, relojPowerUp;
    sf::Time cooldownPU = sf::seconds(10.f);

    std::srand(static_cast<unsigned>(std::time(0)));

    sf::RenderWindow window(sf::VideoMode(800, 640), "Escape del Laberinto");
    window.setFramerateLimit(60);

    // --- Cargar texturas de corazones ---
    sf::Texture texCorazonLleno, texCorazonVacio;
    if (!texCorazonLleno.loadFromFile("corazonRojo.png")) std::cout << "Error: no se pudo cargar corazonRojo.png\n";
    if (!texCorazonVacio.loadFromFile("corazonVacio.png")) std::cout << "Error: no se pudo cargar corazonVacio.png\n";

    std::vector<sf::Sprite> corazones(NUM_VIDAS);
    for (int i = 0; i < NUM_VIDAS; ++i) {
        corazones[i].setTexture(texCorazonLleno);
        corazones[i].setOrigin(0.f, 0.f);
    }

    float targetHeight = 40.f;
    float scaleLleno = targetHeight / static_cast<float>(texCorazonLleno.getSize().y);
    float scaleVacio = targetHeight / static_cast<float>(texCorazonVacio.getSize().y);
    float espacio = 4.f;
    float margenDerecho = 10.f;
    std::vector<float> scaledWidths(NUM_VIDAS);

    // --- Menu ---
    Menu menu(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    enum EstadoJuego { EN_MENU, EN_CREDITOS, EN_JUEGO, EN_PAUSA, CARGANDO_PARTIDA };
    EstadoJuego estado = EN_MENU;

    sf::Font font;
    font.loadFromFile("8bitFont.ttf");
    sf::Text text;
    text.setFont(font);

    // --- Objetos del juego ---
    Personaje guerrero;
    Enemigo monstruo;
    Enemigo2 monstruo2;
    Item item;
    ItemPowerUp itemPu;
    Nivel nivel;

    // --- Laberinto ---
    constexpr std::array<int, 25 * 20> level = { /* 500 valores del laberinto */ };
    Laberinto laberinto;
    if (!laberinto.load("tileset1.png", { 32,32 }, level.data(), 25, 20)) return -1;

    // --- Respawn inicial ---
    guerrero.respawnPj();
    item.respawn(laberinto);
    itemPu.respawn(laberinto);
    monstruo.respawn(laberinto);
    monstruo2.respawn(laberinto);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            // --- Switch de estados ---
            switch (estado) {
            case EN_MENU:
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) menu.MoveUp();
                    else if (event.key.code == sf::Keyboard::Down) menu.MoveDown();
                    else if (event.key.code == sf::Keyboard::Enter) {
                        int opcion = menu.GetPressedItem();
                        if (opcion == 0) {
                            if (archivoPartidas.existePartidaGuardada())
                                estado = CARGANDO_PARTIDA;
                            else {
                                guerrero.respawnPj(); monstruo.respawn(laberinto); monstruo2.respawn(laberinto);
                                item.respawn(laberinto); itemPu.respawn(laberinto);
                                puntos = 0; muertes = 0; gameover = false; timer = 60 * 5;
                                estado = EN_JUEGO;
                            }
                        }
                        else if (opcion == 1) estado = EN_CREDITOS;
                        else if (opcion == 2) window.close();
                    }
                }
                break;

            case EN_PAUSA:
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) estado = EN_JUEGO;
                    else if (event.key.code == sf::Keyboard::Enter) {
                        int opcion = menu.GetPressedItemPausa();
                        switch (opcion) {
                        case 0: estado = EN_JUEGO; break;
                        case 1:
                            if (guardarPartidaActual(guerrero, monstruo, item, itemPu, puntos, muertes, timer, gameover))
                                std::cout << "Partida guardada!\n";
                            break;
                        case 2:
                            guerrero.respawnPj(); puntos = 0; muertes = 0; gameover = false; break;
                        case 3:
                            estado = EN_MENU; guerrero.respawnPj(); puntos = 0; muertes = 0; gameover = false; break;
                        }
                    }
                }
                break;

            case CARGANDO_PARTIDA:
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Num1) {
                        cargarPartidaGuardada(guerrero, monstruo, item, itemPu, puntos, muertes, timer, gameover);
                        estado = EN_JUEGO;
                    }
                    else if (event.key.code == sf::Keyboard::Num2) {
                        archivoPartidas.eliminarPartidaGuardada();
                        guerrero.respawnPj(); monstruo.respawn(laberinto); monstruo2.respawn(laberinto);
                        item.respawn(laberinto); itemPu.respawn(laberinto);
                        puntos = 0; muertes = 0; timer = 60 * 5; gameover = false;
                        estado = EN_JUEGO;
                    }
                    else if (event.key.code == sf::Keyboard::Escape) estado = EN_MENU;
                }
                break;

            case EN_JUEGO:
                if (!gameover && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                    estado = EN_PAUSA;
                break;

            default: break;
            }
        }

        // --- Actualización del juego ---
        if (estado == EN_JUEGO && !gameover) {
            sf::Time dt = relojJuego.restart();
            guerrero.update(laberinto);
            monstruo.update(laberinto);
            monstruo2.update(laberinto);

            auto colisionPersonaje = [&](Colisionable& c) {
                if (guerrero.isColisionable(c)) {
                    guerrero.respawnPj(); guerrero.restartVelocity();
                    puntos = 0; muertes++;
                    if (muertes >= NUM_VIDAS) gameover = true;
                }
                };
            colisionPersonaje(monstruo);
            colisionPersonaje(monstruo2);

            if (guerrero.isColisionable(item)) {
                item.respawn(laberinto);
                puntos++; nivel.agregarPuntos(1);
                if (nivel.checkSubirNivel()) {
                    int nuevoNivel = nivel.getNivelActual();
                    laberinto.loadByLevel(nuevoNivel);
                    item.respawn(laberinto); itemPu.respawn(laberinto);
                    monstruo.respawn(laberinto); monstruo2.respawn(laberinto);
                }
            }

            if (relojPowerUp.getElapsedTime() >= cooldownPU && guerrero.isColisionable(itemPu)) {
                guerrero.addVelocity(1);
                itemPu.respawn(laberinto);
                relojPowerUp.restart();
            }
        }
    }
        // --- Renderizado ---
        window.clear();
        switch (estado) {
        case EN_JUEGO:
            window.draw(laberinto); window.draw(guerrero); window.draw(monstruo); window.draw(monstruo2);
            window.draw(item);
            if (relojPowerUp.getElapsedTime() >= cooldownPU) window.draw(itemPu);

            text.setString("Puntaje: " + std::to_string(puntos));
            window.draw(text);

            for (int i = 0; i < NUM_VIDAS; ++i) {
                corazones[i].setTexture(i < NUM_VIDAS - muertes ? texCorazonLleno : texCorazonVacio);
                window.draw(corazones[i]);
            }
            break;

        case EN_MENU: menu.draw(window); break;
        case EN_PAUSA: window.draw(laberinto); window.draw(guerrero); menu.drawPausa(window); break;
        case CARGANDO_PARTIDA: menu.draw(window); break;
        case EN_CREDITOS: menu.drawCreditos(window); break;
        }
        window.display();

        return 0;
    }

   
    

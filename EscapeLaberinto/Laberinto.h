#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Laberinto : public sf::Drawable, public sf::Transformable
{
public:

    // Carga el tileset y arma el mapa 
    bool load(const std::string& tileset,
              sf::Vector2u tileSize,
              const int* tiles,
              unsigned int width,
              unsigned int height);

    // Cargar un mapa y tileset según el nivel (1, 2 o 3)
    bool loadByLevel(int nivel);

   
    bool loadFromFile(const std::string& mapFile);

    // Validación de colisiones (solo pasto = 0 es caminable)
    bool esCaminable(sf::FloatRect bounds, sf::Vector2u tileSize) const;

    unsigned int getWidth() const { return m_width; }
    unsigned int getHeight() const { return m_height; }
    sf::Vector2u getTileSize() const;

    int getTile(unsigned int row, unsigned int col) const;

private:

    void draw(sf::RenderTarget& target,
              sf::RenderStates states) const override;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    // Almacena el mapa cada número es un tile
    std::vector<int> m_tiles;

    sf::Vector2u m_tileSize;
    unsigned int m_width = 0;
    unsigned int m_height = 0;

    // Guardan el archivo actual del tileset y mapa
    std::string tilesetFile;
    std::string mapFile;
};
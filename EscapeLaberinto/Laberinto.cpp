#include <vector>
#include "Laberinto.h"
#include <fstream>
#include <sstream>
#include "Mapas.h"


bool Laberinto::load(const std::string& tileset,
    sf::Vector2u tileSize,
    const int* tiles,
    unsigned int width,
    unsigned int height)
{
    // se guardan los datos
    m_tileSize = tileSize;
    m_width = width;
    m_height = height;

    // tiles en un vector interno
    m_tiles.assign(tiles, tiles + width * height);

    // se cargan las texturas del tileset
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // creamos array
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    unsigned int tilesPorFila = m_tileset.getSize().x / tileSize.x;

    for (unsigned int j = 0; j < height; ++j)      
    {
        for (unsigned int i = 0; i < width; ++i)   
        {
            int tileNumber = m_tiles[j * width + i];

            int tu = tileNumber % tilesPorFila;
            int tv = tileNumber / tilesPorFila;

            
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // 4 vértices del tile
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // coordenadas de textura
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }

    return true;
}


 bool Laberinto::loadByLevel(int nivel)
   {
       const int* mapa = nullptr;

        if (nivel == 1) mapa = mapaNivel1;
        else if (nivel == 2) mapa = mapaNivel2;
        else if (nivel == 3) mapa = mapaNivel3;
        else return false;

        tilesetFile = "tileset_nivel" + std::to_string(nivel) + ".png";
        return load(tilesetFile,    
            sf::Vector2u(32, 32),
            mapa,
            MAP_WIDTH,
            MAP_HEIGHT);
 }
 bool Laberinto::loadFromFile(const std::string& mapFile)
 {
     std::ifstream file(mapFile);
     if (!file.is_open())
         return false;

     std::vector<int> tiles;
     std::string line;
     unsigned int width = 0, height = 0;

     while (std::getline(file, line)) {
         std::istringstream ss(line);
         int tile;
         unsigned int rowWidth = 0;
         while (ss >> tile) {
             tiles.push_back(tile);
             rowWidth++;
         }
         if (width == 0)
             width = rowWidth;
         height++;
     }

     file.close();

     return load(tilesetFile, m_tileSize, tiles.data(), width, height);
 }


bool Laberinto::esCaminable(sf::FloatRect bounds, sf::Vector2u tileSize) const
{
    sf::Vector2f puntos[4] = {
        {bounds.left, bounds.top},
        {bounds.left + bounds.width, bounds.top},
        {bounds.left, bounds.top + bounds.height},
        {bounds.left + bounds.width, bounds.top + bounds.height}
    };

    for (int i = 0; i < 4; i++)
    {
        int col = puntos[i].x / tileSize.x;
        int row = puntos[i].y / tileSize.y;

        if (col < 0 || row < 0 || col >= m_width || row >= m_height)
            return false;

        int tileNumber = m_tiles[row * m_width + col];
        if (tileNumber != 0) // 0 = pasto
            return false;
    }

    return true;
}


void Laberinto::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}

int Laberinto::getTile(unsigned int row, unsigned int col) const
{
    return m_tiles[row * m_width + col];
}
sf::Vector2u Laberinto::getTileSize() const
{
    return m_tileSize;
}

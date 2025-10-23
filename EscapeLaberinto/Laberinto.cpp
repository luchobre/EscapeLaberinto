#include <vector>
#include "Laberinto.h"

bool Laberinto::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
    if (!m_tileset.loadFromFile(tileset))
        return false;

    m_vertices.setPrimitiveType(sf::Triangles);
    m_vertices.resize(width * height * 6);

    for (unsigned int i = 0; i < width; ++i)
    {
        for (unsigned int j = 0; j < height; ++j)
        {
            int tileNumber = tiles[i + j * width];

            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            sf::Vertex* triangles = &m_vertices[(i + j * width) * 6];

            // Posiciones
            triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

            // Texturas
            triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        }
    }

    m_tiles.assign(tiles, tiles + width * height);
    return true;
}

bool Laberinto::esCaminable(sf::Vector2f posicion, sf::Vector2u tilesize) const
{
    int col = posicion.x / tilesize.x;
    int row = posicion.y / tilesize.y;

    if(col<0 || row<0 || col >=25 || row >=20)
        return false;

    int tileNumber = m_tiles[row * 25 + col];
    return tileNumber == 0;
}

void Laberinto::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}


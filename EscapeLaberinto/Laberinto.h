#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <filesystem>

class Laberinto : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

    //para caminar solo sobre el pasto
    bool esCaminable(sf::Vector2f posicion, sf::Vector2u tilesize) const;
  
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    //se guardan los tiles para ver que no se choque
    std::vector<int> m_tiles;
};
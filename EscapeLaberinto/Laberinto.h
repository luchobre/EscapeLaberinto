#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>

class Laberinto : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};
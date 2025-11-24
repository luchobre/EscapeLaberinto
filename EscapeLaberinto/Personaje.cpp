#include "Personaje.h"
#include "Laberinto.h"

Personaje::Personaje()
{
    _velocity = { 2,2 };
    _texture.loadFromFile("playerIcon.png");
    _sprite.setTexture(_texture);
    _sprite.setScale(0.5f, 0.5f);
    sf::FloatRect bounds = _sprite.getLocalBounds();
    _sprite.setOrigin(bounds.width / 2, bounds.height / 2);
    //Audio
    bufferCaminar.loadFromFile("step-on-stone.wav");
    sonidoCaminar.setBuffer(bufferCaminar);
    sonidoCaminar.setVolume(35);


    _resIzqX = 0;
    _resDerX = 800;
    _resSupY = 0;
    _resInfY = 600;

    tileFrameAnterior = sf::Vector2i(-1, -1); //SE INICIALIZA ASI PARA QUE NO FALLE EN EL PRIMER FRAME
}

//OBTENER POSICION Y COMPARAR CON TAMAÑO DE TILES PARA VER SI SE MOVIO
sf::Vector2i Personaje::getTilePosition(const Laberinto& laberinto) const {
    sf::Vector2f pos = _sprite.getPosition();
    sf::Vector2u tileSize = laberinto.getTileSize();
    int tileX = static_cast<int>(pos.x) / tileSize.x;
    int tileY = static_cast<int>(pos.y) / tileSize.y;
    return sf::Vector2i(tileX, tileY);
}

void Personaje::update(const Laberinto& laberinto)
{
    sf::Vector2f velocity = { 0,0 };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        velocity.y = -_velocity.y;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        velocity.y = _velocity.y;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        velocity.x = _velocity.x;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        velocity.x = -_velocity.x;
    }

    if (velocity.x == 0 && velocity.y == 0) {
        return;
    }

    sf::Vector2i tileAntesDeCaminar = getTilePosition(laberinto);//GUARDAR POSICION PARA COMPARAR (EN ESTE FRAME DEL JUEGO)
    sf::FloatRect newBounds = _sprite.getGlobalBounds();
    newBounds.left += velocity.x;
    newBounds.top += velocity.y;

    sf::Vector2u tileSize = laberinto.getTileSize();
    bool puedeMoverse = laberinto.esCaminable(newBounds, tileSize);
    if (puedeMoverse) {
        _sprite.move(velocity);
    }
    sf::Vector2i tileDespuesDeCaminar = getTilePosition(laberinto);//DETECTAR NUEVA POSICION (TAMBIEN PARA ESTE FRAME)
    //COMPARAR SI SE MOVIO DE TILE Y ACTIVAR SONIDO
    if (tileDespuesDeCaminar != tileAntesDeCaminar && puedeMoverse) {
        sonidoCaminar.play();
        //VELOCIDAD DE SONIDO (FALTA CORREGIR POR SI SUENA MUY ACELERADO)
        float pitch = 0.5f + (_velocity.x * 0.05f);
        sonidoCaminar.setPitch(std::max(0.5f, std::min(1.5f, pitch)));
    }
    //ACA SE GUARDA PARA LA PROXIMA COMPARACION EN EL SIGUIENTE FRAME
    tileFrameAnterior = tileDespuesDeCaminar;

    if (velocity.x < 0) {
        _sprite.setScale(-0.5f, 0.5f);
    }
    else if (velocity.x > 0) {
        _sprite.setScale(0.5f, 0.5f);
    }

    if (_sprite.getPosition().x < _resIzqX + _sprite.getGlobalBounds().width / 2)
        _sprite.setPosition(_resIzqX + _sprite.getGlobalBounds().width / 2, _sprite.getPosition().y);

    if (_sprite.getPosition().x > _resDerX - _sprite.getGlobalBounds().width / 2)
        _sprite.setPosition(_resDerX - _sprite.getGlobalBounds().width / 2, _sprite.getPosition().y);

    if (_sprite.getPosition().y < _resSupY + _sprite.getGlobalBounds().height / 2)
        _sprite.setPosition(_sprite.getPosition().x, _resSupY + _sprite.getGlobalBounds().height / 2);

    if (_sprite.getPosition().y > _resInfY - _sprite.getGlobalBounds().height / 2)
        _sprite.setPosition(_sprite.getPosition().x, _resInfY - _sprite.getGlobalBounds().height / 2);

}

void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

void Personaje::respawnPj()
{
    _sprite.setPosition(50, 50);
    tileFrameAnterior = sf::Vector2i(-1, -1);//EN CASO DE RESPAWN RESETEA ESTO
}

void Personaje::addVelocity(float velocity)
{
    _velocity.x += velocity;
    _velocity.y += velocity;
}

void Personaje::restartVelocity()
{
    _velocity.x = 2;
    _velocity.y = 2;
}

sf::FloatRect Personaje::getBounds() const
{
    return _sprite.getGlobalBounds();
}

//PARA GUARDAR Y CARGAR
sf::Vector2f Personaje::getVelocity() const {
    return _velocity;
}

sf::Vector2f Personaje::getPosition() const {
    return _sprite.getPosition();
}

void Personaje::setVelocity(float velX, float velY) {
    _velocity.x = velX;
    _velocity.y = velY;
}

void Personaje::setPosition(float x, float y) {
    _sprite.setPosition(x, y);
}
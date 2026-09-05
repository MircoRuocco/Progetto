#pragma once

#include <SFML/Graphics.hpp>

class Player
{
private:

    sf::RectangleShape shape;

    float velocitaY;
    float angolo;

    bool aTerra;
    bool morto;

    const float gravita = 1200.f;
    const float forzaSalto = -600.f;
    const float velocitaRotazione = 270.f;

public:

    Player();

    void salta();

    void aggiorna(float deltaTime);

    void atterra(float y);

    void jumpPad(float forza);

    void muori();

    void reset();

    void disegna(sf::RenderWindow& window) const;

    sf::Vector2f getPosition() const;

    float getVelocitaY() const;

    bool isATerra() const;

    bool isMorto() const;

    sf::FloatRect getHitbox() const;
};
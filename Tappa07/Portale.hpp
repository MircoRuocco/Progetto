#pragma once

#include <SFML/Graphics.hpp>

class Portale
{
private:

    sf::CircleShape shape;

    sf::Vector2f posizioneIniziale;

public:

    Portale(float x, float y);

    void aggiorna(float deltaTime, float velocitaLivello);

    void reset();

    sf::FloatRect getBounds() const;

    void disegna(sf::RenderWindow& window) const;
};
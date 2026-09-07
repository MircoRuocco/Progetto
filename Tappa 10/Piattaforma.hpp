#pragma once

#include <SFML/Graphics.hpp>

class Piattaforma
{
private:

    sf::RectangleShape shape;

    sf::Vector2f posizioneIniziale;

public:

    Piattaforma(float x, float y);

    void aggiorna(float deltaTime, float velocitaLivello);

    void reset();

    sf::FloatRect getBounds() const;

    void disegna(sf::RenderWindow& window) const;
};
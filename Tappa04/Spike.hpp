#pragma once

#include <SFML/Graphics.hpp>

class Spike
{
private:

    sf::CircleShape shape;

    // Posizione iniziale, utile per il restart
    sf::Vector2f posizioneIniziale;

    // Margini della hitbox
    const float margineX = 10.f;
    const float margineAlto = 10.f;

public:

    // Costruttore
    Spike(float x);

    // Movimento verso sinistra
    void aggiorna(float deltaTime, float velocitaLivello);

    // Riporta lo spike alla posizione iniziale
    void reset();

    // Restituisce la hitbox
    sf::FloatRect getHitbox() const;

    // Disegna lo spike
    void disegna(sf::RenderWindow& window) const;

    // Disegna la hitbox gialla di debug
    void disegnaHitbox(sf::RenderWindow& window) const;
};
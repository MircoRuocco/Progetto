#include "Piattaforma.hpp"

Piattaforma::Piattaforma(float x, float y)
    : shape({150.f, 30.f}),
      posizioneIniziale({x, y})
{
    shape.setFillColor(sf::Color::Magenta);

    shape.setPosition(posizioneIniziale);
}


void Piattaforma::aggiorna(
    float deltaTime,
    float velocitaLivello)
{
    shape.move({
        -velocitaLivello * deltaTime,
        0.f
    });
}


void Piattaforma::reset()
{
    shape.setPosition(posizioneIniziale);
}



sf::FloatRect Piattaforma::getBounds() const
{
    return shape.getGlobalBounds();
}



void Piattaforma::disegna(
    sf::RenderWindow& window) const
{
    window.draw(shape);
}
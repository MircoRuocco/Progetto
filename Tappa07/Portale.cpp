#include "Portale.hpp"


Portale::Portale(float x, float y)
    : shape(50.f),
      posizioneIniziale({x, y})
{
    shape.setFillColor(sf::Color::Transparent);

    shape.setOutlineColor(sf::Color::Magenta);

    shape.setOutlineThickness(8.f);

    shape.setPosition(posizioneIniziale);
}


void Portale::aggiorna(float deltaTime, float velocitaLivello)
{
    shape.move({
        -velocitaLivello * deltaTime,
        0.f
    });
}


void Portale::reset()
{
    shape.setPosition(posizioneIniziale);
}


sf::FloatRect Portale::getBounds() const
{
    return shape.getGlobalBounds();
}


void Portale::disegna(sf::RenderWindow& window) const
{
    window.draw(shape);
}
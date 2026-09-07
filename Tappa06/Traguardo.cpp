#include "Traguardo.hpp"


Traguardo::Traguardo(float x, float y)
    : shape({20.f, 150.f}),
      posizioneIniziale({x, y})
{
    shape.setFillColor(sf::Color::Cyan);

    shape.setPosition(posizioneIniziale);
}


void Traguardo::aggiorna(float deltaTime, float velocitaLivello)
{
    shape.move({
        -velocitaLivello * deltaTime,
        0.f
    });
}


void Traguardo::reset()
{
    shape.setPosition(posizioneIniziale);
}


sf::FloatRect Traguardo::getBounds() const
{
    return shape.getGlobalBounds();
}


void Traguardo::disegna(sf::RenderWindow& window) const
{
    window.draw(shape);
}
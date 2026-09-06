#include "JumpPad.hpp"

JumpPad::JumpPad(float x, float y)
    : shape({60.f, 10.f}),
      posizioneIniziale({x, y})
{
    shape.setFillColor(sf::Color::Yellow);

    shape.setPosition(posizioneIniziale);
}


void JumpPad::aggiorna(float deltaTime, float velocitaLivello)
{

    shape.move({
        -velocitaLivello * deltaTime,
        0.f
    });
}


void JumpPad::reset()
{
    shape.setPosition(posizioneIniziale);
}


sf::FloatRect JumpPad::getBounds() const
{
    return shape.getGlobalBounds();
}


void JumpPad::disegna(
    sf::RenderWindow& window) const
{
    window.draw(shape);
}
#include "Spike.hpp"


Spike::Spike(float x)
    : shape(25.f, 3),
      posizioneIniziale({x, 462.5f})
{
    shape.setFillColor(sf::Color::Red);

    shape.setPosition(posizioneIniziale);
}


void Spike::aggiorna(float deltaTime, float velocitaLivello)
{
    shape.move({
        -velocitaLivello * deltaTime,
        0.f
    });
}


void Spike::reset()
{
    shape.setPosition(posizioneIniziale);
}



sf::FloatRect Spike::getHitbox() const
{
    auto bounds = shape.getGlobalBounds();

    return sf::FloatRect(
        {
            bounds.position.x + margineX,
            bounds.position.y + margineAlto
        },
        {
            bounds.size.x - 2.f * margineX,
            bounds.size.y - margineAlto
        }
    );
}



void Spike::disegna(sf::RenderWindow& window) const
{
    window.draw(shape);
}



void Spike::disegnaHitbox(sf::RenderWindow& window) const
{
    sf::FloatRect hitbox = getHitbox();

    sf::RectangleShape rettangoloHitbox({
        hitbox.size.x,
        hitbox.size.y
    });

    rettangoloHitbox.setPosition(hitbox.position);

    rettangoloHitbox.setFillColor(sf::Color::Transparent);

    rettangoloHitbox.setOutlineColor(sf::Color::Yellow);

    rettangoloHitbox.setOutlineThickness(2.f);

    window.draw(rettangoloHitbox);
}
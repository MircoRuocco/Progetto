#include "Player.hpp"

// -------------------------
// COSTRUTTORE
// -------------------------

Player::Player()
    : shape({50.f, 50.f}),
      velocitaY(0.f),
      angolo(0.f),
      aTerra(true),
      morto(false)
{
    shape.setFillColor(sf::Color::Green);

    shape.setOrigin({25.f, 25.f});

    shape.setPosition({175.f, 475.f});
}


void Player::salta()
{
    if (aTerra && !morto)
    {
        velocitaY = forzaSalto;
        aTerra = false;
    }
}

void Player::aggiorna(float deltaTime)
{
    if (morto)
        return;

    velocitaY += gravita * deltaTime;

    shape.move({
        0.f,
        velocitaY * deltaTime
    });

    aTerra = false;
    angolo += velocitaRotazione * deltaTime;
    shape.setRotation(sf::degrees(angolo));
}

void Player::atterra(float y)
{
    shape.setPosition({
        shape.getPosition().x,
        y
    });

    velocitaY = 0.f;
    aTerra = true;
    angolo = 0.f;

    shape.setRotation(sf::degrees(0.f));
}

void Player::jumpPad(float forza)
{
    velocitaY = forza;
    aTerra = false;
}

void Player::muori()
{
    morto = true;

    shape.setFillColor(sf::Color::Blue);
}

void Player::reset()
{
    shape.setPosition({175.f, 475.f});

    velocitaY = 0.f;
    angolo = 0.f;

    aTerra = true;
    morto = false;

    shape.setRotation(sf::degrees(0.f));
    shape.setFillColor(sf::Color::Green);
}


void Player::disegna(sf::RenderWindow& window) const
{
    window.draw(shape);
}






//GET 

sf::Vector2f Player::getPosition() const
{
    return shape.getPosition();
}

float Player::getVelocitaY() const
{
    return velocitaY;
}

bool Player::isATerra() const
{
    return aTerra;
}

bool Player::isMorto() const
{
    return morto;
}


sf::FloatRect Player::getHitbox() const
{
    return sf::FloatRect(
        {
            shape.getPosition().x - 20.f,
            shape.getPosition().y - 20.f
        },
        {
            40.f,
            40.f
        }
    );
}
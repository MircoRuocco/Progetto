#include "Player.hpp"


// -------------------------
// COSTRUTTORE
// -------------------------

Player::Player()
    : shape({50.f, 50.f}),
      velocitaY(0.f),
      angolo(0.f),
      aTerra(true),
      morto(false),
      modalita(ModalitaPlayer::Cubo)
{
    shape.setFillColor(sf::Color::Green);

    shape.setOrigin({25.f, 25.f});

    shape.setPosition({175.f, 475.f});
}




void Player::salta()
{
    if (modalita == ModalitaPlayer::Cubo &&
        aTerra &&
        !morto)
    {
        velocitaY = forzaSalto;
        aTerra = false;
    }
}

void Player::aggiorna(float deltaTime, 
    std::vector<Spike>& spikes, 
    std::vector<Piattaforma>& piattaforme, 
    std::vector<JumpPad>& jumpPads)
{
     if (morto)
        return;



    if (modalita == ModalitaPlayer::Navicella)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space))
        {
            velocitaY = -velocitaNavicella;
        }
        else
        {
            velocitaY = velocitaNavicella;
        }

        shape.move({
            0.f,
            velocitaY * deltaTime
        });

        float metaAltezza = shape.getSize().y / 2.f;

        // Collisione con soffitto e terreno
        if (shape.getPosition().y - metaAltezza <= 0.f ||
            shape.getPosition().y + metaAltezza >= 500.f)
        {
            muori();
        }

        // Collisione con gli spike
        sf::FloatRect hitboxPlayer = getHitbox();

        for (const auto& spike : spikes)
        {
            if (hitboxPlayer.findIntersection(spike.getHitbox()))
            {
                muori();
            }
        }

        return;
    }
    
    float yPrecedente = shape.getPosition().y;


    velocitaY += gravita * deltaTime;

    shape.move({0.f, velocitaY * deltaTime });

    aTerra = false;
    angolo += velocitaRotazione * deltaTime;
    shape.setRotation(sf::degrees(angolo));



    // collisione col terreno 
    if (shape.getPosition().y >= 475.f)
    {
        atterra(475.f);
    }

    // collisione con le piattaforme 
    for (const auto& piattaforma : piattaforme)
    {
        auto bounds = piattaforma.getBounds();

        float cimaPiattaforma = bounds.position.y;

        float fondoPrecedente = yPrecedente + 25.f;

        float fondoAttuale = shape.getPosition().y + 25.f;

        float sinistraPlayer = shape.getPosition().x - 25.f;

        float destraPlayer = shape.getPosition().x + 25.f;

        float sinistraPiattaforma = bounds.position.x;

        float destraPiattaforma = bounds.position.x + bounds.size.x;

        bool sovrappostoX = destraPlayer > sinistraPiattaforma && sinistraPlayer < destraPiattaforma;


        if (velocitaY >= 0.f && sovrappostoX && fondoPrecedente <= cimaPiattaforma && fondoAttuale >= cimaPiattaforma )
        {
            atterra(cimaPiattaforma - 25.f);
        }


    }

    // collisione con il JumpPad
    for (const auto& jumpPadd : jumpPads)
    {
        auto boundsPad = jumpPadd.getBounds();

        sf::FloatRect piediPlayer(
            {
                shape.getPosition().x - 20.f,
                shape.getPosition().y + 15.f
            },
            {
                40.f,
                10.f
            }
        );

        if (piediPlayer.findIntersection(boundsPad))
        {
            jumpPad(forzaJumpPad);
        }
    }

    // collisione con le spike 
    sf::FloatRect hitboxPlayer = getHitbox();

    for (const auto& spike : spikes)
    {
        if (hitboxPlayer.findIntersection(spike.getHitbox()))
        {
            muori();
        }
    }


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

void Player::jumpPad(float forzaJumpPad)
{
    velocitaY = forzaJumpPad;
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

    modalita = ModalitaPlayer::Cubo;

    shape.setSize({50.f, 50.f});
    shape.setOrigin({25.f, 25.f});

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

void Player::attivaNavicella()
{
    modalita = ModalitaPlayer::Navicella;

    shape.setSize({70.f, 35.f});
    shape.setOrigin({35.f, 17.5f});

    shape.setFillColor(sf::Color(255, 165, 0));

    velocitaY = 0.f;
    angolo = 0.f;

    shape.setRotation(sf::degrees(0.f));
}

void Player::attivaCubo()
{
    modalita = ModalitaPlayer::Cubo;

    shape.setSize({50.f, 50.f});
    shape.setOrigin({25.f, 25.f});

    shape.setFillColor(sf::Color::Green);

    velocitaY = 0.f;
}

bool Player::isNavicella() const
{
    return modalita == ModalitaPlayer::Navicella;
}
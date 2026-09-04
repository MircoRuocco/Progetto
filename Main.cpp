#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>


// -------------------------
// FUNZIONI PATTERN OSTACOLI 
// -------------------------

const float distanzaSpike = 50.f;
const float margineSpikeX = 10.f;
const float margineSpikeAlto = 10.f;

void patternSpike(std::vector<float>& posizioni, float x, int quantita)
{
    for (int i = 0; i < quantita; i++)
    {
        posizioni.push_back( x + distanzaSpike * i);
    }
}




int main()
{
    // -------------------------
    // FINESTRA
    // -------------------------

    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Geometry Dash 2"
    );

    window.setFramerateLimit(60);

    // -------------------------
    // PLAYER
    // -------------------------
    sf::RectangleShape player({50.f, 50.f});
    player.setFillColor(sf::Color::Green);
    player.setOrigin({25.f, 25.f});
    // Posizione iniziale
    player.setPosition({175.f, 475.f});


    // -------------------------
    // TERRENO
    // -------------------------

    sf::RectangleShape terreno({800.f, 100.f});
    terreno.setFillColor(sf::Color(100, 100, 100));
    terreno.setPosition({0.f, 500.f});


    // -------------------------
    // PIATTAFORME
    // -------------------------

    std::vector<sf::Vector2f> posizioniPiattaforme = {{1850.f, 400.f}, {2100.f, 275.f},{2200.f, 275.f}};
    std::vector<sf::RectangleShape> piattaforme;

    for (const auto& posizione : posizioniPiattaforme)
    {
        sf::RectangleShape piattaforma({150.f, 30.f});

        piattaforma.setFillColor(sf::Color::Magenta);
        piattaforma.setPosition(posizione);

        piattaforme.push_back(piattaforma);
    }


    // -------------------------
    // JUMP PAD
    // -------------------------

    std::vector<sf::Vector2f> posizioniJumpPad = {{2900.f, 490.f}};
    std::vector<sf::RectangleShape> jumpPads;

    for (const auto& posizione : posizioniJumpPad)
    {
        sf::RectangleShape jumpPad({60.f, 10.f});

        jumpPad.setFillColor(sf::Color::Yellow);
        jumpPad.setPosition(posizione);

        jumpPads.push_back(jumpPad);
    }




    // -------------------------
    // OSTACOLO
    // -------------------------

    // Posizioni iniziali degli ostacoli sull'asse X
    std::vector<float> posizioniOstacoli;    

    patternSpike(posizioniOstacoli, 750.f, 1);
    patternSpike(posizioniOstacoli, 1100.f, 2);
    patternSpike(posizioniOstacoli, 1500.f, 3);
    patternSpike(posizioniOstacoli, 2100.f, 10);


   
    // Contenitore di tutti gli ostacoli
    std::vector<sf::CircleShape> ostacoli;

    // Creiamo un triangolo per ogni posizione
    for (float x : posizioniOstacoli)
    {
        sf::CircleShape ostacolo(25.f, 3);

        ostacolo.setFillColor(sf::Color::Red);

        // Altezza 50 px: y = 450 lo appoggia sul terreno
        ostacolo.setPosition({x, 462.5f});

        ostacoli.push_back(ostacolo);
    }

    
    // Velocita' di scorrimento del livello
    const float velocitaLivello = 250.f;





    // -------------------------
    // FISICA DEL PLAYER
    // -------------------------

    float velocitaY = 0.f;

    float angolo = 0.f;
    const float velocitaRotazione = 270.f;

    const float gravita = 1200.f;
    const float forzaSalto = -600.f;
    const float forzaJumpPad = -850.f;

    bool aTerra = true;
    bool morto = false;

    // Orologio per il deltaTime
    sf::Clock clock;

    // -------------------------
    // GAME LOOP
    // -------------------------

    while (window.isOpen())
    {
        // -------------------------
        // EVENTI
        // -------------------------

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            // Salto con Space
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Space && aTerra && !morto)
                {
                    velocitaY = forzaSalto;
                    aTerra = false;
                }

                // Restart con R
                if (keyPressed->scancode == sf::Keyboard::Scancode::R && morto)
                {
                        // Reset player
                        player.setPosition({175.f, 475.f});
                        velocitaY = 0.f;

                        angolo = 0.f;
                        player.setRotation(sf::degrees(0.f));

                        aTerra = true;
                        morto = false;

                        player.setFillColor(sf::Color::Green);

                        // Reset di TUTTI gli ostacoli
                        for (std::size_t i = 0; i < ostacoli.size(); i++)
                        {
                            ostacoli[i].setPosition({posizioniOstacoli[i],462.5f});
                        }
                        
                        for (std::size_t i = 0; i < piattaforme.size(); i++)
                        {
                            piattaforme[i].setPosition( posizioniPiattaforme[i]);
                        }

                        for (std::size_t i = 0; i < jumpPads.size(); i++)
                        {
                            jumpPads[i].setPosition(posizioniJumpPad[i]);
                        }
                }

            }
        }

        // -------------------------
        // DELTA TIME
        // -------------------------
        
        float deltaTime = clock.restart().asSeconds();

        // -------------------------
        // GRAVITA'
        // -------------------------

    if (!morto)
    {

        float yPrecedente = player.getPosition().y;

        velocitaY += gravita * deltaTime;
        player.move({0.f,velocitaY * deltaTime});

        aTerra = false;

        if (!aTerra)
        {
            angolo += velocitaRotazione * deltaTime;
            player.setRotation(sf::degrees(angolo));
        }


        // -------------------------
        // COLLISIONE COL TERRENO
        // -------------------------

        if (player.getPosition().y >= 475.f)
        {
            player.setPosition({player.getPosition().x, 475.f});
            velocitaY = 0.f;
            aTerra = true;
            angolo = 0.f;
            player.setRotation(sf::degrees(0.f));
        }



        // -------------------------
        // SCORRIMENTO OSTACOLO
        // -------------------------
     
        for (auto& ostacolo : ostacoli)
        {
            ostacolo.move({-velocitaLivello * deltaTime, 0.f});
        }

        for (auto& piattaforma : piattaforme)
        {
            piattaforma.move({-velocitaLivello * deltaTime, 0.f });
        }
        
        for (auto& jumpPad : jumpPads)
        {
            jumpPad.move({-velocitaLivello * deltaTime,0.f});
        }


        // -------------------------
        // COLLISIONE CON PIATTAFORME
        // -------------------------

        for (const auto& piattaforma : piattaforme)
        {
            auto bounds = piattaforma.getGlobalBounds();

            float cimaPiattaforma = bounds.position.y;

            float fondoPrecedente = yPrecedente + 25.f;
            float fondoAttuale = player.getPosition().y + 25.f;

            float sinistraPlayer = player.getPosition().x - 25.f;
            float destraPlayer = player.getPosition().x + 25.f;

            float sinistraPiattaforma = bounds.position.x;
            float destraPiattaforma =
                bounds.position.x + bounds.size.x;

            bool sovrappostoX =
                destraPlayer > sinistraPiattaforma &&
                sinistraPlayer < destraPiattaforma;

            if (velocitaY >= 0.f &&
                sovrappostoX &&
                fondoPrecedente <= cimaPiattaforma &&
                fondoAttuale >= cimaPiattaforma)
            {
                player.setPosition({
                    player.getPosition().x,
                    cimaPiattaforma - 25.f
                });

                velocitaY = 0.f;
                aTerra = true;

                angolo = 0.f;
                player.setRotation(sf::degrees(0.f));
            }
        }



        // -------------------------
        // COLLISIONE CON JUMP PAD
        // -------------------------

        for (const auto& jumpPad : jumpPads)
        {
            auto boundsPad = jumpPad.getGlobalBounds();

            // Piccola hitbox nella parte bassa del player
            sf::FloatRect piediPlayer(
                {
                    player.getPosition().x - 20.f,
                    player.getPosition().y + 15.f
                },
                {
                    40.f,
                    10.f
                }
            );

            if (piediPlayer.findIntersection(boundsPad))
            {
                velocitaY = forzaJumpPad;
                aTerra = false;
            }
        }



        // -------------------------
        // COLLISIONE CON OSTACOLI
        // -------------------------
        sf::FloatRect hitboxPlayer({ player.getPosition().x - 20.f,  player.getPosition().y - 20.f},{40.f, 40.f});

        for (const auto& ostacolo : ostacoli)
        {

            auto bounds = ostacolo.getGlobalBounds();
           
            sf::FloatRect hitboxSpike(
                {
                bounds.position.x + margineSpikeX,
                bounds.position.y + margineSpikeAlto
                },
                {
                bounds.size.x - 2.f * margineSpikeX,
                bounds.size.y - margineSpikeAlto
                }
            );


            if (hitboxPlayer.findIntersection(hitboxSpike))
            {
                morto = true;
                player.setFillColor(sf::Color::Blue);
        }
}



    }

        // -------------------------
        // DISEGNO
        // -------------------------

        window.clear(sf::Color::Black);

        window.draw(terreno);
        
        for (const auto& piattaforma : piattaforme)
        {
            window.draw(piattaforma);
        }


        for (const auto& jumpPad : jumpPads)
        {
            window.draw(jumpPad);
        }



        window.draw(player);



        for (const auto& ostacolo : ostacoli)
        {
            window.draw(ostacolo);

            // Prendiamo il rettangolo esterno del triangolo
            auto bounds = ostacolo.getGlobalBounds();

            sf::RectangleShape hitbox({bounds.size.x - 2.f * margineSpikeX, bounds.size.y - margineSpikeAlto });

            hitbox.setPosition({bounds.position.x + margineSpikeX, bounds.position.y + margineSpikeAlto});

            // Interno trasparente
            hitbox.setFillColor(sf::Color::Transparent);

            // Contorno visibile
            hitbox.setOutlineColor(sf::Color::Yellow);
            hitbox.setOutlineThickness(2.f);

            window.draw(hitbox);
        }



        window.display();
    }

    return 0;
}
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>

#include "Player.hpp"
#include "Spike.hpp"
#include "Piattaforma.hpp"
#include "JumpPad.hpp"
#include "Menu.hpp"

// -------------------------
// FUNZIONI PATTERN OSTACOLI 
// -------------------------

const float distanzaSpike = 50.f;

void patternSpike(std::vector<float>& posizioni, float x, int quantita)
{
    for (int i = 0; i < quantita; i++)
    {
        posizioni.push_back( x + distanzaSpike * i);
    }
}

enum class StatoGioco
{
    Menu,
    Gioco,
    Impostazioni
};


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


    
    StatoGioco stato = StatoGioco::Menu;
    Menu menu("Risorse/Font.ttf");
    

    // -------------------------
    // PLAYER
    // -------------------------
    Player player;



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
    std::vector<Piattaforma> piattaforme;

    for (const auto& posizione : posizioniPiattaforme)
    {
        piattaforme.emplace_back(
            posizione.x,
            posizione.y
        );
    }


    // -------------------------
    // JUMP PAD
    // -------------------------

    std::vector<sf::Vector2f> posizioniJumpPad = {{2900.f, 490.f}};
    std::vector<JumpPad> jumpPads;

    for (const auto& posizione : posizioniJumpPad)
    {
        jumpPads.emplace_back(posizione.x, posizione.y);
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
    std::vector<Spike> ostacoli;

    // Creiamo un triangolo per ogni posizione
    for (float x : posizioniOstacoli)
    {
        ostacoli.emplace_back(x);
    }

    
    // Velocita' di scorrimento del livello
    const float velocitaLivello = 250.f;
    const float forzaJumpPad = -850.f;


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
             if (stato == StatoGioco::Menu)
                {
                    // Freccia SU
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
                    {
                        menu.su();
                    }

                    // Freccia GIU'
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
                    {
                        menu.giu();
                    }

                    // INVIO
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)
                    {
                        if (menu.getSelezione() == 0)
                        {
                            stato = StatoGioco::Gioco;
                        }

                        if (menu.getSelezione() == 1)
                        {
                            stato = StatoGioco::Impostazioni;
                        }

                        if (menu.getSelezione() == 2)
                        {
                            window.close();
                        }
                    }
                }
                else if (stato == StatoGioco::Gioco)
                {
                    // Salto
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
                    {
                        player.salta();
                    }

                    // Restart
                    if (keyPressed->scancode == sf::Keyboard::Scancode::R &&
                        player.isMorto())
                    {
                        player.reset();

                        for (auto& ostacolo : ostacoli)
                        {
                            ostacolo.reset();
                        }

                        for (auto& piattaforma : piattaforme)
                        {
                            piattaforma.reset();
                        }

                        for (auto& jumpPad : jumpPads)
                        {
                            jumpPad.reset();
                        }
                    }

                    // ESC torna al menu
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    {
                        stato = StatoGioco::Menu;
                    }
                }
                else if (stato == StatoGioco::Impostazioni)
                {
                    // Per ora ESC torna al menu
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    {
                        stato = StatoGioco::Menu;
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

    if (stato == StatoGioco::Gioco && !player.isMorto())
    {

        float yPrecedente = player.getPosition().y;
        player.aggiorna(deltaTime);


        // -------------------------
        // COLLISIONE COL TERRENO
        // -------------------------

        if (player.getPosition().y >= 475.f)
        {
            player.atterra(475.f);
        }



        // -------------------------
        // SCORRIMENTO OSTACOLO
        // -------------------------
     
        for (auto& ostacolo : ostacoli)
        {
            ostacolo.aggiorna(deltaTime, velocitaLivello);
        }

        for (auto& piattaforma : piattaforme)
        {
            piattaforma.aggiorna(deltaTime,velocitaLivello);
        }
        
        for (auto& jumpPad : jumpPads)
        {
            jumpPad.aggiorna(deltaTime, velocitaLivello);
        }


        // -------------------------
        // COLLISIONE CON PIATTAFORME
        // -------------------------

        for (const auto& piattaforma : piattaforme)
        {
            auto bounds = piattaforma.getBounds();

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

            if (player.getVelocitaY() >= 0.f && sovrappostoX && fondoPrecedente <= cimaPiattaforma && fondoAttuale >= cimaPiattaforma)
            {
                player.atterra(cimaPiattaforma - 25.f);
            }
        }



        // -------------------------
        // COLLISIONE CON JUMP PAD
        // -------------------------

        for (const auto& jumpPad : jumpPads)
        {
            auto boundsPad = jumpPad.getBounds();

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
                player.jumpPad(forzaJumpPad);
            }
        }



        // -------------------------
        // COLLISIONE CON OSTACOLI
        // -------------------------
        sf::FloatRect hitboxPlayer = player.getHitbox();

        for (const auto& ostacolo : ostacoli)
        {
            if (hitboxPlayer.findIntersection(ostacolo.getHitbox()))
            {
                player.muori();
            }
        }



    }

        // -------------------------
        // DISEGNO
        // -------------------------

        window.clear(sf::Color::Black);

        if (stato == StatoGioco::Menu)
        {
            menu.disegna(window);
        }
        else if (stato == StatoGioco::Gioco)
        {
            window.draw(terreno);

            for (const auto& piattaforma : piattaforme)
            {
                piattaforma.disegna(window);
            }

            for (const auto& jumpPad : jumpPads)
            {
                jumpPad.disegna(window);
            }

            player.disegna(window);

            for (const auto& ostacolo : ostacoli)
            {
                ostacolo.disegna(window);
                ostacolo.disegnaHitbox(window);
            }
        }
        else if (stato == StatoGioco::Impostazioni)
        {
            // Per ora la schermata impostazioni la facciamo
            // nel prossimo mini-passaggio.
        }

        window.display();
    }

    return 0;
}
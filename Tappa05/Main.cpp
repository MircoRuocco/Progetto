#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include <iostream>

#include "WorldScene.hpp" 
#include "Menu.hpp"

// -------------------------
// FUNZIONI PATTERN OSTACOLI 
// -------------------------



const float distanzaSpike = 50.f;

void patternSpike(
    std::vector<sf::Vector2f>& posizioni,
    float x,
    float y,
    int quantita
)
{
    for (int i = 0; i < quantita; i++)
    {
        posizioni.push_back({
            x + distanzaSpike * i,
            y
        });
    }
}

enum class StatoGioco
{
    Menu,
    Gioco,
    Vittoria
};


int main()
{
    sf::Clock clock{};
    clock.start(); 
    float deltaTime = 0; 
    

    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Geometry Dash 2"
    );

    window.setFramerateLimit(60); 
    deltaTime = 1.f / 60.f; 

    
    StatoGioco stato = StatoGioco::Menu;
    Menu menu("Risorse/Font.ttf");
    

    WorldScene world{}; 


    sf::RectangleShape terreno({800.f, 100.f});
    terreno.setFillColor(sf::Color(100, 100, 100));
    terreno.setPosition({0.f, 500.f});


    
    // Piattaforme
    std::vector<sf::Vector2f> posizioniPiattaforme = {{1850.f, 400.f}, {2100.f, 275.f},{2200.f, 275.f}};
    for (const auto& posizione : posizioniPiattaforme)
    {
        world.spawnPlatform(posizione);
    }


  
    // Jump Pad 
    std::vector<sf::Vector2f> posizioniJumpPad = {{2900.f, 490.f}};
    for (const auto& posizione : posizioniJumpPad)
    {
        world.spawnJumpPad(posizione);
    }



    // Spikes 
 
    std::vector<sf::Vector2f> posizioniOstacoli; 
    patternSpike(posizioniOstacoli, 750.f,  462.5f, 1);
    patternSpike(posizioniOstacoli, 1100.f, 462.5f, 2);
    patternSpike(posizioniOstacoli, 1500.f, 462.5f, 3);
    patternSpike(posizioniOstacoli, 2100.f, 462.5f, 10);

    for (const auto& posizione : posizioniOstacoli)
    {
        world.spawnSpike(posizione);
    }


    // Traguardo
    world.spawnTraguardo({3400.f, 350.f});


    // -------------------------
    // GAME LOOP
    // -------------------------

    while (window.isOpen())
    {
        // -------------------------
        // EVENTI
        // -------------------------
        float frameStartTime = clock.getElapsedTime().asMilliseconds(); 

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }


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
                            window.close();
                        }
                    }
                }
                else if (stato == StatoGioco::Gioco)
                {

                    world.handleKeyPressed(keyPressed);

                    // ESC torna al menu
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    {
                        stato = StatoGioco::Menu;
                    }
                }
                else if (stato == StatoGioco::Vittoria)
                {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::M)
                    {
                        world.restart();
                        stato = StatoGioco::Menu;
                    }
                }

            }
        }


    if (stato == StatoGioco::Gioco)
    {
        world.update(deltaTime);

        if (world.livelloCompletato())
        {
            stato = StatoGioco::Vittoria;
        }

    }

  
        // Disegno

        window.clear(sf::Color::Black);

        if (stato == StatoGioco::Menu)
        {
            menu.disegna(window);
        }
        else if (stato == StatoGioco::Gioco)
        {
            window.draw(terreno);
            world.draw(window);
        }
        else if (stato == StatoGioco::Vittoria)
        {
            menu.disegnaVittoria(window);
        }

        window.display();


      
    }

    


    return 0;

}
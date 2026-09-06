#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.hpp"
#include "JumpPad.hpp"
#include "Spike.hpp"
#include "Piattaforma.hpp"
#include "Traguardo.hpp"


class WorldScene {
public:


    const float velocitaLivello = 250.f;


    void spawnJumpPad(sf::Vector2f position) {
        m_jumpPads.emplace_back(position.x, position.y);
    }

    void spawnPlatform(sf::Vector2f position) {
        m_platforms.emplace_back(position.x, position.y);

    }

    void spawnSpike(sf::Vector2f position) {
        m_spikes.emplace_back(position.x, position.y);
    }
    

    void spawnTraguardo(sf::Vector2f position)
    {
        m_traguardi.emplace_back(position.x, position.y);
    }   


    void handleKeyPressed(const sf::Event::KeyPressed* key)
    {
        if (key->scancode == sf::Keyboard::Scancode::Space)
        {
            m_player.salta();
        }

        if (key->scancode == sf::Keyboard::Scancode::R &&
            m_player.isMorto())
        {
            restart();
        }
    }

    bool livelloCompletato() const
    {
        for (const auto& traguardo : m_traguardi)
        {
            if (m_player.getHitbox().findIntersection(traguardo.getBounds()))
            {
                return true;
            }
        }

        return false;
    }

    void update(float deltaTime)
    {
         if (m_player.isMorto())
            return;


        // Aggiorna oggetti del livello
        for (auto& spike : m_spikes)
        {
            spike.aggiorna(deltaTime, velocitaLivello);
        }

        for (auto& piattaforma : m_platforms)
        {
            piattaforma.aggiorna(deltaTime, velocitaLivello);
        }

        for (auto& jumpPad : m_jumpPads)
        {
            jumpPad.aggiorna(deltaTime, velocitaLivello);
        }

        for (auto& traguardo : m_traguardi)
        {
            traguardo.aggiorna(deltaTime, velocitaLivello);
        }
        
        // Aggiorno il player + le collisioni 
        m_player.aggiorna(
            deltaTime,
            m_spikes,
            m_platforms,
            m_jumpPads
        );
    
    }



     void restart()
    {
        m_player.reset();

        for (auto& spike : m_spikes)
        {
            spike.reset();
        }

        for (auto& piattaforma : m_platforms)
        {
            piattaforma.reset();
        }

        for (auto& jumpPad : m_jumpPads)
        {
            jumpPad.reset();
        }
      
        for (auto& traguardo : m_traguardi)
        {
            traguardo.reset();
        }
    }

    void draw(sf::RenderWindow& window)
    {
        for (const auto& piattaforma : m_platforms)
        {
            piattaforma.disegna(window);
        }

        for (const auto& jumpPad : m_jumpPads)
        {
            jumpPad.disegna(window);
        }

        m_player.disegna(window);

        for (const auto& spike : m_spikes)
        {
            spike.disegna(window);
            spike.disegnaHitbox(window);
        }
        
        for (const auto& traguardo : m_traguardi)
        {
            traguardo.disegna(window);
        }
    }

private:
    std::vector<Spike> m_spikes {};
    std::vector<Piattaforma> m_platforms{};
    std::vector<JumpPad> m_jumpPads {};
    Player m_player {};
    std::vector<Traguardo> m_traguardi{};
};


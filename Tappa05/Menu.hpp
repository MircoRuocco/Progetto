#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>

class Menu
{
private:

    // Font usato da tutte le scritte
    sf::Font font;

    // Testi del menu
    sf::Text titolo;
    sf::Text gioca;
    sf::Text esci;
    sf::Text vittoria;
    sf::Text tornaMenu;
    
    // 0 = Gioca
    // 1 = Esci
    int selezione;

    // Aggiorna il colore della voce selezionata
    void aggiornaColori();

public:

    // Costruttore
    Menu(const std::filesystem::path& percorsoFont);

    // Sposta la selezione
    void su();
    void giu();

    // Restituisce la voce selezionata
    int getSelezione() const;

    // Disegna il menu
    void disegna(sf::RenderWindow& window) const;

    void disegnaVittoria(sf::RenderWindow& window) const;
};
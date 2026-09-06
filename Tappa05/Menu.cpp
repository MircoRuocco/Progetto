#include "Menu.hpp"


Menu::Menu(const std::filesystem::path& percorsoFont)
    : font(percorsoFont),
      titolo(font, "GEOMETRY DASH 2", 48),
      gioca(font, "GIOCA", 36),
      esci(font, "ESCI", 36),
      vittoria(font, "LIVELLO COMPLETATO!", 48),
      tornaMenu(font, "M - MENU PRINCIPALE", 28),
      selezione(0)
{
    // Posizioni delle scritte

    titolo.setPosition({180.f, 100.f});

    gioca.setPosition({320.f, 250.f});

    esci.setPosition({335.f, 340.f});
    
    vittoria.setPosition({140.f, 200.f});

    tornaMenu.setPosition({240.f, 300.f});

    aggiornaColori();
}



void Menu::su()
{
    selezione--;

    if (selezione < 0)
    {
        selezione = 1;
    }

    aggiornaColori();
}



void Menu::giu()
{
    selezione++;

    if (selezione > 1)
    {
        selezione = 0;
    }

    aggiornaColori();
}


void Menu::aggiornaColori()
{
    // Prima rimettiamo tutte le voci bianche

    gioca.setFillColor(sf::Color::White);
    esci.setFillColor(sf::Color::White);


    // Poi evidenziamo quella selezionata

    if (selezione == 0)
    {
        gioca.setFillColor(sf::Color::Yellow);
    }

    if (selezione == 1)
    {
        esci.setFillColor(sf::Color::Yellow);
    }
}



int Menu::getSelezione() const
{
    return selezione;
}


void Menu::disegna(sf::RenderWindow& window) const
{
    window.draw(titolo);

    window.draw(gioca);
    window.draw(esci);
}


void Menu::disegnaVittoria(sf::RenderWindow& window) const
{
    window.draw(vittoria);
    window.draw(tornaMenu);
}
# Geometry Dash 2

Progetto realizzato in C++ utilizzando SFML 3.0.0

## Precisazione
Nel CMakeLists.txt SFML viene individuata tramite il percorso relativo:

set(SFML_DIR
    "${CMAKE_SOURCE_DIR}/SFML-3.0.0-windows-vc16-64-bit/SFML-3.0.0/lib/cmake/SFML"
)

La cartella SFML deve quindi essere presente nella directory principale del progetto.
In alternativa, il percorso indicato in SFML_DIR deve essere modificato in modo da fare riferimento alla posizione in cui SFML 3.0.0 è installata sul computer

## Compilazione
Aprire un terminale nella cartella principale del progetto

fare: cmake -S . -B build
fare: cmake --build build 

## Comandi Input/Output  

Menu:
    Freccia SU / GIÙ: cambia selezione
    INVIO: conferma selezione

Gioco
    SPAZIO: salto del cubo
    R: ricomincia dopo la morte
    ESC: torna al menu

Modalità navicella
    SPAZIO tenuto: sale
    SPAZIO rilasciato: scende

Vittoria
    M: torna al menu principale
# Geometry Dash 2

Progetto realizzato in C++ utilizzando SFML 3.0.0

# Precisazione
CMake individua SFML tramite:
    find_package(SFML 3.0.0 REQUIRED COMPONENTS Graphics Window System)

SFML 3.0.0 deve quindi essere installata e configurata nel sistema in modo che CMake possa trovarla.

Se CMake non riesce a individuare automaticamente SFML, è possibile specificare la cartella contenente SFMLConfig.cmake durante la configurazione:
    cmake -S . -B build -DSFML_DIR="percorso-nella-quale-risiede-SFML/SFML-3.0.0/lib/cmake/SFML"



# Compilazione
Aprire un terminale nella cartella principale del progetto

configurazione: 
    fare: cmake -S . -B build

Compilazione:
    fare: cmake --build build 

# Avvio

Su Windows, con configurazione Debug:

powershell: 

.\build\Debug\Tappa01.exe
.\build\Debug\Tappa02.exe
.\build\Debug\Tappa03.exe
.\build\Debug\Tappa04.exe
.\build\Debug\Tappa05.exe
.\build\Debug\Tappa06.exe
.\build\Debug\Tappa07.exe
.\build\Debug\Tappa08.exe
.\build\Debug\Tappa09.exe
.\build\Debug\Tappa10.exe


# Comandi Input/Output  

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


cmake_minimum_required(VERSION 3.17)

project(MioGiocoSFML)

# Per adesso serve sul tuo PC per trovare SFML
set(SFML_DIR "C:/Users/Il mircone/Desktop/SFML-3.0.0-windows-vc16-64-bit/SFML-3.0.0/lib/cmake/SFML")

find_package(SFML 3.0.0 REQUIRED COMPONENTS Graphics Window System)



# TAPPA 01
add_executable(Tappa01
    Tappa01/Main.cpp
)

target_link_libraries(Tappa01 PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)


# TAPPA 02
add_executable(Tappa02
    Tappa02/Main.cpp
)

target_link_libraries(Tappa02 PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)


# TAPPA 03
add_executable(Tappa03
    Tappa03/Main.cpp
)

target_link_libraries(Tappa03 PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)


# TAPPA 04 - IN SVILUPPO
add_executable(Tappa04
    Tappa04/Main.cpp
    Tappa04/Player.cpp
    Tappa04/Spike.cpp
    Tappa04/Piattaforma.cpp
    Tappa04/JumpPad.cpp
    Tappa04/Menu.cpp
)
add_custom_command(TARGET Tappa04 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Risorse"
        "$<TARGET_FILE_DIR:Tappa04>/Risorse"
)

target_link_libraries(Tappa04 PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)
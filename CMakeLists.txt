cmake_minimum_required(VERSION 3.17)

project(MioGiocoSFML)

#set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML-3.0.0-windows-vc16-64-bit/SFML-3.0.0/lib/cmake/SFML")

find_package(SFML 3.0.0 REQUIRED COMPONENTS Graphics Window System)


# Trova automaticamente tutte le cartelle Tappa*
file(GLOB TAPPE
    LIST_DIRECTORIES true
    RELATIVE "${CMAKE_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/Tappa*"
)

list(SORT TAPPE)


# Crea un eseguibile per ogni tappa
foreach(TAPPA ${TAPPE})

    if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/${TAPPA}")

        file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
            "${CMAKE_SOURCE_DIR}/${TAPPA}/*.cpp"
            "${CMAKE_SOURCE_DIR}/${TAPPA}/*.hpp"
        )

        add_executable(${TAPPA} ${SOURCES})

        target_link_libraries(${TAPPA} PRIVATE
            SFML::Graphics
            SFML::Window
            SFML::System
        )

        add_custom_command(TARGET ${TAPPA} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_SOURCE_DIR}/Risorse"
                "$<TARGET_FILE_DIR:${TAPPA}>/Risorse"
        )

    endif()

endforeach()
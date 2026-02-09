cmake_minimum_required(VERSION 3.10)

# 1. Projektname
project(SpaceInvader)

# 2. C++ Standard festlegen
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. SFML PFAD ANPASSEN (Windows-spezifisch)
if(WIN32)
    # Dein Pfad für Windows
    set(SFML_DIR "C:/libs/SFML/lib/cmake/SFML")
    set(CMAKE_PREFIX_PATH ${SFML_DIR})
endif()

# 4. SFML Module suchen
# Auf Linux wird dies automatisch im System gefunden
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# 5. Alle .cpp Dateien im Verzeichnis finden
file(GLOB SOURCES "*.cpp")

# 6. Die EXE erstellen
add_executable(SpaceInvader ${SOURCES})

# 7. Header-Verzeichnisse (damit .h Dateien gefunden werden)
target_include_directories(SpaceInvader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# 8. SFML Bibliotheken verknüpfen
target_link_libraries(SpaceInvader sfml-graphics sfml-window sfml-system)

# 9. DLLs nach dem Build automatisch in den build-Ordner kopieren
if(WIN32)
    add_custom_command(TARGET SpaceInvader POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SFML_DIR}/../../../bin"
        $<TARGET_FILE_DIR:SpaceInvader>)
endif()
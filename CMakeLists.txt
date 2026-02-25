cmake_minimum_required(VERSION 3.10)
project(SpaceInvader)

# 1. C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. PFADE DEFINIEREN (SFML Ordner -> Unterordner)
# Wir nutzen CMAKE_CURRENT_SOURCE_DIR, damit es auf jedem PC funktioniert
set(SFML_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML")
set(SFML_INCLUDE_DIR "${SFML_BASE_DIR}/SFML_include")
set(SFML_LIB_DIR "${SFML_BASE_DIR}/SFML_lib")

# 3. Quellen finden
file(GLOB SOURCES "src/*.cpp")

# 4. EXE erstellen
add_executable(SpaceInvader ${SOURCES})

# 5. Header-Verzeichnisse (Hier liegen deine .hpp Dateien)
target_include_directories(SpaceInvader PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/SFML/SFML_include
    ${SFML_INCLUDE_DIR}
)

# 6. Bibliotheken verknüpfen
# Wir sagen CMake, wo die .a Dateien liegen
target_link_directories(SpaceInvader PRIVATE ${SFML_LIB_DIR})

# Wir verlinken die SFML-Komponenten
target_link_libraries(SpaceInvader 
    sfml-graphics 
    sfml-window 
    sfml-system 
    sfml-audio
)

# 7. DLLs und Assets kopieren (Damit die .exe beim Starten alles findet)
if(WIN32)
    # Kopiert den assets Ordner in den build-Ordner
    add_custom_command(TARGET SpaceInvader POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:SpaceInvader>/assets")
        
    # Kopiert alle DLLs aus deinem Hauptverzeichnis in den build-Ordner
    file(GLOB ALL_DLLS "${CMAKE_CURRENT_SOURCE_DIR}/*.dll")
    foreach(dll ${ALL_DLLS})
        add_custom_command(TARGET SpaceInvader POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${dll} $<TARGET_FILE_DIR:SpaceInvader>)
    endforeach()
endif()
#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include "Player.h"
#include "Shot.h"

class Game {

    public:
    void run();                                                                 //Baut das Spielfeld und zieht alle Updates rein
    void startStop();
    void init();
    void processInput();
    void update();
    void render();

    private:
    sf :: RenderWindow fenster{sf :: VideoMode(900, 900), "Space Invaders"};    //Erstellung Fenster in Groesse (x, y)
    Player player;
    std :: optional<Shot> playershot;       //???
};
#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include "Player.h"
#include "Shot.h"
#include "Alien.h"

class Game {

    public:
    void run();                                                                 //Baut das Spielfeld und zieht alle Updates rein

    private:
    sf :: RenderWindow fenster{sf :: VideoMode(900, 900), "Space Invaders"};    //Erstellung Fenster in Groesse (x, y)
    Player player;
    std :: optional<Shot> playershot;       //Im Player kann es einen Shot geben, muss es aber nicht...Daher spaetere Kontrollen
    
    std :: vector<Alien> aliens;
    void buildAliens();
};
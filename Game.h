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
    void buildAliens();                     //Methode zum Aufbau der Alienreihen

    float alienDirection = 1.f;             //Bewegungsrichtung pro Frame (+2 nach rechts / -2 nach links)
    float alienSpeed = 50.f;                //Bewegungsgeschwindigkeit (px pro Sekunde)
    float alienDrop = 30.f;                 //Alien bewegung nach unten (y muss groesser werden)

    private:
    void updateAliens(float dt);            //Updated die Position der Aliens
};
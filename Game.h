#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include <string>
#include "Player.h"
#include "Shot.h"
#include "Alien.h"

class Game {

    public:
    void run();                             //Baut das Spielfeld und zieht alle Updates rein bzw ruft alle Build Funktionen auf
    float alienDirection = 1.f;             //Bewegungsrichtung pro Frame (+2 nach rechts / -2 nach links)
    float alienSpeed = 50.f;                //Bewegungsgeschwindigkeit (px pro Sekunde)
    float alienDrop = 30.f;                 //Alien bewegung nach unten (y muss groesser werden)

    private:
    sf :: RenderWindow fenster{sf :: VideoMode(900, 900), "Space Invaders"};    //Erstellung Fenster in Groesse (x, y)
    Player player;
    std :: optional<Shot> playershot;       //Im Player kann es einen Shot geben, muss es aber nicht...Daher spaetere Kontrollen
    
    std :: vector<Alien> aliens;
    void buildAliens();                     //Methode zum Aufbau der Alienreihen

    void updateAliens(float dt);            //Updated die Position der Aliens

    //Display - Score + Text
    int score = 0;                          //Aktueller Punktestand
    const int scorePointsAlien = 20;        //Punkte pro Treffer
    void updateDisplay();                   //Aktualisierung des Angezeigten Punktestands
    void initDisplay();                     //Definieren der Texteigenschaften
    sf :: Font font;                        //Textart anlegen
    sf :: Text gameName;                    //Textfeld fuer Titel definieren
    sf :: Text scoreBoard;                  //Textfeld fuer Punktestand definieren
    sf :: Text playerLives;                 ////Textfeld fuer Leben definieren
};
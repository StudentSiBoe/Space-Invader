#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include <string>
#include <random>
#include <cstdlib>
#include <iostream>
#include "Player.h"
#include "Shot.h"
#include "Alien.h"
#include "AlienShot.h"

class Game {

    public:
    void run();                             //Baut das Spielfeld und zieht alle Updates rein bzw ruft alle Build Funktionen auf
    float alienDirection = 1.f;             //Bewegungsrichtung pro Frame (+2 nach rechts / -2 nach links)
    float alienSpeed = 77.f;                //Bewegungsgeschwindigkeit (px pro Sekunde)
    float alienDrop = 30.f;                 //Alien bewegung nach unten (y muss groesser werden)

    private:
    sf :: RenderWindow fenster{sf :: VideoMode(900, 900), "Space Invaders"};    //Erstellung Fenster in Groesse (x, y)
    Player player;
    std :: vector<Alien> aliens;
    std :: optional<Shot> playershot;       //Im Player kann es einen Shot geben, muss es aber nicht...Daher spaetere Kontrollen
    std :: optional<AlienShot> alienShot;   //Es gibt vielleicht einen Alien Schuss muss es aber nicht... Wie playershot

    void buildAliens();                     //Methode zum Aufbau der Alienreihen
    void updateAliens(float dt);            //Updated die Position der Aliens

    void tryAlienShoot(float dt);           //Alien Schuss Berechnung und Freigaben zum schiessen testen
    float alienShootTimer = 0.f;            //vergangene Zeit nach jedem Schuss 
    float alienShootInterval = 1.2f;        //Alien Schuss Intervall (alle ... Sekunden schiessen)

    //Trefferanzeige - Spieler 
    bool hitPause = false;
    float hitPauseTimer = 0.f;
    const float hitPauseFreeze = 2.5f;

    bool invincible = false;
    float invincibleTimer = 0.f;
    const float invincibleFreeze = 2.5f;

    float blinkTimer = 0.f;
    const float blinkInterval = 0.15f;
    bool blinkOn = false;

    //Display - Score + Text
    int score = 0;                          //Aktueller Punktestand
    int playerLivesAmount = 3;              //Anzahl Leben fuer Spieler
    bool gameOverStatus = false;            //Status Gameover
    const int scorePointsAlien = 20;        //Punkte pro Treffer
    void updateDisplay();                   //Aktualisierung des Angezeigten Punktestands
    void initDisplay();                     //Definieren der Texteigenschaften
    sf :: Font font;                        //Textart anlegen
    sf :: Text gameName;                    //Textfeld fuer Titel definieren
    sf :: Text scoreBoard;                  //Textfeld fuer Punktestand definieren
    sf :: Text playerLives;                 //Textfeld fuer Leben definieren
    sf :: Text gameOverText;                //Textfeld bei Gameover
};
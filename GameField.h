#pragma once                                //Schutz fuer den Header gegen doppelte Definition/doppelte Einbindung
#include <SFML/Graphics.hpp>

class GameField{
    public:
    void buildWindow();
    void updateAliens();
    void updateShot();
    void handlePlayer();

    private:
    sf :: RenderWindow fenster{sf :: VideoMode(900, 900), "Space Invaders"};
};
#pragma once                                //Schutz fuer den Header gegen doppelte Definition/doppelte Einbindung
#include <SFML/Graphics.hpp>

// Gamefield rendert und updatet das Spielfeld, Das Feld soll in der Game loop erzeugt werden, um das ganze uebersichtlich zu halten

class GameField{

    public:
    //void buildWindow();
    void updateAliens();
    void updateShot();
    void handlePlayer();

    private:
    
};
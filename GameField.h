#pragma once                                //Schutz fuer den Header gegen doppelte Definition/doppelte Einbindung
#include <SFML/Graphics.hpp>
/**/
// Gamefield rendert und updatet das Spielfeld, Das Feld soll in der Game loop erzeugt werden, um das ganze uebersichtlich zu halten

class GameField{

    public:
    //sf :: RenderWindow fenster{sf :: VideoMode(900, 900), "Space Invaders"};    //Erstellung Fenster in Groesse (x, y)
    GameField(sf :: RenderWindow fenster);
    //void buildWindow();
    void initDisplay();
    void updateDisplay();
    void restartGame();

    private:
    int score = 0;                          //Aktueller Punktestand
    int playerLivesAmount = 3;              //Anzahl Leben fuer Spieler
    bool gameOverStatus = false;            //Status Gameover

    bool hitPause = false;                  //Variable bei getroffen werden            
    float hitPauseTimer = 0.f;              //gestoppte Zeit als Timer
    const float hitPauseStop = 2.5f;        //Pausezeit bei Treffer

    bool invincible = false;                //Variable zum unverwundbar werden
    float invincibleTimer = 0.f;            //gestoppte Zeit fuer Unverwundbarkeit
    const float invincibleStop = 2.5f;      //Unverwundbarkeitszeitraum bei Treffer

    float blinkTimer = 0.f;                 //getoppte Zeit zwischen Farbwechseln
    const float blinkInterval = 0.15f;      //Zeit bis Farbwechsel
    bool blinkOn = false;                   //Variable zum einschalten des blinkens
    
    sf :: Font font;                        //Textart anlegen
    sf :: Text gameName;                    //Textfeld fuer Titel definieren
    sf :: Text scoreBoard;                  //Textfeld fuer Punktestand definieren
    sf :: Text playerLives;                 //Textfeld fuer Leben definieren
    sf :: Text gameOverText;                //Textfeld bei Gameover
    sf :: Text miniIntroduction;
    sf :: Text gameOverAddOn;
};


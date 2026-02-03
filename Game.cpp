#include "Game.h"
/*
int main (int argc, char ** argv) {
    
    Game game;
    game.run();
    return 0;

}
void Game::run(){
    init();
    while(true){
        processInput();         // Eingaben einlesen
        update();               // staendige Aktualisierung
        render();               // Ausgabe auf das Spielfeld-Fenster
    }
}
    NUR ZUM TEST AUSKOMMENTIERT    
*/

void Game :: run () {

    sf :: Clock clock;
    
    fenster.setFramerateLimit(60);                                                  //FPS einstellen

    while (fenster.isOpen()) {
        sf :: Event event;                                                          //Variable event zum abfangen von befehlen

        while (fenster.pollEvent(event)) {                                          //Holt alle Infos aus Event
            if (event.type == sf :: Event :: Closed)                                //Bei Anwahl X Fenster schliessen
                fenster.close();
        }

    
    // Oeffnet Fenster in Groesse x, y... Bleibt offen bis Befehl - Schliessen kommt, dann clear und löscht das fenster
    
    float dt = clock.restart().asSeconds();                                         //SFML Stoppuhr - Gibt die Zeit seid dem letztem Restart zurück und wandelt das in Sekunden um

    //Eingaben vom Player
    player.handleInput();                                                           //Bewegungssteuerung Spieler

    //Player aktualisieren
    player.update(dt, static_cast<float>(fenster.getSize().x));                     //deltaTime und Breite des Feldes uebergeben an Positionspruefung 

    fenster.clear();
    player.render(fenster);
    fenster.display();

    }
}

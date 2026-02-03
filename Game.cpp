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
    
    float dt = clock.restart().asSeconds();
    //SFML Stoppuhr - clock.restart(), Gibt die Zeit seid dem letztem Restart zurück und .asSeconds() wandelt die Zeit in Sekunden um                                         
    //Spiel laeuft mit vorgegebenen 60 fps -> dt (Zeit zwischen e Frames) = ca. 0,02sec -> dt = 0,02s
    //Im Player: spieler.move(direction * speed * dt, 0.f); == Bewegung des Players in einem Frame

    //Eingaben vom Player
    player.handleInput();                                                           //Bewegungssteuerung Spieler

    //Player aktualisieren
    player.update(dt, static_cast<float>(fenster.getSize().x));                     //deltaTime und Breite des Feldes uebergeben an Positionspruefung 

    fenster.clear();
    player.render(fenster);
    fenster.display();

    }
}

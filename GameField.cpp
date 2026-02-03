# include "GameField.h"

void GameField :: buildWindow () {

    // sf :: RenderWindow fenster(sf :: VideoMode(900, 900), "Space Invaders");        //Fenstergroesse einstellen
    fenster.setFramerateLimit(60);                                                  //FPS einstellen

    while (fenster.isOpen()) {
        sf :: Event event;                                                          //Variable event zum abfangen von befehlen

        while (fenster.pollEvent(event)) {                                          //Holt alle Infos aus Event
            if (event.type == sf :: Event :: Closed)                                //Bei Anwahl X Fenster schliessen
                fenster.close();
        }
        fenster.clear();
        fenster.display();

    }
    // Oeffnet Fenster in Groesse x, y... Bleibt offen bis Befehl - Schliessen kommt, dann clear und löscht das fenster
  
}
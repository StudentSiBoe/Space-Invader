#include "Game.h"

void Game :: run () {

    sf :: Clock clock;
    
    fenster.setFramerateLimit(60);                                                  //FPS einstellen

    while (fenster.isOpen()) {
        sf :: Event event;                                                          //Variable event zum abfangen von befehlen

        while (fenster.pollEvent(event)) {                                          //Holt alle Infos aus Event
            if (event.type == sf :: Event :: Closed)                                //Bei Anwahl X Fenster schliessen
                fenster.close();
        }

    
    // Oeffnet Fenster, Bleibt offen bis Befehl - Schliessen kommt, dann clear und löschen
    
    float dt = clock.restart().asSeconds();
    //SFML Stoppuhr - clock.restart(), Gibt die Zeit seid dem letztem Restart zurück und .asSeconds() wandelt die Zeit in Sekunden um                                         
    //Spiel laeuft mit vorgegebenen 60 fps -> dt (Zeit zwischen e Frames) = ca. 0,02sec -> dt = 0,02s
    //Im Player: spieler.move(direction * speed * dt, 0.f); == Bewegung des Players in einem Frame

    //Eingaben vom Player
    player.handleInput();                                                           //Bewegungssteuerung Spieler
    
    //Schuss erzeugen bei Tastendruck --------------- ??
    if (player.shotRequest()) {
        if(!playershot.has_value() || !playershot->isActive()) {
            sf :: Vector2f pos = player.shotStartPosition();
            playershot = Shot(pos.x, pos.y);
        }
        player.processShotRequest();
    }

    player.update(dt, static_cast<float>(fenster.getSize().x));                     //deltaTime und Breite des Feldes uebergeben an Positionspruefung 


    if (playershot.has_value() && playershot->isActive()) {
        playershot->update(dt);
        if (playershot->upperLimit() < 0.f) {
            playershot->deactivate();
        }
    }

    fenster.clear();
    player.render(fenster);

    if (playershot.has_value()) {
        playershot->render(fenster);
    }

    fenster.display();

    }
}

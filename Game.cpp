#include "Game.h"
#include <iostream>

void Game :: buildAliens() {                                                        //Aufbau der Alien Reihen
    aliens.clear();                                                                 //Erstmal aufräumen

    const int rows = 4;                                                             //Anzahl Reihen nach unten (y)
    const int cols = 12;                                                            //Anzahl Spalten nach rechts (x)

    const float startX = 100.f;                                                     //Start X Koordinate erstes Alien
    const float startY = 150.f;                                                     //Start Y Koordinate erstes Alien

    const float gapX = 60.f;                                                        //Abstand X zwischen zwei Aliens
    const float gapY = 60.f;                                                        //Abstand Y zwischen zwei Aliens

    for (int i = 0; i < rows; i++) {                                                //Schleife - Reihen durchlaufen 
        for (int j = 0; j < cols; j++) {                                            //Schleife - Spalten durchgehen 
            float x = startX + j * gapX;                                            //X - Position fuer Alien Plazierung
            float y = startY + i * gapY;                                            //Y - Position fuer Alien Plazierung
            aliens.emplace_back(x, y);                                              //Positionen (x,y) weitergeben
        }
    }
}

void Game :: updateAliens(float dt) {                                               //Positions Aktualisierung der Aliens
    float moveX = alienDirection * alienSpeed * dt;                                 //Bewegung in X-Richtung (Bestehend aus Richtung, Geschwindigkeit und delta Time)
    bool border = false;                                                            //Grenze des Fensters anlegen (Bewegungsradius)

    for (const Alien& a : aliens) {
        if (alienDirection > 0 && a.right() >= fenster.getSize().x) {               //Alienbewegung nach rechts (Direction +) UND rechte Kante des Aliens ist an / ueber der Fenstergroesse (rechte Kante)
            border = true;                                                          //DANN setze die Grenze 
        }
        if (alienDirection < 0 && a.left() <= 0.f) {                                //Alienbewegung nach links (Direction -) UND linke Kante des Aliens ist an /ueber dem beginn des Fensters (linke Kante) 
            border = true;                                                          //DANN setze die Grenze
        }                                  
    }

    if (border) {                                                                   //Wenn die Grenze erreicht ist
        for (Alien& a : aliens) {                                                   //Jedes Alien soll:
            a.move(0.f, alienDrop);                                                 //Nach unten (Y) um den vorgegebenen Wert alienDrop bewegt werden
        }
        alienDirection *= -1.f;                                                     //Danach wird die Bewegungsrichtung umgedreht
    } else {                                                                        //Solange keine Grenze erreicht ist
        for (Alien& a : aliens) {                                                   //Soll sich jedes Alien
            a.move(moveX, 0.f);                                                     //Um die errechnete Bewegungseinheit auf X bewegen
        }
    }
}
//-----------------------------------
//------------HERZ-STUECK------------
//-----------------------------------
void Game :: run () {

    sf :: Clock clock;
    
    fenster.setFramerateLimit(60);                                                  //FPS einstellen

    buildAliens();                                                                  //Aufruf - Bau Alien-Reihen

    while (fenster.isOpen()) {
        sf :: Event event;                                                          //Variable event zum abfangen von befehlen

        while (fenster.pollEvent(event)) {                                          //Holt alle Infos aus Event
            if (event.type == sf :: Event :: Closed)                                //Bei Anwahl X Fenster schliessen
                fenster.close();
        }

    
    // Oeffnet Fenster, Bleibt offen bis Befehl - Schliessen kommt(oben rechts X), dann clear und löschen
    
    float dt = clock.restart().asSeconds();                                         //dt berechnen 
    //SFML Stoppuhr - clock.restart(), Gibt die Zeit seid dem letztem Restart zurück und .asSeconds() wandelt die Zeit in Sekunden um                                         
    //Spiel laeuft mit vorgegebenen 60 fps -> dt (Zeit zwischen e Frames) = ca. 0,02sec -> dt = 0,02s
    //Im Player: spieler.move(direction * speed * dt, 0.f); == Bewegung des Players in einem Frame

    //Eingaben vom Player bzw. Bewegungssteuerung
    player.handleInput();                                                           
    
    //Schuss Abfrage (es kann nur einen Schuss geben)
    if (player.shotRequest()) {                                                     //Wenn Space-Taste gedrueckt, shotRequest gibt true zurueck
        if(!playershot.has_value() || !playershot->isActive()) {                    //Wenn kein Schuss existiert (has_value) ODER kein Schuss aktiviert (noch fliegt/isActive) ist
            sf :: Vector2f pos = player.shotStartPosition();                        //Neue Start-Pos fuer neuen Schuss ermitteln
            playershot = Shot(pos.x, pos.y);                                        //Neuen Shot dort erzeugen...
        }
        player.processShotRequest();                                                //Nach dem Schuss wird der Schussaufruf wieder auf false gesetzt
    }

    player.update(dt, static_cast<float>(fenster.getSize().x));                     //deltaTime und Breite des Feldes uebergeben an Positionspruefung 
    updateAliens(dt);                                                               //Aufruf Alien update Methode mit delta Time

    if (playershot.has_value() && playershot->isActive()) {                         //Schuss existiert und ist aktiv
        playershot->update(dt);                                                     //Updated die Position des Schusses pro Frame
        
        for (int i = 0; i < aliens.size(); i++) {                                   //solange i kleiner wie Anzahl der existierenden Aliens ist
            if (playershot->hitbox().intersects(aliens[i].hitbox())) {              //Pruefe mit intersects(SFLM-Fkt zum testen, schneiden sich zwei Rechtecke), indem Fall schneidet sich die Hitbox des Schusses mit einem Alien[i]
                aliens.erase(aliens.begin() + i);                                   //Treffer -> ALSO: loesche das Alien bei [i], begin()...Art Zeiger auf erstes Element, darum begin() + i, um aktuelles Alien zu loeschen
                playershot->deactivate();                                           //Schuss deaktivieren
                break;                                                              //Schleife verlassen, weil durch erase ein Element fehlt...Dadurch ist alien.size() um eins kleiner und es muss erneut von vorn kontrolliert werden
            }
        }

        if (playershot->upperLimit() < 120.f) {                                     //Wenn Schuss ist hinter festgelegter Grenze, deaktivieren
            playershot->deactivate();                                               //Schaltet den Schuss aus 
        }

        if (aliens.empty()) {                                                       //Wenn keine Aliens mehr in dem Fenster sind
            buildAliens();                                                          //DANN erstelle erneut eine Formation
        }
    }

    fenster.clear();
    player.render(fenster);                                                         //Player im Fenster zeichen

    for (const Alien& a : aliens) {                                                 //a ist die Referenz (&) auf ein Alien, welches nicht veraendert werden darf (const)
        a.render(fenster);                                                          //a : aliens -> a bekommt nacheinander jedes Element aus aliens (Was eine Referenz von Alien ist und keine Kopie!)
    }                                                                               //Diese Referenz a in das fenster zeichnen

    if (playershot.has_value()) {                                                   //Wenn gerade einen Shot existiert, DANN
        playershot->render(fenster);                                                //Zeichne den Schuss in das Fenster
    }                                                                               //Hier keine isActive Abfrage, weil render Active bereits kontrolliert

    fenster.display();                                                              //SFML Fenster auf dem Screen anzeigen

    }
}






/*
    OPTIONALE ANPASSUNG fuer Event Schleife, damit Space-Taste nicht gehalten werden kann (isKeypressed -> Keypressed)
    while (fenster.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
        fenster.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            // EINMALIG pro Druck
            shotRequested = true;
        }
    }
*/

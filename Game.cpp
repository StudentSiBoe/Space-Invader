#include "Game.h"
#include <iostream>
#include <string>

//Highscore Boe: 4180
//Highscore Simon: 2180

void Game :: buildAliens() {                                                        //Aufbau der Alien Reihen
    aliens.clear();                                                                 //Erstmal aufräumen

    const int rows = 5;                                                             //Anzahl Reihen nach unten (y)
    const int cols = 11;                                                            //Anzahl Spalten nach rechts (x)

    const float startX = 120.f;                                                     //Start X Koordinate erstes Alien
    const float startY = 140.f;                                                     //Start Y Koordinate erstes Alien

    const float gapX = 65.f;                                                        //Abstand X zwischen zwei Aliens
    const float gapY = 65.f;                                                        //Abstand Y zwischen zwei Aliens

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
    bool border = false;                                                            //Grenze des Fensters anlegen (Bewegungsgrenze)

    for (const Alien& a : aliens) {
        if (alienDirection > 0 && a.right() >= static_cast<float>(fenster.getSize().x)) {               //Alienbewegung nach rechts (Direction +) UND rechte Kante des Aliens ist an / ueber der Fenstergroesse (rechte Kante)
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

void Game :: initDisplay() {                                                        //Definieren der Texteigenschaften - Display
    font.loadFromFile("assets/fonts/zephyrean-brk.ttf");                            //Textart laden

    gameName.setFont(font);                                                         //Textart zuweisen
    gameName.setCharacterSize(95);                                                  //Textgroesse definieren
    gameName.setString("SPACE INVADERS");                                           //Text definieren
    gameName.setFillColor(sf :: Color :: Green);                                    //Textfarbe definieren

    scoreBoard.setFont(font);                                                       //Textart zuweisen
    scoreBoard.setCharacterSize(45);                                                //Textgroesse definieren
    scoreBoard.setFillColor(sf :: Color :: Yellow);                                 //Textfarbe definieren

    playerLives.setFont(font);                                                      //Textart zuweisen
    playerLives.setCharacterSize(45);                                               //Textgroesse definieren
    
    playerLives.setFillColor(sf :: Color :: Yellow);                                //Textfarbe definieren

    gameOverText.setFont(font);                                                     //Textart zuweisen                             
    gameOverText.setCharacterSize(180);                                             //Textgroesse definieren       
    gameOverText.setString("GAME OVER");                                            //Text definieren
    gameOverText.setFillColor(sf :: Color :: Red);                                  //Textfarbe definieren

    updateDisplay();                                                                //Aufruf der Text-Update Methode fuer Score Aenderung
}

void Game :: updateDisplay() {                                                      //Aktualiert staendig den Score 
    scoreBoard.setString("SCORE: " + std :: to_string(score));                      //Textausgabe im SFML, darum muss der Int Score in einen String gewandelt werden...
    scoreBoard.setPosition(10.f, 10.f);                                             //Position fuer Score definieren (x,y)

    playerLives.setString("LIVES: " + std :: to_string(playerLivesAmount));         //Playerleben mit der int Variable anzeigen

    float fensterBreite = static_cast<float>(fenster.getSize().x);                  //Breite des gesamten Fensters (Size in pixel bzw int darum in float umwandeln)
    float fensterHoehe = static_cast<float>(fenster.getSize().y);

    auto titel = gameName.getLocalBounds();                                         //Mase des Text-Rechtecks title
    gameName.setPosition((fensterBreite - titel.width) / 2.f - titel.left, 5.f);    //Position fuer Game Titel (x,y), Mathematisch berechnen - Offset (Textfeld Versatz links)

    auto lP = playerLives.getLocalBounds();                                         //Mase des Text-Rechtecks player
    playerLives.setPosition(fensterBreite - lP.width - 10.f - lP.left, 10.f);       //10.f = Abstand zum Rand (fuer die Optik)

    auto gOver = gameOverText.getLocalBounds();                                    //Mase des Text-Rechtecks gameOver
    gameOverText.setPosition((fensterBreite - gOver.width) / 2.f - gOver.left, (fensterHoehe - gOver.height) / 2.f - gOver.top);    //Position fuer GameOver Textfeld mittig auf Fenster anzeigen
}

void Game :: tryAlienShoot(float dt) {
    alienShootTimer += dt;                                                          //Timer erhoehen in jedem Frame

    if (aliens.empty()                                                              //Wenn es keine Aliens mehr auf dem Feld gibt 
    || alienShootTimer < alienShootInterval                                         //ODER Zeit bis naechster Schuss noch nicht erreicht
    || (alienShot.has_value() && alienShot->isActive())) return;                    //ODER ein AlienSchuss existiert und fliegt noch -> DANN return

    int randomNum = rand() % aliens.size();                                         //Random Alien (Zahl) aus zufallsfolge ermitteln, mit hilfe vom aktuelle Seed

    sf :: FloatRect alienHitbox = aliens[randomNum].hitbox();                       //Hitbox des Random-ausgewaehlten Aliens ermitteln
    
    float x = alienHitbox.left + alienHitbox.width / 2.f - 5.f;                     //Mitte der Alien-Hitbox - halber Schuss fuer Abfeuerkoordinate X
    float y = alienHitbox.top + alienHitbox.height;                                 //untere Alienkante der Alien-Hitbox fuer Abfeuerkoordinate Y

    alienShot = AlienShot(x, y);                                                    //Abschuss-Positions Koordinaten uebergeben
    
    alienShootTimer = 0.f;                                                          //Wenn Zeit fuer neuer Schuss erreicht UND neuer Schuss wird erzeugt -> Reset Timer
    
    alienShootInterval = 0.9f + static_cast<float>(rand()) / RAND_MAX * 1.2f;       //Die Zufallszahl wird mit rand() von 0 bis RAND_MAX erzeugt... Normieren durch / -> 0..1 + &* -> 0,9 bis 2.1
                                                                                    //Schuss ist nicht vorhersehbar, macht Spiel schwerer (kein Muster)
}
//-----------------------------------
//------------HERZ-STUECK------------
//-----------------------------------
void Game :: run () {
    srand(static_cast<unsigned int>(time(nullptr)));                                //Start der Zufallsfolge setzen (seed) fuer rand(), time gibt aktuelle Zeit (time) -> cast in int (fuer srand)                        

    sf :: Clock clock;
    
    fenster.setFramerateLimit(60);                                                  //FPS einstellen

    initDisplay();

    buildAliens();                                                                  //Aufruf - Bau Alien-Reihen

    while (fenster.isOpen()) {                                                      //Feedback vom fenster (es existiert)
        sf :: Event event;                                                          //Variable event zum abfangen von befehlen
                                                                                    
        while (fenster.pollEvent(event)) {                                          //Holt das naechste Event aus Warteschlange und schreibt es in event
            if (event.type == sf :: Event :: Closed) {                              //Bei Anwahl x Fenster schliessen
                fenster.close();
            }
        }
    
        float dt = clock.restart().asSeconds();                                     //dt berechnen 
        //SFML Stoppuhr - clock.restart(), Gibt die Zeit seid dem letztem Restart zurück und .asSeconds() wandelt die Zeit in Sekunden um                                         
        //Spiel laeuft mit vorgegebenen 60 fps -> dt (Zeit zwischen e Frames) = ca. 0,02sec -> dt = 0,02s
        //Im Player: spieler.move(direction * speed * dt, 0.f); == Bewegung des Players in einem Frame

        if (hitPause) {                                                             //Trefferpause ist aktiv, dann
            hitPauseTimer += dt;                                                    //Stoppt alles und zählt die Zeit zwischen den Frames hoch, bis:
            if (hitPauseTimer >= hitPauseStop) {                                    //Timer Zeit = vorgegebenen Stoppzeit
                hitPause = false;                                                   //Pause aufloesen
            } 
        }

        if (!gameOverStatus && !hitPause) {                                                 //Spiel laeuft, wenn kein Gameover oder Treffer am Spieler
            
            player.handleInput();                                                           //Eingaben vom Player bzw. Bewegungssteuerung                                                           
    
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

            tryAlienShoot(dt);

            if (playershot.has_value() && playershot->isActive()) {                     //Player - Schuss existiert und ist aktiv
                playershot->update(dt);                                                     //Updated die Position des Schusses pro Frame
        
                for (int i = 0; i < aliens.size(); i++) {                                   //solange i kleiner wie Anzahl der existierenden Aliens ist
                    if (playershot->hitbox().intersects(aliens[i].hitbox())) {              //Pruefe mit intersects(SFLM-Fkt zum testen, schneiden sich zwei Rechtecke), indem Fall schneidet sich die Hitbox des Schusses mit einem Alien[i]
                        aliens.erase(aliens.begin() + i);                                   //Treffer -> ALSO: loesche das Alien bei [i], begin()...Art Zeiger auf erstes Element, darum begin() + i, um aktuelles Alien zu loeschen
                        playershot->deactivate();                                           //Schuss deaktivieren
                        score += scorePointsAlien;
                        updateDisplay();
                        break;                                                              //Schleife verlassen, weil durch erase ein Element fehlt...Dadurch ist alien.size() um eins kleiner und es muss erneut von vorn kontrolliert werden
                    }
                }

                if (playershot->upperLimit() < 120.f) {                                 //Wenn Schuss ist hinter festgelegter Grenze, deaktivieren
                    playershot->deactivate();                                               //Schaltet den Schuss aus 
                }            

                if (aliens.empty()) {                                                   //Wenn keine Aliens mehr in dem Fenster sind
                    buildAliens();                                                          //DANN erstelle erneut eine Formation
                }
            }    
        }   
    
        if (alienShot.has_value() && alienShot->isActive()) {      
            alienShot->update(dt);

            if (alienShot->lowerLimit() > static_cast<float>(fenster.getSize().y)) {    //Schuss verlässt Spielfeld / ueber Fenstergroesse hinaus
                alienShot->deactivate();

            } else if (alienShot->hitbox().intersects(player.hitbox())) {           //Treffer am Spieler registriert
                alienShot->deactivate();
                playerLivesAmount -= 1;                                                 //Spielerleben um 1 verringern
                updateDisplay();                                                        //Display / Lebensanzeige aktualisieren

                if (playerLivesAmount <= 0) {                                           //Check ob Spieler noch Leben hat
                    gameOverStatus = true;                                              //Wenn nicht -> Gameover
                    invincible = true;                                                  //Unverwundbarkeitsphase an
                    invincibleTimer = 0.f;                                              //Unverwundbarkeitszeit startet

                    blinkTimer = 0.f;                                                   //Blink Zeit startet
                    blinkOn = true;                                                     //blinken an
                    player.setHitVisual(blinkOn);                                       //Methode zum blinken aufrufen mit true
                    
                } else {                                                            //TREFFER Anzeige
                    hitPause = true;                                                    //ANSONSTEN Stopp/stehen an (Player bleibt stehen)
                    hitPauseTimer = 0.f;                                                //Start Standzeit

                    invincible = true;                                                  //Unverwundbarkeitsphase an
                    invincibleTimer = 0.f;                                              //Unverwundbarkeitszeit startet

                    blinkTimer = 0.f;                                                   //Blink Zeit startet
                    blinkOn = true;                                                     //blinken an
                    player.setHitVisual(blinkOn);                                       //Methode zum blinken aufrufen mit true
                }
            }
        }

        for (const Alien& a : aliens) {                                             //Kontrolle, erreicht ein Alien (alle Aliens) den Spieler
            float loseLineY = player.spielerPosY;                                       //Linie auf Hoehe des Spielers um Gameover zu ermitteln
            if (a.bottom() >= loseLineY) {
                gameOverStatus = true;                                                  //Alien erreicht Spielerhoehe -> Gameover
                break;
            }
        }
        
        if (invincible) {                                                               //Wenn unverwundbar, dann
            invincibleTimer += dt;                                                      //Timer hochzaehlen fuer unverwundbar sein
            blinkTimer += dt;                                                           //Timer hochzaehlen fuer blinken

            if (blinkTimer >= blinkInterval) {                                          //Wenn Zei zum blinken/Farbwechsel erreicht
                blinkTimer = 0.f;                                                       //Timer zuruecksetzen
                blinkOn = !blinkOn;                                                     //Blink-Status negieren
                player.setHitVisual(blinkOn);                                           //Methode zum blinken/Farbwechsel tauschen
            }
            if (invincibleTimer >= invincibleStop) {                                    //Wenn Unverwundbarkeitszeit abgelaufen, dann
                invincible = false;                                                     //unverwundbarkeit wieder aus
                player.setHitVisual(invincible);                                        //Ausgangsfarbe wieder einstellen
            }
        }

        fenster.clear();
        player.render(fenster);                                                         //Player im Fenster zeichen

        for (const Alien& a : aliens) {                                                 //a ist die Referenz (&) auf ein Alien, welches nicht veraendert werden darf (const)
            a.render(fenster);                                                          //a : aliens -> a bekommt nacheinander jedes Element aus aliens (Was eine Referenz von Alien ist und keine Kopie!)
        }                                                                               //Diese Referenz a in das fenster zeichnen
    
        if (playershot.has_value()) {                                                   //Wenn gerade einen Shot vom Spieler existiert, DANN
            playershot->render(fenster);                                                //Zeichne den Schuss in das Fenster
    
        }                                                                               //Hier keine isActive Abfrage, weil render Active bereits kontrolliert
        if (alienShot.has_value()) {                                                    //Wenn gerade einen Shot vom Spieler existiert, DANN                                                                             
            alienShot->render(fenster);                                                 //Zeichne den Schuss in das Fenster
        }

        fenster.draw(playerLives);
        fenster.draw(gameName);
        fenster.draw(scoreBoard);

        if (gameOverStatus) {
            fenster.draw(gameOverText);
        }

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

#include "Game.h"
#include "GameField.h"
#include <iostream>
#include <string>

//Highscore Boe: 13140      Jasmin: 10070
//Highscore Simon: 21180

//Methode zum Aufbau der Barrieren 
void Game :: buildBarriers() {                                                        
    barriers.clear();                                                               //Erstmal aufräumen
    int hp = 10;                                                                    //Definieren der Trefferpunkte
    int damage = 0;                                                                 //???

    const int rows = 1;                                                             //Anzahl Reihen nach unten (y)
    const int cols = 4;                                                             //Anzahl Spalten nach rechts (x)

    const float startX = 75.f;                                                      //Start X Koordinate erster Barriere
    const float startY = 750.f;                                                     //Start Y Koordinate erster Barriere

    const float gapX = 225.f;                                                       //Abstand X zwischen zwei Barrieren
    const float gapY = 0.f;                                                         //Abstand Y zwischen zwei Barrieren

    for (int i = 0; i < rows; i++) {                                                //Schleife - Reihen durchlaufen 
        for (int j = 0; j < cols; j++) {                                            //Schleife - Spalten durchgehen 
            float x = startX + j * gapX;                                            //X - Position fuer Barrieren Platzierung
            float y = startY + i * gapY;                                            //Y - Position fuer Barrieren Platzierung
            barriers.emplace_back(x, y);                                            //Positionen (x,y) weitergeben
        }
    }
}
//Methode zum Aufbau der Alienfront
void Game :: buildAliens() {                                                        
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
//Methode fuer die Alienbewegung bzw. Positions Aktualisierung
void Game :: updateAliens(float dt) {                                               
    float moveX = alienDirection * alienSpeed * dt;                                             //Bewegung in X-Richtung (Bestehend aus Richtung, Geschwindigkeit und delta Time)
    bool border = false;                                                                        //Grenze des Fensters anlegen (Bewegungsgrenze)

    for (const Alien& a : aliens) {                                                             //Alle Aliens durchgehen und kontrollieren:
        if (alienDirection > 0 && a.right() >= static_cast<float>(fenster.getSize().x)) {       //WENN sich die Aliens nach rechts bewegen & die rechte Kante eines Aliens sich mit der rechten Fensterbegrenzung schneidet:
            border = true;                                                                      //DANN setze die Begrenzung 
        }
        if (alienDirection < 0 && a.left() <= 0.f) {                                            //WENN sich die Aliens nach links bewegen & die linke Kante eines Aliens sich mit der linken Fensterbegrenzung schneidet:
            border = true;                                                                      //DANN setze die Begrenzung
        }                                  
    }

    if (border) {                                                                               //WENN ein Alien am rechten oder linken Spielfeldrand ist (border == true)
        for (Alien& a : aliens) {                                                               //DANN soll jedes Alien:
            a.move(0.f, alienDrop);                                                             //Nach unten (Y) um den vorgegebenen Wert "alienDrop" bewegt werden
        }
        alienDirection *= -1.f;                                                                 //Danach wird die Bewegungsrichtung umgekehrt
    } else {                                                                                    //Solange kein Alien eine Begrenzung erreicht hat
        for (Alien& a : aliens) {                                                               //Soll sich jedes Alien
            a.move(moveX, 0.f);                                                                 //Um die errechnete Bewegungseinheit auf X bewegen
        }
    }
}
//Methode fuer die Erzeugung der Textfelder
void Game :: initDisplay() {                                                        
    font.loadFromFile("assets/fonts/zephyrean-brk.ttf");                            //Schriftart aus der ...ttf Datei in ein font Objekt laden 

    gameName.setFont(font);                                                         //Textfeld "gameName" die Schriftart zuweisen
    gameName.setCharacterSize(115);                                                 //Textgroesse vom Textfeld "gameName" definieren
    gameName.setString("SPACE INVADERS");                                           //Text vom Textfeld "gameName" definieren
    gameName.setFillColor(sf :: Color :: Green);                                    //Textfarbe vom Textfeld "gameName" definieren

    scoreBoard.setFont(font);                                                       //Textfeld "scoreBoard" Textart zuweisen
    scoreBoard.setCharacterSize(45);                                                //Textgroesse vom Textfeld "scoreBoard" definieren
    scoreBoard.setFillColor(sf :: Color :: Cyan);                                   //Textfarbe vom Textfeld "scoreBoard" definieren

    playerLives.setFont(font);                                                      //Eigenschaften vom Textfeld "playerLives" festlegen
    playerLives.setCharacterSize(45);                                               
    playerLives.setFillColor(sf :: Color :: Cyan);                                  

    gameOverText.setFont(font);                                                     //Eigenschaften vom Textfeld "gameOverText" festlegen
    gameOverText.setCharacterSize(180);                                             
    gameOverText.setString("GAME OVER");                                            
    gameOverText.setFillColor(sf :: Color :: Red);                                  

    highScore.setFont(font);                                                        //Eigenschaften vom Textfeld "highScore" festlegen                             
    highScore.setCharacterSize(100);                                             
    highScore.setString("HIGH SCORE: " + std::to_string(highscore));             
    highScore.setFillColor(sf :: Color :: Cyan);                                 


    miniIntroduction.setFont(font);                                                 //Eigenschaften vom Textfeld "miniIntroduction" festlegen
    miniIntroduction.setCharacterSize(55);                                          
    miniIntroduction.setString("Controlls: \n"
        "\n"
        "move Player left _ arrow key left \n"                                      //vielleicht Pfeil-Icons
        "move Player right _  arrow key right \n"
        "Player shoots _ space \n"
        "continue playing _ P\n"
        "continue after Gameover _ R \n"
        "\n"
        "\n"
        "Remake of Space Invaders Arcade \n"
        "made by: Boerge + Simon : )");             
    miniIntroduction.setFillColor(sf :: Color :: Magenta);                           

    gameOverAddOn.setFont(font);                                                    //Eigenschaften vom Textfeld "gameOverAddOn" festlegen
    gameOverAddOn.setCharacterSize(80);                                             
    gameOverAddOn.setString("to continue press: R");                                
    gameOverAddOn.setFillColor(sf :: Color :: Red);                                 

    pausedText.setFont(font);                                                       //Eigenschaften vom Textfeld "pausedText" festlegen
    pausedText.setCharacterSize(115);
    pausedText.setString("PAUSE MENU");
    pausedText.setFillColor(sf :: Color :: Magenta);
    updateDisplay();                                                                //Aufruf der Text-Update Methode fuer Score Aenderung + Text-Positionierung
} 
//Methode fuer die Display-Aktualisierung und Positionierung der Textfelder
void Game :: updateDisplay() {                                                                      
    scoreBoard.setString("SCORE:\n" + std :: to_string(score));                                                                     //Textausgabe als String -> Umwandelung Int Score in einen String
    scoreBoard.setPosition(10.f, 10.f);                                                                                             //Position fuer das Score-Textfeld definieren (x,y)

    playerLives.setString("LIVES:\n" + std :: to_string(playerLivesAmount));                                                        //Int Playerleben Variable im Textfeld anzeigen

    float fensterBreite = static_cast<float>(fenster.getSize().x);                                                                  //Breite des gesamten Fensters (Size in pixel bzw int darum in float umwandeln) als Temp-Variable
    float fensterHoehe = static_cast<float>(fenster.getSize().y);                                                                   //Hoehe des gesamten Fensters als Temp-Variable

    auto titel = gameName.getLocalBounds();                                                                                         //Mase des Textfeld-Rechtecks title
    gameName.setPosition((fensterBreite - titel.width) / 2.f - titel.left + 10.f, 2.f);                                             //Position fuer Game Titel (x,y), Mathematisch berechnen - Offset (Textfeld Versatz links)

    auto lP = playerLives.getLocalBounds();                                                                                         //auto entspricht dem Ausdruck: sf :: FloatRect TEXTFELD = ...
    playerLives.setPosition(fensterBreite - lP.width - 10.f - lP.left, 10.f);                                                       //10.f = Abstand zum Rand (fuer die Optik)

    auto hS = highScore.getLocalBounds();
    highScore.setPosition((fensterBreite - hS.width) / 2.f - hS.left, (fensterHoehe - hS.height) / 2.f - hS.top - 235.f);

    auto gOver = gameOverText.getLocalBounds();                                                     
    gameOverText.setPosition((fensterBreite - gOver.width) / 2.f - gOver.left, (fensterHoehe - gOver.height) / 2.f - gOver.top - 55.f);     

    auto gAdd = gameOverAddOn.getLocalBounds();                                                                                             
    gameOverAddOn.setPosition((fensterBreite - gAdd.width) / 2.f - gAdd.left, (fensterHoehe / 2.f + gOver.height / 2.f) - 15.f);            

    auto mI = miniIntroduction.getLocalBounds();                                                                                            
    miniIntroduction.setPosition((fensterBreite - mI.width) / 2.f - mI.left, (fensterHoehe - mI.height) / 2.f);                             

    auto pause = pausedText.getLocalBounds();
    pausedText.setPosition((fensterBreite - pause.width) / 2.f - pause.left, 2.f);
} 

void Game :: tryAlienShoot(float dt) {                                              //Alien Schuss Berechnung... Alien Auswahl + Start Koordinaten berechnen 
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

void Game :: restartGame() {                                                        //Option zum Restart bei Gameover und R
    gameOverStatus = false;                                                         //Alle Kontroll-Variablen zuruecksetzen
    hitPause = false;
    invincible = false;
    blinkOn = false;
    hitPauseTimer = 0.f;                                                            //Timer zuruecksetzen       
    invincibleTimer = 0.f;
    blinkTimer = 0.f;
    score = 0;                                                                      //Score zuruecksetzen
    playerLivesAmount = 3;                                                          //Leben zuruecksetzen
    
    playershot.reset();                                                             //Optionaler Spielerschuss loeschen
    alienShot.reset();                                                              //Optionaler Alienschuss loeschen

    buildAliens();                                                                  //Neue Alienfront
    buildBarriers();

    player.setHitVisual(false);                                                     //Absicherung fuer normale Farbe 

    updateDisplay();                                                                //Alle Resets anzeigen
} 

void Game :: pauseGame() {
    paused = !paused;
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

    buildBarriers();    
    while (fenster.isOpen()) {                                                      //Feedback vom fenster (es existiert)
        sf :: Event event;                                                          //Variable event zum abfangen von befehlen
                                                                                    
        while (fenster.pollEvent(event)) {                                          //Holt das naechste Event aus Warteschlange und schreibt es in event
            if (event.type == sf :: Event :: Closed) {                              //Bei Anwahl x Fenster schliessen
                fenster.close();
            }
            if (event.type == sf :: Event :: KeyPressed) {
                if (event.key.code == sf :: Keyboard :: P || event.key.code == sf :: Keyboard :: Escape) {
                    pauseGame();
                }
                if (gameOverStatus && event.key.code == sf :: Keyboard :: R) {
                    restartGame();
                }
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

        if (!gameOverStatus && !hitPause && !paused) {                                                 //Spiel laeuft, wenn kein Gameover oder Treffer am Spieler
            
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

            if (playershot.has_value() && playershot->isActive() && !paused) {                         //Player - Schuss existiert und ist aktiv
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
//Barrier Änderungen
                for (int i = 0; i < barriers.size(); i++) {                                   //solange i kleiner als die Anzahl der existierenden Barrieren ist
                    if (playershot->hitbox().intersects(barriers[i].hitbox())) {              //Pruefe mit intersects(SFLM-Fkt zum testen, schneiden sich zwei Rechtecke), indem Fall schneidet sich die Hitbox des Schusses mit einem Barrier[i]
                        barriers[i].damage(1);                                          //Barriere um 1 HP beschädigen
                        playershot->deactivate();
                        
                        if (barriers[i].getHealthPoints() <= 5 && barriers[i].getHealthPoints() > 3) {                      //Wenn HP der Barriere kleiner als 10 aber groesser als 5, dann
                            barriers[i].setColor(sf :: Color :: Yellow);                           //Farbe der Barriere auf Gelb aendern                                                    
                            updateDisplay();
                        }
                        if (barriers[i].getHealthPoints() <= 3 && barriers[i].getHealthPoints() > 0) {                      //Wenn HP der Barriere kleiner als 10 aber groesser als 5, dann
                            barriers[i].setColor(sf :: Color :: Red);                           //Farbe der Barriere auf Rot aendern                                                     
                            updateDisplay();
                        }
                        if (barriers[i].getHealthPoints() <= 0) {                                        //Wenn HP der Barriere 0 oder kleiner, dann
                            barriers.erase(barriers.begin() + i);                               //Barriere loeschen
                            updateDisplay();                                 
                            break;                                                              //Schleife verlassen, weil durch erase ein Element fehlt...Dadurch ist barrier.size() um eins kleiner und es muss erneut von vorn kontrolliert werden
                    }
                }
            }


                if (playershot->upperLimit() < 130.f) {                                     //Wenn Schuss ist hinter festgelegter Grenze, deaktivieren
                    playershot->deactivate();                                               //Schaltet den Schuss aus 
                }            
            }    
        }   
        
        if (aliens.empty() && !paused) {                                                       //Wenn keine Aliens mehr in dem Fenster sind
            if (playerLivesAmount < 3) {                                            //Wenn Spieler keine 3 Leben, dann
                playerLivesAmount += 1;                                             //1 Leben dazu 
                updateDisplay();                                                    //Display aktualisieren
            } 
            buildAliens();                                                          //DANN erstelle erneut eine Formation
        }

        if (alienShot.has_value() && alienShot->isActive()&& !paused) {      
            alienShot->update(dt);

            if (alienShot->lowerLimit() > static_cast<float>(fenster.getSize().y)) {    //Schuss verlässt Spielfeld / ueber Fenstergroesse hinaus
                alienShot->deactivate();

            } else if (alienShot->hitbox().intersects(player.hitbox())) {               //Treffer am Spieler registriert
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
                    
                } else {                                                                //TREFFER Anzeige
                    hitPause = true;                                                    //ANSONSTEN Stopp/stehen an (Player bleibt stehen)
                    hitPauseTimer = 0.f;                                                //Start Standzeit

                    invincible = true;                                                  //Unverwundbarkeitsphase an
                    invincibleTimer = 0.f;                                              //Unverwundbarkeitszeit startet

                    blinkTimer = 0.f;                                                   //Blink Zeit startet
                    blinkOn = true;                                                     //blinken an
                    player.setHitVisual(blinkOn);                                       //Methode zum blinken aufrufen mit true
                }
            //Alienshot killt Barrier    
            } else {

                for (int j = 0; j < barriers.size(); j++) {                                   //solange i kleiner wie Anzahl der existierenden Aliens ist
                    if (alienShot->hitbox().intersects(barriers[j].hitbox())) {              //Pruefe mit intersects(SFLM-Fkt zum testen, schneiden sich zwei Rechtecke), indem Fall schneidet sich die Hitbox des Schusses mit einem Alien[i]
                        barriers[j].damage(1);                                          //Barriere um 1 HP beschädigen
                        alienShot->deactivate();
                        
                        if (barriers[j].getHealthPoints() <= 5 && barriers[j].getHealthPoints() > 3) {                      //Wenn HP der Barriere kleiner als 7 aber groesser als 5, dann
                            barriers[j].setColor(sf :: Color :: Yellow);                           //Farbe der Barriere auf Gelb aendern                                                    
                            updateDisplay();
                        }
                        if (barriers[j].getHealthPoints() <= 3 && barriers[j].getHealthPoints() > 0) {                      //Wenn HP der Barriere kleiner als 5 aber groesser als 0, dann
                            barriers[j].setColor(sf :: Color :: Red);                           //Farbe der Barriere auf Rot aendern                                                     
                            updateDisplay();
                        }
                        if (barriers[j].getHealthPoints() <= 0) {                                        //Wenn HP der Barriere 0 oder kleiner, dann
                            barriers.erase(barriers.begin() + j);                               //Barriere loeschen
                            updateDisplay();                                 
                            break;                                                              //Schleife verlassen, weil durch erase ein Element fehlt...Dadurch ist barrier.size() um eins kleiner und es muss erneut von vorn kontrolliert werden
                    }
                }

                }

            }
        }

        for (const Alien& a : aliens) {                                                 //Kontrolle, erreicht ein Alien (alle Aliens) den Spieler
            float loseLineY = player.spielerPosY;                                       //Linie auf Hoehe des Spielers um Gameover zu ermitteln
            if (a.bottom() >= loseLineY) {
                gameOverStatus = true;                                                  //Alien erreicht Spielerhoehe -> Gameover
                break;
            }
        }
        
        if (invincible && !paused) {                                                               //Wenn unverwundbar, dann
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
        //RenderWindow / fenster befüllen 
        fenster.clear();

        if (paused) {
            fenster.draw(pausedText);
            fenster.draw(miniIntroduction);
        } else {
            player.render(fenster);                                                         //Player im Fenster zeichen

            for (const Alien& a : aliens) a.render(fenster);                                //a ist die Referenz (&) auf ein Alien, welches nicht veraendert werden darf (const); a : aliens -> a bekommt nacheinander jedes Element aus aliens (Was eine Referenz von Alien ist und keine Kopie!
            for (const Barrier& b : barriers) b.render(fenster);                            //b ist die Referenz (&) auf eine Barriere, welches nicht veraendert werden darf (const); b : barriers -> b bekommt nacheinander jedes Element aus barriers (Was eine Referenz von Barrier ist und keine Kopie!
            
            if (playershot.has_value()) playershot->render(fenster);                        //Wenn gerade einen Shot vom Spieler existiert, DANN                                                                                    
            if (alienShot.has_value()) alienShot->render(fenster);                          //Wenn gerade einen Shot vom Spieler existiert, DANN
            
            fenster.draw(playerLives);                                                      //Alle Textfelder auf das Fenster zeichnen
            fenster.draw(gameName);
            fenster.draw(scoreBoard);
        }
        
        if (gameOverStatus && !paused) {                                                    //Textfeld ausgabe bei GameOver
            if (score > highscore) {                                                        //Wenn Highscore gebrochen wurde
                highscore = score;                                                          //Highscore wird zu Score
                highScore.setString("HIGH SCORE: " + std::to_string(highscore));            //Highscore Text aktualisieren    
            
                //Blinken des Highscores bei neuem Highscore
                highScoreBlinkTimer = 0.f;
                highScoreBlink = true;
                if (highScoreBlink) {
                    highScoreBlinkTimer += dt;
                    TestTimer+= dt;
                    highScore.setFillColor(sf :: Color :: Magenta);
                    updateDisplay();   

                    if (highScoreBlinkTimer >= highScoreBlinkInterval) {                          
                    highScoreBlinkTimer = 0.f;                                                      
                    highScoreBlink = !highScoreBlink;
                    highScore.setFillColor(sf :: Color :: Cyan);
                    updateDisplay();                                                   
                    }
                    
                    if(TestTimer >= 100.0f){
                        highScoreBlink = false;
                        highScore.setFillColor(sf :: Color :: Cyan);
                        updateDisplay();
                    }
                    
                }
                
                

                
            
            
            }
            fenster.draw(highScore);
            fenster.draw(gameOverText);
            fenster.draw(gameOverAddOn);
        }

        fenster.display();                                                                  //SFML Fenster auf dem Screen anzeigen

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

# include "GameField.h"
/*
void GameField :: initDisplay() {                                                        //Definieren der Texteigenschaften - Display
    font.loadFromFile("assets/fonts/zephyrean-brk.ttf");                            //Textart laden

    gameName.setFont(font);                                                         //Textart zuweisen
    gameName.setCharacterSize(90);                                                  //Textgroesse definieren
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

    miniIntroduction.setFont(font);                                                 //Textart zuweisen
    miniIntroduction.setCharacterSize(38);                                          //Textgroesse definieren
    miniIntroduction.setString("Controlls: move left/right = arrow key left/right, shot = space");      //Text definieren       
    miniIntroduction.setFillColor(sf :: Color :: Yellow);                           //Textfarbe definieren

    gameOverAddOn.setFont(font);                                                    //Textart zuweisen
    gameOverAddOn.setCharacterSize(75);                                             //Textgroesse definieren
    gameOverAddOn.setString("to continue press: R");                                //Text definieren
    gameOverAddOn.setFillColor(sf :: Color :: Red);                                 //Textfarbe definieren

    updateDisplay();                                                                //Aufruf der Text-Update Methode fuer Score Aenderung
}

void GameField :: updateDisplay() {                                                                      //Aktualiert staendig den Score 
    scoreBoard.setString("SCORE: " + std :: to_string(score));                                      //Textausgabe im SFML, darum muss der Int Score in einen String gewandelt werden...
    scoreBoard.setPosition(10.f, 10.f);                                                             //Position fuer Score definieren (x,y)

    playerLives.setString("LIVES: " + std :: to_string(playerLivesAmount));                         //Playerleben mit der int Variable anzeigen

    float fensterBreite = static_cast<float>(fenster.getSize().x);                                  //Breite des gesamten Fensters (Size in pixel bzw int darum in float umwandeln)
    float fensterHoehe = static_cast<float>(fenster.getSize().y);                                   //Hoehe des gesamten Fensters

    auto titel = gameName.getLocalBounds();                                                         //Mase des Text-Rechtecks title
    gameName.setPosition((fensterBreite - titel.width) / 2.f - titel.left + 15.f, 2.f);             //Position fuer Game Titel (x,y), Mathematisch berechnen - Offset (Textfeld Versatz links)

    auto lP = playerLives.getLocalBounds();                                                         //Mase des Text-Rechtecks player
    playerLives.setPosition(fensterBreite - lP.width - 10.f - lP.left, 10.f);                       //10.f = Abstand zum Rand (fuer die Optik)

    auto gOver = gameOverText.getLocalBounds();                                                     //Mase des Text-Rechtecks gameOver
    gameOverText.setPosition((fensterBreite - gOver.width) / 2.f - gOver.left, (fensterHoehe - gOver.height) / 2.f - gOver.top - 55.f);     //Position fuer GameOver Textfeld mittig auf Fenster anzeigen

    auto mI = miniIntroduction.getLocalBounds();                                                                                            //Mase des Text-Rechtecks miniIntroduction
    miniIntroduction.setPosition((fensterBreite - mI.width) / 2.f - mI.left, titel.height + 25.f);                                          //Position fuer die miniIntroduction ermiteln

    auto gAdd = gameOverAddOn.getLocalBounds();                                                                                             //Mase des Text-Rechtecks GameOver Zusatz Text
    gameOverAddOn.setPosition((fensterBreite - gAdd.width) / 2.f - gAdd.left, (fensterHoehe / 2.f + gOver.height / 2.f) - 15.f);            //Position fuer den GameOver Zusatz ermitteln
}

void GameField :: restartGame() {                                                        //Option zum Restart bei Gameover und R
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

    player.setHitVisual(false);                                                     //Absicherung fuer normale Farbe 

    updateDisplay();                                                                //Alle Resets anzeigen
}

*/

GameField :: GameField (sf :: RenderWindow fenster) {
    //Groesse festlegen
    //BAUSTELLE xD
}
#include "Player.h"

Player :: Player() {                                            //Objekt Spieler erzeugen

    spieler.setSize({60.f, 30.f});                              //Spielerfigur Groesse definieren
    spieler.setFillColor(sf :: Color :: Green);                //Spielerfigut Farbe definieren
    spieler.setPosition(420.f, spielerPosY);                    //Position des Spielers definieren

    speed = 550.f;                                              //Bewegungsgeschwindigkeit [Pixel pro Sekunde]
    direction = 0.f;

    shotStatus = false;                                      //Schuss nur bei Tasteneindruck
}

void Player :: handleInput() {
    //Bewegung - Player
    direction = 0.f;
    if (sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Left)) {   //Bei Eingabe Links
        direction -= 1.f;                                           //Bewegung ein Feld nach Links auf X, Y=0
    }
    if (sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Right)) {  //Bei Eingabe Rechts
        direction += 1.f;;                                          //Bewegung ein Feld nach Links auf X, Y=0
    }
    //Schuss - Player
    if (sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Space)) {  //Bei Eingabe Space
        shotStatus = true;                                       //Schussanforderung true setzen
    }
}

void Player :: update(float dt, float windowWidth) {                //float dt = delta Time 
    spieler.move(direction * speed * dt, 0.f);
    
    //Grenzen fuer die Bewegung des Spielers einstellen
    float x = spieler.getPosition().x;                              //x Position ermitteln
    float width = spieler.getSize().x;                              //Breite des Spielers speichern

    if (x < 0.f) x = 0.f;                                            //Pruefen Links
    if (x + width > windowWidth) x = windowWidth - width;            //Pruefen Rechts

    spieler.setPosition(x, spielerPosY);                            //Wenn ausserhalb, Position ueberschreiben
}

void Player :: render(sf :: RenderWindow&fenster) {                 //Zeichnet die Player Figur mit vorgegebenen Eigenschaften
    fenster.draw(spieler);
}

bool Player :: shotRequest() const {                                //Gibt den Shot-Status zurück... 
    return shotStatus;                                              //Um zu schauen ob der Befehl zum schiessen kam oder nicht
}

void Player :: processShotRequest() {                               //Nach einem Schuss die Schussbestaetigung wieder ruecksetzen
    shotStatus = false;
}

sf :: Vector2f Player :: shotStartPosition() const {                //Startpunkt fuer Schuss-Animation definieren
    float x = spieler.getPosition().x + spieler.getSize().x / 2.f - 3.f;        //X-Koordinate Ab da wo der Spieler ist + halbe Breite und halbem Schuss
    float y = spieler.getPosition().y - 18.f;                                   //Y-Koordinate Ab der oberseite des Spielers
    return{x, y};                                                               //Werte uebergeben
}
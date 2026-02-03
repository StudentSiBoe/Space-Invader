#include "Player.h"

Player :: Player() {                                            //Objekt Spieler erzeugen

    spieler.setSize({50.f, 30.f});                              //Spielerfigur Groesse definieren
    spieler.setFillColor(sf :: Color :: Yellow);                //Spielerfigut Farbe definieren
    spieler.setPosition(420.f, spielerPosY);                    //Position des Spielers definieren

    speed = 600.f;                                              //Bewegungsgeschwindigkeit [Pixel pro Sekunde]
    direction = 0.f;

    shotRequested = false;                                      //Schuss nur bei Tasteneindruck
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
        shotRequested = true;                                       //Schussanforderung true setzen
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

void Player :: render(sf :: RenderWindow&fenster) {
    fenster.draw(spieler);
}

bool Player :: shotRequest() const {
    return shotRequested;
}

void Player :: processShotRequest() {
    shotRequested = false;
}

sf :: Vector2f Player :: shotStartPosition() const {
    float x = spieler.getPosition().x + spieler.getSize().x / 2.f - 3.f;
    float y = spieler.getPosition().y - spielerPosY;
    return{x, y};
}
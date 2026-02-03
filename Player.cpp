#include "Player.h"

Player :: Player() {                                            //Objekt Spieler erzeugen

    spieler.setSize({50.f, 30.f});                              //Spielerfigur Groesse
    spieler.setFillColor(sf :: Color :: Blue);                  //Spielerfigut Farbe
    spieler.setPosition(420.f, spielerPosY);                          //Position des Spielers

    speed = 600.f;                                              //Bewegungsgeschwindigkeit [Pixel pro Sekunde]
    direction = 0.f;
}

void Player :: handleInput() {
    direction = 0.f;
    if (sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Left)) {   //Bei Eingabe Links
        direction -= 1.f;                                           //Bewegung ein Feld nach Links auf X, Y=0
    }
    if (sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Right)) {  //Bei Eingabe Rechts
        direction += 1.f;;                                          //Bewegung ein Feld nach Links auf X, Y=0
    }
}

void Player :: update(float dt, float windowWidth) {                //float dt = delta Time 
    spieler.move(direction * speed * dt, 0.f);
    
    //Grenzen fuer die Bewegung des Spielers einstellen
    float x = spieler.getPosition().x;                              //x Position ermitteln
    float width = spieler.getSize().x;                              //Breite des Spielers speichern

    if(x < 0.f) x = 0.f;                                            //Pruefen Links
    if(x + width > windowWidth) x = windowWidth - width;            //Pruefen Rechts

    spieler.setPosition(x, spielerPosY);                                    //Wenn ausserhalb, Position ueberschreiben
}

void Player :: render(sf :: RenderWindow&fenster) {
    fenster.draw(spieler);
}
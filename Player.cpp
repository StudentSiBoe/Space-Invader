#include "Player.h"

Player :: Player() {                                            //Objekt Spieler erzeugen

    shape.setSize({50.f, 30.f});                                //Spielerfigur Groesse
    shape.setFillColor(sf :: Color :: Blue);                    //Spielerfigut Farbe
    shape.setPosition(420.f, 850.f);                            //Position des Spielers

    speed = 700.f;                                              //Bewegungsgeschwindigkeit [Pixel pro Sekunde]
}

void Player :: handleInput() {

    if (sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Left)) {       //Bei Eingabe Links
        shape.move(-3.f, 0.f);                                          //Bewegung ein Feld nach Links auf X, Y=0
    }
    if (sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Right)) {      //Bei Eingabe Rechts
        shape.move(3.f, 0.f);                                           //Bewegung ein Feld nach Links auf X, Y=0
    }
}

void Player :: update(float dt) {
    shape.move(0.f, 0.f);
}

void Player :: render(sf :: RenderWindow&fenster) {
    fenster.draw(shape);
}
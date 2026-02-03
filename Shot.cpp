#include "Shot.h"

Shot :: Shot(float AbX, float AbY) {                            //Objekt Schuss erzeugen
    
    schuss.setSize({6.f, 16.f});                                //Schuss Groesse definieren
    schuss.setFillColor(sf :: Color :: Red);                    //Schuss Farbe definieren

    schuss.setPosition(AbX, AbY);                               //Schuss Startposition definieren

    speed = 500.f;                                              //Schuss Geschwindigkeit definieren
    active = true;                                              //Schuss Ja oder Nein
}

void Shot :: update(float dt) {
    if (!active) return;
    schuss.move(0.f, -speed * dt);                              // - weil der Schuss nach oben gehen soll           
}

void Shot :: render(sf :: RenderWindow&fenster) const {
    if (!active) return;
    fenster.draw(schuss);
}

bool Shot :: isActive() const {
    return active;
}

void Shot :: deactivate() {
    active = false;
}

float Shot :: upperLimit() const {
    return schuss.getPosition().y;
}

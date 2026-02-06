#include "Shot.h"

Shot :: Shot(float abX, float abY) {                            //Objekt Schuss erzeugen
    
    schuss.setSize({6.f, 16.f});                                //Schuss Groesse definieren
    schuss.setFillColor(sf :: Color :: Red);                    //Schuss Farbe definieren
    schuss.setPosition(abX, abY);                               //Schuss Startposition definieren

    speed = 650.f;                                              //Schuss Geschwindigkeit definieren
    active = true;                                              //Schuss Ja oder Nein
}

void Shot :: update(float dt) {
    if (!active) return;                                        //nur bei einem Schuss die Methode ausführen
    schuss.move(0.f, -speed * dt);                              //Schussbewegung in x-Richtung = 0 und y-Richtung: - Geschwindigkeit(hoch) * delta time           
}

void Shot :: render(sf :: RenderWindow&fenster) const {         //Zeichnet den Schuss mit Eigenschaften, wenn geschossen wird
    if (!active) return;
    fenster.draw(schuss);
}

bool Shot :: isActive() const {                                 //Schuss ist aktiviert (fliegt noch)
    return active;                                              //aktiv = true, wenn neuer Schuss erzeugt wird...
}

void Shot :: deactivate() {                                     //Schuss auf deaktiviert/false setzen
    active = false;
}

float Shot :: upperLimit() const {                              //Fuer den Vergleich der aktuellen Pos-Y mit dem oberen Limit
    return schuss.getPosition().y;
}

sf :: FloatRect Shot :: hitbox() const {                        //FloatRect...Ist ein SFML Recheck
    return schuss.getGlobalBounds();                            //betrachtet das aktuelle Shape/rechteck und nimmt Position, Groesse und baut ein aequivalentes Rechteck dazu
}
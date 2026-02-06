#include "AlienShot.h"

AlienShot :: AlienShot(float abX, float abY) {                              //Objekt Schuss erzeugen
    
    alienschuss.setSize({10.f, 30.f});                                       //Schuss Groesse definieren
    alienschuss.setFillColor(sf :: Color :: Blue);                          //Schuss Farbe definieren
    alienschuss.setPosition(abX, abY);                                      //Schuss Startposition definieren

    speed = 500.f;                                                          //Schuss Geschwindigkeit definieren
    active = true;                                                          //Schuss Ja oder Nein
}

void AlienShot :: update(float dt) {
    if (!active) return;                                                    //nur bei einem Schuss die Methode ausführen
    alienschuss.move(0.f, speed * dt);                                      //Schussbewegung in x-Richtung = 0 und y-Richtung: - Geschwindigkeit(hoch) * delta time           
}

void AlienShot :: render(sf :: RenderWindow&fenster) const {                //Zeichnet den Schuss mit Eigenschaften, wenn geschossen wird
    if (!active) return;
    fenster.draw(alienschuss);
}

bool AlienShot :: isActive() const {                                        //Schuss ist aktiviert (fliegt noch)
    return active;                                                          //aktiv = true, wenn neuer Schuss erzeugt wird...
}

void AlienShot :: deactivate() {                                            //Schuss auf deaktiviert/false setzen
    active = false;
}

float AlienShot :: lowerLimit() const {                                     //Fuer den Vergleich der aktuellen Pos-Y mit dem oberen Limit
    return alienschuss.getPosition().y + alienschuss.getSize().y;
}

sf :: FloatRect AlienShot :: hitbox() const {                               //FloatRect...Ist ein SFML Recheck
    return alienschuss.getGlobalBounds();                                   //betrachtet das aktuelle Shape/rechteck und nimmt Position, Groesse und baut ein aequivalentes Rechteck dazu
}
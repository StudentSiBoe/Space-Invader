#include "Alien.h"

Alien :: Alien(float x, float y) {                                     //Objekt Alien erzeugen

   alien.setSize({45.f, 45.f});                                        //Groesse eines Aliens definieren
   alien.setFillColor(sf :: Color :: White);                           //Farbe eines Aliens definieren
   alien.setPosition(x, y);                                            //Position eines Aliens

}
sf :: FloatRect Alien ::  hitbox() const {                             //FloatRect...Ist ein SFML Recheck
   return alien.getGlobalBounds();                                     //betrachtet das aktuelle Shape/rechteck und nimmt Position, Groesse und baut ein aequivalentes Rechteck dazu
}

void Alien :: render(sf :: RenderWindow&fenster) const {               //Alien auf dem Fenster zeichnen 
   fenster.draw(alien);
 }     

 void Alien :: move(float dx, float dy) {                              //Bewegung eines Aliens 
   alien.move(dx, dy);
 }

 float Alien :: left() const {                                         //Genau Position (x-Achse) eines Aliens (links)
   return alien.getPosition().x;                                       //Linke Seite des Aliens 
 }

 float Alien :: right() const {                                        //Genau Position (x-Achse) eines Aliens (rechts)
   return alien.getPosition().x + alien.getSize().x;                   //Rechte Seite des Aliens (durch Breite)
 }

 float Alien :: bottom() const {
   return alien.getPosition().y + alien.getSize().y;                    //gibt genaue Y-Pos + Hoehe bzw Groesse-Y zurueck -> Pos untere Kante - Alien   
 }
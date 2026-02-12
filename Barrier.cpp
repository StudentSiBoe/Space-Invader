#include "Barrier.h"
Barrier :: Barrier(float x, float y) {                                     //Objekt Barrier erzeugen

   barrier.setSize({75.f, 60.f});                                        //Groesse einer Barriere definieren
   barrier.setFillColor(sf :: Color :: Cyan);                           //Farbe einer Barriere definieren
   barrier.setPosition(x, y);                                            //Position einer Barriere


}
sf :: FloatRect Barrier ::  hitbox() const {                             
   return barrier.getGlobalBounds();                                     //betrachtet das aktuelle Shape/rechteck und nimmt Position, Groesse und baut ein aequivalentes Rechteck dazu
}

void Barrier :: render(sf :: RenderWindow&fenster) const {               //Barrier auf dem Fenster zeichnen 
   fenster.draw(barrier);
 }     
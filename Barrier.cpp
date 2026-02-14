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

 int Barrier :: getHealthPoints() const {                                       //Methode um die aktuellen HP der Barriere zu erhalten, damit im Game.cpp kontrolliert werden kann, ob die Barriere zerstört werden muss
    return healthPoints;
   }

void Barrier :: damage(int amount) {                                       //Methode um die Barriere zu beschädigen, indem die HP um den übergebenen Betrag verringert werden
    healthPoints -= amount;
   }

void Barrier :: setColor(const sf :: Color& color) {                                       //Methode um die Farbe der Barriere zu ändern, damit im Game.cpp die Farbe der Barriere bei Beschädigung geändert werden kann
    barrier.setFillColor(color);
   }
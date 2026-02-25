#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class Barrier {

    public:
    Barrier(float x, float y);  //Konstruktor der Barriere, der die Position der Barriere auf dem Spielfeld festlegt
    
    void render(sf :: RenderWindow&fenster) const;  //Methode zum Zeichnen der Barriere auf dem Fenster

    int getHealthPoints() const; //Methode um die aktuellen HP der Barriere zu erhalten, damit im Game.cpp kontrolliert werden kann, ob die Barriere zerstört werden muss

    
    void setColor(const sf :: Color& color); //Methode um die Farbe der Barriere zu ändern, damit im Game.cpp die Farbe der Barriere bei Beschädigung geändert werden kann
    sf :: FloatRect hitbox() const; //Hitbox fuer das Barriere Rechteck erzeugen
    void damage(int amount);    //Methode um die Barriere zu beschädigen, indem die HP um den übergebenen Betrag verringert werden
    private:
    sf :: RectangleShape barrier;   //Rechteckform der Barriere    
    int healthPoints = 10;          //HP der Barriere, wenn HP 0 oder kleiner, dann wird die Barriere zerstört 
};
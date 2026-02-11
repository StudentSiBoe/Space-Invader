#pragma once
#include <SFML/Graphics.hpp>
class Barrier {

    public:
    Barrier(float x, float y);  //Konstruktor der Barriere, der die Position der Barriere auf dem Spielfeld festlegt
    
    void render(sf :: RenderWindow&fenster) const;  //Methode zum Zeichnen der Barriere auf dem Fenster

    sf :: FloatRect hitbox() const; //Hitbox fuer das Barriere Rechteck erzeugen
    int hp() const; //Methode um die HP der Barriere zu bestimmen
    void damage(int amount);    //Methode um die Barriere zu beschädigen, indem die HP um den übergebenen Betrag verringert werden
    private:
    sf :: RectangleShape barrier;   //Rechteckform der Barriere    
};
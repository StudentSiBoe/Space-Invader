#pragma once
#include <SFML/Graphics.hpp>

struct Alien{

    public:
    Alien(float x, float y);
    
    void render(sf :: RenderWindow&fenster) const;

    sf :: FloatRect hitbox() const;                                 //Hitbox fuer das Alien Rechteck erzeugen

    //Methoden zur Bewegung
    void move(float dx, float dy);
    float left() const;
    float right() const;

    private:
    sf :: RectangleShape alien;
};
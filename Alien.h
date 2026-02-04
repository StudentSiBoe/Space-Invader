#pragma once
#include <SFML/Graphics.hpp>

struct Alien{

    public:
    Alien(float x, float y);
    
    void render(sf :: RenderWindow&fenster) const;

    private:
    sf :: RectangleShape alien;
};
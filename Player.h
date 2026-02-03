#pragma once
#include <SFML/Graphics.hpp>

class Player{
    public:
    
    Player();
    float spielerPosY = 870.f;
    void handleInput();                                     //Bewegungssteuerung Spielfigur
    void update(float dt, float windowWidth);
    void render(sf :: RenderWindow&fesnter);

    private:
    sf :: RectangleShape spieler;                           //Zum anlegen der Spieler Eigenschaften
    float speed;
    float direction;
};
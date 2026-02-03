#pragma once
#include <SFML/Graphics.hpp>

class Player{
    public:
    
    Player();

    void handleInput();                                     //Bewegungssteuerung Spielfigur
    void update(float dt);
    void render(sf :: RenderWindow&fesnter);

    private:
    sf :: RectangleShape shape;
    float speed;
};
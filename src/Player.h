#pragma once
#include <SFML/Graphics.hpp>

class Player{
    
    public:
    Player();
    float spielerPosY = 870.f;
    void handleInput();                                     //Bewegungssteuerung Spielfigur
    void update(float dt, float windowWidth);
    void render(sf :: RenderWindow&fesnter);
    
    //Erweiterungen Methode - Schuss
    bool shotRequest() const;
    void processShotRequest();
    sf :: Vector2f shotStartPosition() const;

    sf :: FloatRect hitbox() const;
    
    void setHitVisual(bool on);
    
    private:
    sf :: RectangleShape spieler;                           //Zum anlegen der Spieler Eigenschaften
    float speed;
    float direction;

    bool shotStatus;                                     //Tastenabfrage für Schuss
};

#pragma once
#include <SFML/Graphics.hpp>

class Shot{

    public:
    Shot(float abX, float abY);

    void update(float dt);
    void render(sf :: RenderWindow&fenster) const;

    bool isActive() const;
    void deactivate();

    float upperLimit() const;                                       //obere Grenze Y-Pos (aus dem Fenster)

    sf :: FloatRect hitbox() const;                                 //Hitbox fuer das Schuss Rechteck erzeugen

    private:
    sf :: RectangleShape schuss;
    float speed;
    bool active;
};
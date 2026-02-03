#pragma once
#include <SFML/Graphics.hpp>

class Shot{

    public:
    Shot(float AbX, float AbY);

    void update(float dt);
    void render(sf :: RenderWindow&fenster) const;

    bool isActive() const;
    void deactivate();

    float upperLimit() const;                                        //obere Grenze Y-Pos (aus dem Fenster)

    private:
    sf :: RectangleShape schuss;
    float speed;
    bool active;
};
#pragma once
#include <SFML/Graphics.hpp>

class AlienShot {
    
    public:
    AlienShot(float abX, float abY);

    void update(float dt);
    void render(sf :: RenderWindow&fenster) const;

    bool isActive() const;
    void deactivate();

    float lowerLimit() const;
    sf :: FloatRect hitbox() const;

    private:
    sf :: RectangleShape alienschuss;
    float speed;
    bool active;
};

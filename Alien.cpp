#include "Alien.h"

Alien :: Alien(float x, float y) {

    alien.setSize({40.f, 40.f});
    alien.setFillColor(sf :: Color :: White);
    alien.setPosition(x, y);

}

void Alien :: render(sf :: RenderWindow&fenster) const {
    fenster.draw(alien);
 }     
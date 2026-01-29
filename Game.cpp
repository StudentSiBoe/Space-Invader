#include "Game.h"

int main (int argc, char ** argv) {
    
    Game game;
    game.run();
    return 0;

}
void Game::run(){
    init();
    while(true){
        processInput();         // Eingaben einlesen
        update();               // staendige Aktualisierung
        render();               // Ausgabe auf das Spielfeld-Fenster
    }
}
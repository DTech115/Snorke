#include "Game.h"
#include <iostream>

int main() {
    // INIT GAME ENGINE!!!
    Game game;

    //create the stuff
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    sf::Texture texture("smough.png");
    sf::Sprite sprite(texture);

    sprite.setScale({0.1f, 0.1f});  // it's so peak...

    // ~~~~GAME LOOP~~~~
    // run the program as long as the window is open
    while (game.running()) {
        //~~~~Update~~~~
        game.update();

        //~~~~Render~~~~
        game.render();

    }

    return 0;
}
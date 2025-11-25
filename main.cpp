#include "Game.h"

int main() {

    // //create stuff
    // sf::Texture texture("smough.png");
    // sf::Sprite sprite(texture);
    //
    // sprite.setScale({0.1f, 0.1f});  // it's so peak...

    // INIT GAME ENGINE!!!!
    Game game;

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
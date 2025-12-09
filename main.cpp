#include "Game.h"

int main() {


    // it's so peak...

    // INIT GAME ENGINE!!!
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
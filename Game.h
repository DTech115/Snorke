//
// Created by DT on 11/16/25.
//

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

// game engine class-like for doing most of the general stuff
class Game {
private:
    //vars
    sf::RenderWindow* window;
    sf::VideoMode videoMode;

    void initVars();
    void initWindow();
public:
    Game(); //constructor
    ~Game(); //destructor

    bool running();
    void pollEvents();
    void update();
    void render();
};



#endif //GAME_H

//
// Created by DT on 11/16/25.
//

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Snorke.h"

//game engine class like for doing most of the general stuff
enum Rooms { startRoom, secondRoom, thirdRoom };
class Game {
private:
    // variables
    sf::RenderWindow* window;
    sf::VideoMode videoMode;

    sf::Vector2i mousePos;
    sf::Texture texture;
    sf::Sprite* sprite;
    sf::IntRect rectSourceSprite;
    sf::Clock clock;

    bool mouseWasPressed = false;
    bool endGame;

    //objects
    Snorke snorke;
    Rooms room;

    // init functions!!!
    void initVars();
    void initWindow();

public:
    Game(); // constructor
    ~Game(); // destructor

    int  MouseOnDot(float x, float y, sf::RenderWindow &renderWindow);
    bool running();
    void pollEvents();
    void update();
    void render();
    void imageGeneratorLive();

};



#endif //GAME_H

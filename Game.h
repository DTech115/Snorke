//
// Created by DT on 11/16/25.
//

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Snorke.h"

//game engine class like for doing most of the general stuff
enum Rooms { startRoom, secondRoom, thirdRoom, topRoom };
class Game {
private:
    // variables
    sf::RenderWindow* window;
    sf::VideoMode videoMode;

    // saw stuff
    sf::Texture texture;
    sf::Sprite* sprite;
    sf::IntRect rectSourceSprite;
    sf::Clock clock;
    // saw movement
    sf::Vector2f sawSpeed;
    bool moveRight;

    // last door shape [ngl we should've optimized exits like this if we had time
    sf::RectangleShape finalDoor;
    sf::RectangleShape finalDoorBack;
    sf::RectangleShape exitDoor;

    // coin collection
    std::vector<sf::CircleShape> coins;
    std::vector<bool> coinCheck;

    // text stuff, make sure to DELETE IN DECONSTRUCTOR CHARLIE
    sf::Font gameFont;
    sf::Text* gameOverText;
    sf::Text* scoreText;
    sf::Text* winText;

    bool gameOver;
    bool allCoinsCollected;
    bool gameWin;

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

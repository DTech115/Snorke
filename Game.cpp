//
// Created by DT on 11/16/25.
//

#include "Game.h"

#include <iostream>

//private functions
void Game::initVars() {
    this->gameOver = false;
    this->gameWin = false;
    this->allCoinsCollected = false;

    this->window = nullptr;
}
void Game::initWindow() {
    this->videoMode = sf::VideoMode({800, 600});
        // Vector2u & Vector2f is just what SFML "3" requires when using number pairs.
        // Just pretend it only says "sf::setPosition(50, 50)" for clarity when you read it

        // nvm you can just use {x, y} instead rip

    this->window = new sf::RenderWindow(this->videoMode, "Snorke");
    this->window->setFramerateLimit(60);
}
//de/constructor stuffs
Game::Game() {
    // initialization
    this->initVars();
    this->initWindow();
    this->room = startRoom;

    // sprite loading
    if (!texture.loadFromFile("sawSheet.png")){
        std::cerr << "Failed to load";
    }
    rectSourceSprite = sf::IntRect({0,0},{100, 100});
    sprite = new sf::Sprite(texture, rectSourceSprite);

    // shape loading
    this->finalDoor.setPosition({0.f, 0.f});
    this->finalDoor.setSize({800.f, 20.f});
    this->finalDoor.setFillColor(sf::Color::Yellow);

    this->finalDoorBack.setPosition({0.f, 580.f});
    this->finalDoorBack.setSize({800.f, 580.f});
    this->finalDoorBack.setFillColor(sf::Color::Yellow);

    this->exitDoor.setPosition({300.f, 550.f});
    this->exitDoor.setSize({300.f, 50.f});
    this->exitDoor.setFillColor(sf::Color::White);
    this->exitDoor.setOutlineThickness(3);
    this->exitDoor.setOutlineColor(sf::Color::Yellow);

    for (int i = 0; i < 5; i++) {
        sf::CircleShape coin(15.f);
        coin.setFillColor(sf::Color::Yellow);
        coin.setOutlineThickness(4);
        coin.setOutlineColor({255,165,0});
        this->coins.push_back(coin);

        this->coinCheck.push_back(true);
    }

    // font stuff
    if (!gameFont.openFromFile("DFPOCOC.TTF")) {
        std::cerr << "Failed to load";
    }
    gameOverText = new sf::Text(gameFont);
    scoreText = new sf::Text(gameFont);
    winText = new sf::Text(gameFont);

    // game over text stuff
    gameOverText->setString(" Y O U    D I E D ");
    gameOverText->setCharacterSize(64);
    gameOverText->setFillColor(sf::Color::Red);
    gameOverText->setPosition({150.f, 300.f});

    // score text stuff
    scoreText->setCharacterSize(24);
    scoreText->setFillColor(sf::Color::White);
    scoreText->setPosition({680.f, 10.f});

    // win text
    winText->setString(" V I C T O R Y   A C H I E V E D ");
    winText->setCharacterSize(48);
    winText->setFillColor({255, 189, 0});
    winText->setPosition({10.f, 300.f});

}
Game::~Game() {
    delete this->window;
    delete sprite;  // blud almost caused a memory leak by not adding this
    delete gameOverText;
    delete scoreText;
    delete winText;
}


//  ~~~~~~~ functions ~~~~~~~

//checks if window is open/running
bool Game::running() {
    return this->window->isOpen();
    imageGeneratorLive();
}

void Game::pollEvents() {
    // check all the window's events that were triggered since the last iteration of the loop
    while (const std::optional event = this->window->pollEvent())
    {
        //sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);//tracking and printing mouse position for testing purposes
        //std::cout << "Mouse X: " << mousePos.x << " Y: " << mousePos.y << "\n";
        // "close requested" event: we close the window
        if (event->is<sf::Event::Closed>()) {
            this->window->close();
        }
        // close if escape key
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            this->window->close();
        }
    }
}

void Game::update() {

    // coordinate bounds for each thing on screen
    //          after making my own room, this stuff is pretty useless but oh well
    sf::FloatRect snakeBounds = this->snorke.getSnorkeBounds();
    sf::FloatRect spriteBounds = this->sprite->getGlobalBounds();
    sf::FloatRect doorToSecond({750.f, 500.f}, {50.f, 100.f});
    sf::FloatRect doorLeft({0.f,   380.f}, {25.f, 300.f});
    sf::FloatRect doorRight({775.f, 380.f}, {25.f, 295.f});
    sf::FloatRect door({0.f, 500.f}, {25.f, 100.f});


    this->pollEvents();

    // if game is over, close screen
    if (gameOver || gameWin) {
        sleep(sf::seconds(2));
        this->window->close();
        return;
    }


    // move snake
    this->snorke.update(this->window);

    // check if buzzsaw hit
    if (room == secondRoom) {
        if (!gameOver && snakeBounds.findIntersection(spriteBounds)) {
            gameOver = true;
        }
    }

    // check if exit unlocked
    if (snorke.getScore() == 5) {
        this->allCoinsCollected = true;
        if (room == thirdRoom) {
            if (!gameWin && snakeBounds.findIntersection(exitDoor.getGlobalBounds())) {
                gameWin = true;
            }
        }
    }

    // door collisions & loading
    switch (this->room ) {

        case(startRoom):

            if(snakeBounds.findIntersection(doorToSecond)) {
                float y = snakeBounds.position.y;
                snorke.teleportSnake({50.f, y});
                this->room = secondRoom;
                this->window->setSize({800, 600});
                //this->window->setTitle("Second Room");

            }

            // check if coins already taken/collided with
            if (coinCheck[0] == true) {
                if (snakeBounds.findIntersection(coins[0].getGlobalBounds())) {
                    snorke.scoreUp();
                    coinCheck[0] = false;
                }
            }
            break;

        case(secondRoom):

            if (snakeBounds.findIntersection(doorLeft)) {
                float y = snakeBounds.position.y;
                snorke.teleportSnake({720.f, y});
                this->room = startRoom;
                this->window->setSize({800, 600});
                //this->window->setTitle("First Room");
            }
            if (snakeBounds.findIntersection(doorRight)) {
                float y = snakeBounds.position.y;
                snorke.teleportSnake({40.f, y});
                this->room = thirdRoom;
                this->window->setSize({800, 600});
                //this->window->setTitle("Final Room");
            }


            // check if coins already taken/collided with
            if (coinCheck[1] == true) {
                if (snakeBounds.findIntersection(coins[1].getGlobalBounds())) {
                    snorke.scoreUp();
                    coinCheck[1] = false;
                }
            }
            break;

        case(thirdRoom):

            if (snakeBounds.findIntersection(door)) {
                float y = snakeBounds.position.y;
                snorke.teleportSnake({720.f, y});
                this->room = secondRoom;
                this->window->setSize(sf::Vector2u(800, 600));
                //this->window->setTitle("Second Room");
            }
            if (snakeBounds.findIntersection(finalDoor.getGlobalBounds())) {
                float x = snakeBounds.position.x;
                snorke.teleportSnake({x, 550.f});
                this->room = topRoom;
                this->window->setSize({800, 600});
                //this->window->setTitle("Final Room");
            }
            // check if coins already taken/collided with
            if (coinCheck[2] == true) {
                if (snakeBounds.findIntersection(coins[2].getGlobalBounds())) {
                    snorke.scoreUp();
                    coinCheck[2] = false;
                }
            }
            break;

        case(topRoom):

            if (snakeBounds.findIntersection(finalDoorBack.getGlobalBounds())) {
                float x = snakeBounds.position.x;
                snorke.teleportSnake({x, 20.f});
                this->room = thirdRoom;
                this->window->setSize({800, 600});
            }

            // check if coins already taken/collided with
            if (coinCheck[3] == true) {
                if (snakeBounds.findIntersection(coins[3].getGlobalBounds())) {
                    snorke.scoreUp();
                    coinCheck[3] = false;
                }
            }
            // check if coins already taken/collided with
            if (coinCheck[4] == true) {
                if (snakeBounds.findIntersection(coins[4].getGlobalBounds())) {
                    snorke.scoreUp();
                    coinCheck[4] = false;
                }
            }
            break;
    }

    // increase score
    scoreText->setString("Score: " + std::to_string(snorke.getScore()));

    imageGeneratorLive();
}
// renders game stuff
void Game::render() {

    this->window->clear(); // clears screen (no it doesnt DT clearing the screen is a myth)
                            // shhh don't let them know that Charlemagne

    switch (this->room) {

        case startRoom: {

            this->snorke.render(this->window);

            sf::RectangleShape rectangle({50,100});
            rectangle.setPosition({750,500});
            rectangle.setFillColor(sf::Color::Green);
            rectangle.setOutlineThickness(3);
            rectangle.setOutlineColor(sf::Color::Blue);
            this->window->draw(rectangle);

            // check if coin already taken, display if not
            if (coinCheck[0] == true) {
                this->coins[0].setPosition({100.f, 400.f});
                this->window->draw(this->coins[0]);
            }
            break;
        }
        case secondRoom: {

            this->window->draw(*sprite);
            sprite->setPosition({300,300});

            this->snorke.render(this->window);

            sf::RectangleShape rectangle({25,300});
            rectangle.setPosition({0,380});
            rectangle.setFillColor(sf::Color::Green);
            rectangle.setOutlineThickness(-3);
            rectangle.setOutlineColor(sf::Color::Blue);
            this->window->draw(rectangle);

            sf::RectangleShape rectangle2({25,295});
            rectangle2.setPosition({775,380});
            rectangle2.setFillColor(sf::Color::Green);
            rectangle2.setOutlineThickness(-3);
            rectangle2.setOutlineColor(sf::Color::Blue);
            this->window->draw(rectangle2);

            // check if coin already taken, display if not
            if (coinCheck[1] == true) {
                this->coins[1].setPosition({400.f, 30.f});
                this->window->draw(this->coins[1]);
            }
            break;

        }
        case thirdRoom: {
            this->snorke.render(this->window);
            sf::RectangleShape rectangle2({25,100});
            rectangle2.setPosition({0,500});
            rectangle2.setFillColor(sf::Color::Green);
            rectangle2.setOutlineThickness(-3);
            rectangle2.setOutlineColor(sf::Color::Blue);
            this->window->draw(rectangle2);
            this->window->draw(finalDoor);

            // exit door if all coins collected
            if (allCoinsCollected == true) {
                this->window->draw(exitDoor);
            }

            // check if coin already taken, display if not
            if (coinCheck[2] == true) {
                this->coins[2].setPosition({700.f, 60.f});
                this->window->draw(this->coins[2]);
            }

            break;
        }
        case topRoom: {
            this->window->draw(finalDoorBack);

            // check if coin already taken, display if not
            if (coinCheck[3] == true) {
                this->coins[3].setPosition({200.f, 300.f});
                this->window->draw(this->coins[3]);
            }
            // check if coin already taken, display if not
            if (coinCheck[4] == true) {
                this->coins[4].setPosition({600.f, 300.f});
                this->window->draw(this->coins[4]);
            }
            this->snorke.render(this->window);

            break;
        }
    }

    this->window->draw(*scoreText);

    // check if gameover to draw text
    if (gameOver) {
        this->window->draw(*gameOverText);
    }

    if (gameWin) {
        this->window->draw(*winText);
    }

    //this->window->draw(sprite);
    this->window->display();
}

void Game::imageGeneratorLive() {
    if (clock.getElapsedTime().asSeconds() > 0.1f) {
        if (rectSourceSprite.position.x == 200) {
            rectSourceSprite.position.x = 0;
        } else {
            rectSourceSprite.position.x += 100;
        }
        sprite->setTextureRect(rectSourceSprite);
        clock.restart();
    }
}

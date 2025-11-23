//
// Created by DT on 11/16/25.
//

#include "Game.h"

#include <iostream>

//private functions
void Game::initVars() {
    this->endGame = false;
    this->window = nullptr;
}
void Game::initWindow() {
    this->videoMode = sf::VideoMode({800, 600});
        // Vector2u & Vector2f is just what SFML "3" requires when using number pairs.
        // Just pretend it only says "sf::setPosition(50, 50)" for clarity when you read it

        // nvm you can just use {x, y} instead fml

    this->window = new sf::RenderWindow(this->videoMode, "First Room");
    this->window->setFramerateLimit(60);
}
//de/constructor stuffs
Game::Game() {
    this->initVars();
    this->initWindow();
    this->room = startRoom;

    if (!texture.loadFromFile("sawSheet.png")){
        std::cerr << "Failed to load";
    }
    rectSourceSprite = sf::IntRect({0,0},{100, 100});
    sprite = new sf::Sprite(texture, rectSourceSprite);
}
Game::~Game() {
    delete this->window;

    delete sprite;  // blud almost caused a memory leak by not adding this
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
    this->pollEvents();

    imageGeneratorLive();

    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
    bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    bool clickedThisFrame = (mousePressed && !mouseWasPressed);
    mouseWasPressed = mousePressed;

    sf::FloatRect snakeBounds = this->snorke.getSnorkeBounds();
    sf::FloatRect doorToSecond({750.f, 500.f}, {50.f, 100.f});
    sf::FloatRect doorLeft({0.f,   380.f}, {25.f, 300.f});
    sf::FloatRect doorRight({775.f, 380.f}, {25.f, 295.f});
    sf::FloatRect door({0.f, 500.f}, {25.f, 100.f});

    switch (this->room ) {

        case(startRoom):

            if(snakeBounds.findIntersection(doorToSecond)) {
                snorke.teleportSnake({50.f, 400.f});
                this->room = secondRoom;
                this->window->setSize({800, 600});
                this->window->setTitle("Second Room");

            }
            break;

        case(secondRoom):

            if (snakeBounds.findIntersection(doorLeft)) {
                snorke.teleportSnake({750.f, 400.f});
                this->room = startRoom;
                this->window->setSize({800, 600});
                this->window->setTitle("First Room");
            }
            if (snakeBounds.findIntersection(doorRight)) {
                snorke.teleportSnake({50.f, 400.f});
                this->room = thirdRoom;
                this->window->setSize({800, 600});
                this->window->setTitle("Final Room");
            }
            break;

        case(thirdRoom):

            if (snakeBounds.findIntersection(door)) {
                snorke.teleportSnake({750.f, 400.f});
                this->room = secondRoom;
                this->window->setSize(sf::Vector2u(800, 600));
                this->window->setTitle("Im a snake");
            }
            break;
    }
    this->snorke.update(this->window);

    imageGeneratorLive();
}
// renders game stuff
void Game::render() {
    this->window->clear(); // clears screen (no it doesnt DT clearing the screen is a myth)
                            // shhh don't let them know that Charlie
    switch (this->room) {

        case startRoom: {

            this->snorke.render(this->window);

            sf::RectangleShape rectangle({50,100});
            rectangle.setPosition({750,500});
            rectangle.setFillColor(sf::Color::Green);
            rectangle.setOutlineThickness(3);
            rectangle.setOutlineColor(sf::Color::Blue);
            this->window->draw(rectangle);
            break;
        }
        case secondRoom: {
            this->snorke.render(this->window);
            this->window->draw(*sprite);
            sprite->setPosition({300,300});

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
            break;

        }
        case thirdRoom:
            this->snorke.render(this->window);
            sf::RectangleShape rectangle2({25,100});
            rectangle2.setPosition({0,500});
            rectangle2.setFillColor(sf::Color::Green);
            rectangle2.setOutlineThickness(-3);
            rectangle2.setOutlineColor(sf::Color::Blue);
            this->window->draw(rectangle2);
            break;
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

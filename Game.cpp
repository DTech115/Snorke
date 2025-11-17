//
// Created by DT on 11/16/25.
//

#include "Game.h"

//private functions
void Game::initVars() {
    this->endGame = false;
    this->window = nullptr;
}
void Game::initWindow() {
    this->videoMode = sf::VideoMode(sf::Vector2u(800, 600));
    this->window = new sf::RenderWindow(this->videoMode, "Smough Gaming");

    this->window->setFramerateLimit(60);
}
//de/constructor stuffs
Game::Game() {
    this->initVars();
    this->initWindow();
}
Game::~Game() {
    delete this->window;
}


//  ~~~~~~~ functions ~~~~~~~

//checks if window is open/running
bool Game::running() {
    return this->window->isOpen();
}

void Game::pollEvents() {
    // check all the window's events that were triggered since the last iteration of the loop
    while (const std::optional event = this->window->pollEvent())
    {
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
}
// renders game stuff
void Game::render() {
    // clear the window
    this->window->clear();

    // draw everything here...
    this->snorke.render(this->window);  // uses player class's render method to take in window for rendering
    //this->window->draw(sprite);

    // show everything
    this->window->display();
}


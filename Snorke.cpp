//
// Created by DT on 11/17/25.
//

#include "Snorke.h"


void Snorke::initVariables() {
    this->movementSpeed = 10.f;
}
void Snorke::initSnake() {
    this->snake.setPosition(sf::Vector2f(400.f, 300.f));
    this->snake.setSize(sf::Vector2f(50.f, 50.f));
    this->snake.setFillColor(sf::Color::Green);
}

Snorke::Snorke(float x, float y) {
    this->snake.setPosition(sf::Vector2f(x, y));
    this->initVariables();
    this->initSnake();
}

Snorke::~Snorke() {

}

// moves player every time a key is pressed in one of four directions
void Snorke::updateInput() {
    // keyboard
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        this->snake.move(sf::Vector2f(-this->movementSpeed, 0.f));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        this->snake.move(sf::Vector2f(this->movementSpeed, 0.f));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        this->snake.move(sf::Vector2f(0.f, -this->movementSpeed));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        this->snake.move(sf::Vector2f(0.f, this->movementSpeed));
    }
}

// checks if player hits the sides of the screen
    // stops you from moving for now, will change rooms eventually
void Snorke::updateWindowCollision(sf::RenderTarget* targetWindow) {

    // position refers to x/y coordinate of the square
    // size refers to the x/y length of the square
    sf::FloatRect bounds = this->snake.getGlobalBounds();

    // checks if the snake's x position is less than the left side of screen
    if (bounds.position.x <= 0.f) {
        this->snake.setPosition(sf::Vector2f(0.f, bounds.position.y));
    }
    // right side
    else if (bounds.position.x + bounds.size.x >= targetWindow->getSize().x) {
        this->snake.setPosition(sf::Vector2f(targetWindow->getSize().x - bounds.size.x, bounds.position.y));
    }
    bounds = this->snake.getGlobalBounds();
    // top
    if (bounds.position.y <= 0.f) {
        this->snake.setPosition(sf::Vector2f(bounds.position.x, 0.f));
    }
    // bottom
    else if (bounds.position.y + bounds.size.y >= targetWindow->getSize().y) {
        this->snake.setPosition(sf::Vector2f(bounds.position.x, targetWindow->getSize().y - bounds.size.y));
    }
}

// updates the given window every frame by calling the other two updates
void Snorke::update(sf::RenderTarget* targetWindow) {
    this->updateInput();
    this->updateWindowCollision(targetWindow);
}

// draws everything to the screen
void Snorke::render(sf::RenderTarget* targetWindow) {
    targetWindow->draw(this->snake);
}
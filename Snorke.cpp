//
// Created by DT on 11/17/25.
//

#include "Snorke.h"


void Snorke::initVariables() {
    this->movementSpeed = 10.f;
}
void Snorke::initSnake() {
    this->snake.setSize(sf::Vector2f(50.f, 50.f));
    this->snake.setPosition(sf::Vector2f(100.f, 100.f));
    this->snake.setFillColor(sf::Color::Green);
}

Snorke::Snorke(float x, float y) {

    this->snake.setPosition(sf::Vector2f(x, y));

    this->initVariables();
    this->initSnake();
}

Snorke::~Snorke() {

}

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
void Snorke::updateWindowCollision(sf::RenderTarget* targetWindow) {
    // collisions :skull:
    sf::FloatRect bounds = this->snake.getGlobalBounds();

    //checks if the snake's x position is less than the left side of screen
    if (bounds.position.x <= 0.f) {
        this->snake.setPosition(sf::Vector2f(0.f, bounds.position.y));
    }
    else if (bounds.position.x + bounds.size.x >= targetWindow->getSize().x) {
        this->snake.setPosition(sf::Vector2f(targetWindow->getSize().x - bounds.size.x, bounds.position.y));
    }
}
void Snorke::update(sf::RenderTarget* targetWindow) {

    this->updateWindowCollision(targetWindow);

    this->updateInput();
}
void Snorke::render(sf::RenderTarget* targetWindow) {
    targetWindow->draw(this->snake);
}
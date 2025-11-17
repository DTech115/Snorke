//
// Created by DT on 11/17/25.
//

#include "Snorke.h"


void Snorke::initVariables() {

}
void Snorke::initSnake() {
    this->snake.setSize(sf::Vector2f(50.f, 50.f));
    this->snake.setPosition(sf::Vector2f(100.f, 100.f));
    this->snake.setFillColor(sf::Color::Green);
}

Snorke::Snorke() {
    this->initSnake();
}

Snorke::~Snorke() {

}

void Snorke::update() {

}
void Snorke::render(sf::RenderTarget* targetWindow) {
    targetWindow->draw(this->snake);
}
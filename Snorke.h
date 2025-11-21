//
// Created by DT on 11/17/25.
//

#ifndef SNORKE_H
#define SNORKE_H
#include <SFML/Graphics.hpp>


class Snorke {
private:

	//snake parts
	sf::RectangleShape snake;
	std::vector<sf::RectangleShape> body;
	std::vector<sf::Vector2f> bodyHistory;
	sf::Vector2f lastSnakePosition;

	float movementSpeed;

	void initVariables();
	void initSnake();

public:
	Snorke(float x = 0.f, float y = 0.f);
	~Snorke();

	void updateInput();
	void updateWindowCollision(sf::RenderTarget* targetWindow);
	void updateSnakeMovement();
	void update(sf::RenderTarget* targetWindow);
	void render(sf::RenderTarget* targetWindow);
};



#endif //SNORKE_H
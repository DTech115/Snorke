//
// Created by DT on 11/17/25.
//

#ifndef SNORKE_H
#define SNORKE_H
#include <SFML/Graphics.hpp>


class Snorke {
private:
	sf::RectangleShape snake;
	float movementSpeed;

	void initVariables();
	void initSnake();

public:
	Snorke(float x = 0.f, float y = 0.f);
	~Snorke();

	void updateInput();
	void update();
	void render(sf::RenderTarget* targetWindow);
};



#endif //SNORKE_H
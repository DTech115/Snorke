//
// Created by DT on 11/17/25.
//

#ifndef SNORKE_H
#define SNORKE_H
#include <SFML/Graphics.hpp>


class Snorke {
private:
	sf::RectangleShape snake;

	void initVariables();
	void initSnake();

public:
	Snorke();
	~Snorke();

	void update();
	void render(sf::RenderTarget* targetWindow);
};



#endif //SNORKE_H
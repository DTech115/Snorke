#include <SFML/Graphics.hpp>

int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML works!");

    //create the stuff
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    sf::Texture texture("smough.png");
    sf::Sprite sprite(texture);

    sprite.setScale({0.2f, 0.2f});
    // it's so peak...

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // clear the window with black color
        window.clear();

        // draw everything here...
        // window.draw(...);
        window.draw(sprite);
        // end the current frame
        window.display();
    }

    return 0;
}
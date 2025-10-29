#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Show Image");

    sf::Texture texture;
    if (!texture.loadFromFile("sprites/sprite.png")) {
        std::cerr << "Error: could not load image\n";
        return -1;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(30, 20); // optional: move image

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }

    return 0;
}

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game window");
    window.setFramerateLimit(60);


    // Four walls: top, bottom, left, right
    sf::RectangleShape topWall, bottomWall, leftWall, rightWall;

    sf::RectangleShape box;

    // vector2U size is gewoon de width en height van lijn 5 (window)
    auto updateWalls = [&](sf::Vector2u size)// size = (800, 600)
    {
        float w = static_cast<float>(size.x); // w = 800
        float h = static_cast<float>(size.y); // h = 600

        const float wallThicknessw = w * 0.04;
        const float wallThicknessh = h * 0.04;


        // Top wall
        topWall.setSize({w, wallThicknessh}); // w is de lengte van de rectangle daarom dus breedte van window
        topWall.setPosition(0, 0);

        // Bottom wall
        bottomWall.setSize({w, wallThicknessh});
        bottomWall.setPosition(0, h - wallThicknessh); // h is de lengte van de window

        // Left wall
        leftWall.setSize({wallThicknessw, h});
        leftWall.setPosition(0, 0);

        // Right wall
        rightWall.setSize({wallThicknessw, h});
        rightWall.setPosition(w - wallThicknessw, 0);

        // Set color
        sf::Color wallColor(55, 55, 155);
        topWall.setFillColor(wallColor);
        bottomWall.setFillColor(wallColor);
        leftWall.setFillColor(wallColor);
        rightWall.setFillColor(wallColor);

        // 🟦 Center Box (scales with window)
        float boxWidth = w * 0.2f;   // 20% of window width
        float boxHeight = h * 0.2f;  // 20% of window height
        box.setSize({boxWidth, boxHeight});

        // Center it
        box.setPosition((w - boxWidth) / 2.f, (h - boxHeight) / 2.f);

        box.setFillColor(sf::Color(255, 150, 50));
    };

    // gebruik de lambda functie
    updateWalls(window.getSize()); // Initialize

    while (window.isOpen())
    {
        // event zijn dingen dat gebeuren met de window elke frame
        sf::Event event;

        // pollevent checkt of er iets is gebeurd van input of verandering als er iets is gebeurd true anders false
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                // Update the view to avoid stretching
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));

                // Recalculate wall positions/sizes
                updateWalls({event.size.width, event.size.height});
            }
        }

        window.clear(sf::Color(30, 30, 30));
        window.draw(topWall);
        window.draw(bottomWall);
        window.draw(leftWall);
        window.draw(rightWall);
        window.draw(box);
        window.display();
    }

    return 0;
}
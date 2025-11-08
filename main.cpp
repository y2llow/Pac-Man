#include <SFML/Graphics.hpp>
#include "representation/include/Game.h"

int main(){
    // Program entry point.
    Game game; // Creating our game object.
    while(!game.GetWindow().IsDone()){
        // Game loop.

        // game.HandleInput();
        game.Update();
        game.Render();

    }
    return 0;
}





































// #include <fstream>
// #include <SFML/Graphics.hpp>
// #include <vector>
// #include <cmath>
//
// bool checkCollision(const sf::CircleShape& player, const std::vector<sf::RectangleShape>& walls) {
//     for (const auto& wall : walls) {
//         // Get the closest point on the wall to the center of the player
//         float playerCenterX = player.getPosition().x + player.getRadius();
//         float playerCenterY = player.getPosition().y + player.getRadius();
//
//         float wallLeft = wall.getPosition().x;
//         float wallTop = wall.getPosition().y;
//         float wallRight = wall.getPosition().x + wall.getSize().x;
//         float wallBottom = wall.getPosition().y + wall.getSize().y;
//
//         // Find the closest point on the wall to the player's center
//         float closestX = std::clamp(playerCenterX, wallLeft, wallRight);
//         float closestY = std::clamp(playerCenterY, wallTop, wallBottom);
//
//         // Calculate the distance from the player's center to the closest point
//         float distanceX = playerCenterX - closestX;
//         float distanceY = playerCenterY - closestY;
//
//         // If the distance is less than the player's radius, there's a collision
//         float distanceSquared = distanceX * distanceX + distanceY * distanceY;
//         if (distanceSquared < player.getRadius() * player.getRadius()) {
//             return true; // Collision detected
//         }
//     }
//
//     return false; // No collision
// }
//
// int main() {
//     sf::RenderWindow window(sf::VideoMode(800, 440), "Game window");
//     window.setFramerateLimit(60);
//     const float speed = 200.f; // pixels per second
//     sf::Clock clock; // for delta time (smooth movement)
//
//     // Initialize map from file
//     std::ifstream file("map.txt");
//     std::string line;
//     std::vector<std::string> maze;
//     while (std::getline(file, line))
//         maze.push_back(line);
//
//     // Create walls vector
//     std::vector<sf::RectangleShape> walls;
//     std::vector<sf::CircleShape> characters;
//     sf::CircleShape player({20});
//     const float tileSize = 40.f;
//
//     for (unsigned int y = 0; y < maze.size(); y++) {
//         for (unsigned int x = 0; x < maze[y].size(); x++) {
//             if (maze[y][x] == 'x') {
//                 sf::RectangleShape wall({tileSize-5, tileSize-5});
//                 wall.setPosition(x * tileSize, y * tileSize);
//                 wall.setFillColor(sf::Color::Blue);
//                 walls.push_back(wall);
//             }
//             if (maze[y][x] == 'p') {
//                 player.setPosition(x * tileSize, y * tileSize);
//                 player.setFillColor(sf::Color::Yellow);
//             }
//             if (maze[y][x] == 'g') {
//                 sf::CircleShape character({20});
//                 character.setPosition(x * tileSize, y * tileSize);
//                 character.setFillColor(sf::Color::Red);
//                 characters.push_back(character);
//             }
//             if (maze[y][x] == 'h') {
//                 sf::CircleShape character({20});
//                 character.setPosition(x * tileSize, y * tileSize);
//                 character.setFillColor(sf::Color::Cyan);
//                 characters.push_back(character);
//             }
//             if (maze[y][x] == 'j') {
//                 sf::CircleShape character({20});
//                 character.setPosition(x * tileSize, y * tileSize);
//                 character.setFillColor(sf::Color::Magenta);
//                 characters.push_back(character);
//             }
//             if (maze[y][x] == 'k') {
//                 sf::CircleShape character({20});
//                 character.setPosition(x * tileSize, y * tileSize);
//                 character.setFillColor(sf::Color::Green);
//                 characters.push_back(character);
//             }
//         }
//     }
//
//     // Four walls: top, bottom, left, right
//     sf::RectangleShape topWall, bottomWall, leftWall, rightWall;
//
//     sf::RectangleShape box;
//
//     // Update walls
//     auto updateWalls = [&](sf::Vector2u size) {
//         float w = static_cast<float>(size.x);
//         float h = static_cast<float>(size.y);
//
//         const float wallThicknessw = w * 0.04;
//         const float wallThicknessh = h * 0.04;
//
//         topWall.setSize({w, wallThicknessh});
//         topWall.setPosition(0, 0);
//         bottomWall.setSize({w, wallThicknessh});
//         bottomWall.setPosition(0, h - wallThicknessh);
//         leftWall.setSize({wallThicknessw, h});
//         leftWall.setPosition(0, 0);
//         rightWall.setSize({wallThicknessw, h});
//         rightWall.setPosition(w - wallThicknessw, 0);
//
//         sf::Color wallColor(55, 55, 155);
//         topWall.setFillColor(wallColor);
//         bottomWall.setFillColor(wallColor);
//         leftWall.setFillColor(wallColor);
//         rightWall.setFillColor(wallColor);
//
//         float boxWidth = w * 0.2f;
//         float boxHeight = h * 0.2f;
//         box.setSize({boxWidth, boxHeight});
//         box.setPosition((w - boxWidth) / 2.f, (h - boxHeight) / 2.f);
//         box.setFillColor(sf::Color(255, 150, 50));
//     };
//
//     updateWalls(window.getSize()); // Initialize walls
//
//     while (window.isOpen()) {
//         sf::Event event;
//
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }
//
//         float deltaTime = clock.restart().asSeconds();
//
//         // Movement input
//         sf::Vector2f movement(0.f, 0.f);
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
//             sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//             movement.y -= speed * deltaTime;
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
//             sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//             movement.y += speed * deltaTime;
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
//             sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//             movement.x -= speed * deltaTime;
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
//             sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//             movement.x += speed * deltaTime;
//
//         // Check if the new position collides with any walls
//         sf::CircleShape tempPlayer = player;
//         tempPlayer.move(movement);
//
//         if (!checkCollision(tempPlayer, walls)) {
//             player.move(movement); // Apply movement if no collision
//         }
//
//         window.clear(sf::Color(30, 30, 30));
//         for (auto& w : walls)
//             window.draw(w);
//         for (auto& c : characters)
//             window.draw(c);
//
//         window.draw(player);
//         window.display();
//     }
//
//     return 0;
// }

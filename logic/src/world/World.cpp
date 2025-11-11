#include "world/World.h"
#include "entities/WallModel.h"
#include "entities/CoinModel.h"
#include <iostream>

World::World(const sf::Vector2u& windowSize, LogicFactory& factory)
    : m_factory(&factory), m_windowSize(windowSize) {
    m_score = std::make_unique<Score>();
}

void World::initialize() {
    // Load map and create entities
    if (m_mapModel.loadFromFile("assets/maps/map2.txt")) {
        createEntitiesFromMap();
    }
}

void World::createEntitiesFromMap() {
    const auto& grid = m_mapModel.getGrid();
    sf::Vector2u gridSize = m_mapModel.getGridSize();

    if (grid.empty()) return;

    float tileWidth = 2.0f / gridSize.x;
    float tileHeight = 2.0f / gridSize.y;

    for (unsigned int y = 0; y < gridSize.y; ++y) {
        for (unsigned int x = 0; x < gridSize.x; ++x) {
            if (grid[y][x] == 'x') {
                float posX = -1.0f + (x * tileWidth) + (tileWidth / 2.0f);
                float posY = -1.0f + (y * tileHeight) + (tileHeight / 2.0f);

                auto wall = m_factory->createWall(
                    sf::Vector2f(posX, posY),
                    sf::Vector2f(tileWidth * 0.9f, tileHeight * 0.9f),
                    "wall_basic"
                );
                m_walls.push_back(std::move(wall));
            }
            else if (grid[y][x] == '.') {
                float posX = -1.0f + (x * tileWidth) + (tileWidth / 2.0f);
                float posY = -1.0f + (y * tileHeight) + (tileHeight / 2.0f);

                auto coin = m_factory->createCoin(
                    sf::Vector2f(posX, posY),
                    sf::Vector2f(tileWidth * 0.9f, tileHeight * 0.9f),
                    "Coin"
                );
                m_coins.push_back(std::move(coin));
            }
            else if (grid[y][x] == 'P') {
                float posX = -1.0f + (x * tileWidth) + (tileWidth / 2.0f);
                float posY = -1.0f + (y * tileHeight) + (tileHeight / 2.0f);

                auto pacman = m_factory->createPacman(
                    sf::Vector2f(posX, posY),
                    sf::Vector2f(tileWidth * 0.9f, tileHeight * 0.9f),
                    "Pacman");

                m_pacman.push_back(std::move(pacman));
            }
        }
    }
    //TODO remove
    std::cout << "World: Created " << m_walls.size() << " walls and " << m_coins.size() << " coins" << std::endl;
}

void World::addEntity(std::unique_ptr<EntityModel> entity) {
    // For dynamic entity creation later
}

void World::update(float deltaTime) {
    // Update all entities
    for (auto& wall : m_walls) {
        wall->update(deltaTime);
    }
    for (auto& coin : m_coins) {
        coin->update(deltaTime);
    }

}


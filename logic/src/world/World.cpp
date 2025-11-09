#include "world/World.h"
#include "../../include/entities/WallModel.h"

World::World(const sf::Vector2u& windowSize, LogicFactory& factory)
    : m_factory(&factory) {
}

void World::createEntitiesFromMap() {
    // Use factory to create walls and coins
    const auto& grid = m_mapModel.getGrid();

    for (unsigned int y = 0; y < grid.size(); ++y) {
        for (unsigned int x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == '#') {
                // Calculate position and create wall using factory
                auto wall = m_factory->createWall(calculatePosition(x, y), calculateSize());
                m_walls.push_back(std::move(wall));
            }
            else if (grid[y][x] == '.') {
                // Create coin using factory
                auto coin = m_factory->createCoin(calculatePosition(x, y), calculateSize(), "coin");
                m_coins.push_back(std::move(coin));
            }
        }
    }
}
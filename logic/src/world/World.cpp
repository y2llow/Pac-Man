#include "world/World.h"
#include "entities/StaticEntity_collectibles/WallModel.h"
#include "entities/EntityModel.h"
#include <iostream>

World::World(const sf::Vector2u& windowSize)
    : m_windowSize(windowSize) {
}

World::~World() {
}

bool World::initialize() {
    if (!m_mapModel.loadFromFile("assets/maps/map.txt")) {
        return false;
    }
    return true;
}


bool World::isCollisionWithWalls(const sf::Vector2f& position, const sf::Vector2f& size) const {
    const auto& walls = getWalls(); // Duidelijk dat we alleen walls checken

    for (const auto& wall : walls) {
        sf::Vector2f entityPos = wall->getPosition();
        sf::Vector2f entitySize = wall->getSize();

        bool collisionX = position.x + size.x > entityPos.x &&
                         entityPos.x + entitySize.x > position.x;
        bool collisionY = position.y + size.y > entityPos.y &&
                         entityPos.y + entitySize.y > position.y;

        if (collisionX && collisionY) {
            return true;
        }
    }
    return false;
}

void World::update(float deltaTime) {
    // Update alleen walls voor nu
    const auto& walls = getWalls();
    for (const auto& wall : walls) {
        wall->update(deltaTime);
    }
}
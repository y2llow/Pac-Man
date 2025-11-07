#include "world/World.h"
#include "entities/StaticEntity_collectibles/WallModel.h"
#include "entities/EntityModel.h"
#include <iostream>

World::World(const sf::Vector2u& windowSize)
    : m_windowSize(windowSize) {
}

World::~World() {
    clearEntities();
}

bool World::initialize() {
    if (!m_mapModel.loadFromFile("assets/maps/map.txt")) {
        return false;
    }

    addEntitiesFromMap();
    return true;
}

void World::addEntitiesFromMap() {
    clearEntities(); // Clear any existing entities

    // Add all walls from the map to our entity list
    const auto& walls = m_mapModel.getWalls();
    for (const auto& wall : walls) {
        m_entities.push_back(wall.get()); // Store raw pointer
    }

    //TODO delete this
    std::cout << "World initialized with " << m_entities.size() << " entities" << std::endl;
}

void World::clearEntities() {
    m_entities.clear(); // Just clear pointers, unique_ptrs in MapModel handle deletion
}

bool World::isCollision(const sf::Vector2f& position, const sf::Vector2f& size) const {
    for (const auto& entity : m_entities) {
        sf::Vector2f entityPos = entity->getPosition();
        sf::Vector2f entitySize = entity->getSize();

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
    for (const auto& entity : m_entities) {
        entity->update(deltaTime);
    }
}
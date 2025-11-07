#include "world/World.h"

World::World(const sf::Vector2u& windowSize)
    : m_windowSize(windowSize) {
}

bool World::initialize() {
    // Load the map - this is LOGIC only
    if (!m_mapModel.loadFromFile("map.txt")) {
        return false;
    }
    return true;
}

bool World::isCollision(const sf::Vector2f& position) const {
    return m_mapModel.isWall(position);
}

void World::update(float deltaTime) {
    // Update game logic here
    // We'll add entity updates later
}

// REMOVE the render() method completely from World class!
// Rendering should happen in the representation layer
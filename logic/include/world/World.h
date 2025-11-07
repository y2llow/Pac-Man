#ifndef WORLD_H
#define WORLD_H

#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>
#include "MapModel.h"
#include "entities/EntityModel.h"

// Forward declarations
class Entity;

class World {
public:
    World(const sf::Vector2u& windowSize);
    ~World(); // Add destructor
    bool initialize();
    void update(float deltaTime);

    // Entity management
    const std::vector<Entity*>& getEntities() const { return m_entities; }
    const MapModel& getMapModel() const { return m_mapModel; }

    // Collision detection
    bool isCollision(const sf::Vector2f& position, const sf::Vector2f& size) const;

private:
    MapModel m_mapModel;
    sf::Vector2u m_windowSize;
    std::vector<Entity*> m_entities; // Use raw pointers for now

    void addEntitiesFromMap();
    void clearEntities();
};

#endif
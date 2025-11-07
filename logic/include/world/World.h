#ifndef WORLD_H
#define WORLD_H

#include <SFML/System/Vector2.hpp>
#include "MapModel.h"

class World {
public:
    World(const sf::Vector2u& windowSize);
    bool initialize();
    void update(float deltaTime);

    // Pure logic methods - no rendering!
    bool isCollision(const sf::Vector2f& position) const;
    const MapModel& getMapModel() const { return m_mapModel; } // Allow access to map data

private:
    MapModel m_mapModel;
    sf::Vector2u m_windowSize;
};

#endif
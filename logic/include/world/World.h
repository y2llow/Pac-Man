#ifndef WORLD_H
#define WORLD_H

#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>
#include "MapModel.h"
#include "patterns/AbstractFactory.h"

class World {
public:
    World(const sf::Vector2u& windowSize, LogicFactory& factory);

    void setFactory(LogicFactory& factory) { m_factory = &factory; }
    void createEntitiesFromMap(); // Use factory to create entities

private:
    MapModel m_mapModel;
    LogicFactory* m_factory; // World uses factory to create entities
    std::vector<std::unique_ptr<WallModel>> m_walls;
    std::vector<std::unique_ptr<CoinModel>> m_coins;
};

#endif


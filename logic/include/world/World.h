#ifndef WORLD_H
#define WORLD_H

#include "MapModel.h"


#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>
#include "patterns/AbstractFactory.h"
#include "scoring/Score.h"
#include "entities/WallModel.h"
#include "entities/CoinModel.h"
#include "entities/PacmanModel.h"
#include "entities/GhostModel.h"
#include "entities/FruitModel.h"

class World {
public:
    World(const sf::Vector2u& windowSize, LogicFactory& factory);

    void initialize();
    void update(float deltaTime);

    void setFactory(LogicFactory& factory) { m_factory = &factory; }
    void createEntitiesFromMap();
    void addEntity(std::unique_ptr<EntityModel> entity);

    Score& getScore() { return *m_score; }

    // Add getters for LevelState to access entities for rendering
    [[nodiscard]] const std::vector<std::unique_ptr<WallModel>>& getWalls() const { return m_walls; }
    [[nodiscard]] const std::vector<std::unique_ptr<CoinModel>>& getCoins() const { return m_coins; }
    [[nodiscard]] const std::vector<std::unique_ptr<PacmanModel>>& getPacman() const { return m_pacman; }
    [[nodiscard]] const std::vector<std::unique_ptr<GhostModel>>& getGhosts() const { return m_ghosts; }
    [[nodiscard]] const std::vector<std::unique_ptr<FruitModel>>& getFruit() const { return m_fruits; }

private:
    MapModel m_mapModel;
    LogicFactory* m_factory;
    std::unique_ptr<Score> m_score;

    // World stores all entities
    std::vector<std::unique_ptr<WallModel>> m_walls;
    std::vector<std::unique_ptr<CoinModel>> m_coins;
    std::vector<std::unique_ptr<PacmanModel>> m_pacman;
    std::vector<std::unique_ptr<GhostModel>> m_ghosts;
    std::vector<std::unique_ptr<FruitModel>> m_fruits;

    sf::Vector2u m_windowSize;

};

#endif


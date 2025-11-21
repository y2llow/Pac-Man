#ifndef WORLD_H
#define WORLD_H

#include "MapModel.h"
#include "core/Stopwatch.h"


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
    World(const Vector2f& windowSize, LogicFactory& factory);

    void initialize();
    void update(float deltaTime);

    void handleCollisions();
    bool checkCollision(const PacmanModel& pacman, const EntityModel& entity2);

    void handlePacmanWallCollision(PacmanModel&pacman, const WallModel&wall);
    void handlePacmanGhostCollision(PacmanModel&pacman, GhostModel&ghost);
    void handlePacmanCoinCollision(CoinModel&coin);
    void handlePacmanFruitCollision(FruitModel&fruit);

    void cleanupCollectedItems();
    void checkGameState();

    void setFactory(LogicFactory& factory) { m_factory = &factory; }
    void createEntitiesFromMap();
    void addEntity(std::unique_ptr<EntityModel> entity);
    void handleResize(const Vector2f& newSize);



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

    Vector2f m_windowSize;

    float PACMAN_SIZE = 0.75;
    float GHOST_SIZE = 0.75;
    float COIN_SIZE = 0.125;
    float FRUIT_SIZE = 0.3;

};

#endif


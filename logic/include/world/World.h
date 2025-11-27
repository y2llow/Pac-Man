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
    explicit World(LogicFactory& factory);

    void initialize();
    void update(float deltaTime);

    Score& getScore() { return *m_score; }
    void setFactory(LogicFactory& factory) { m_factory = &factory; }
    void addEntity(std::unique_ptr<EntityModel> entity);

    static bool checkCollision(const PacmanModel& pacman, const EntityModel& entity2);
    void handlePacmanWallCollision(PacmanModel&pacman, const WallModel&wall);
    void handlePacmanGhostCollision(PacmanModel&pacman, GhostModel&ghost);
    void handlePacmanCoinCollision(CoinModel&coin);
    void handlePacmanFruitCollision(FruitModel&fruit);
    void cleanupCollectedItems();

    // Nieuwe predictive collision methodes
    bool wouldCollideWithWalls(const PacmanModel& pacman, const Vector2f& newPosition) const;
    void handlePredictiveMovement(float deltaTime);
    void handleCollectibleCollisions();
    bool areAllCoinsCollected() const { return m_coins.empty() && m_fruits.empty(); }
    void advanceToNextLevel();

    // Add getters for LevelState to access entities for rendering
    [[nodiscard]] const std::vector<std::shared_ptr<WallModel>>& getWalls() const { return m_walls; }
    [[nodiscard]] const std::vector<std::shared_ptr<CoinModel>>& getCoins() const { return m_coins; }
    [[nodiscard]] const std::vector<std::shared_ptr<GhostModel>>& getGhosts() const { return m_ghosts; }
    [[nodiscard]] const std::vector<std::shared_ptr<FruitModel>>& getFruit() const { return m_fruits; }
    [[nodiscard]] const std::shared_ptr<PacmanModel>& getPacman() const { return m_pacman; }
    [[nodiscard]] std::shared_ptr<Score> Getscore() const {return m_score;}


private:
    MapModel m_mapModel;
    LogicFactory* m_factory;
    std::shared_ptr<Score> m_score;

    // Change ALL vectors to shared_ptr
    std::vector<std::shared_ptr<WallModel>> m_walls;
    std::vector<std::shared_ptr<CoinModel>> m_coins;
    std::vector<std::shared_ptr<GhostModel>> m_ghosts;
    std::vector<std::shared_ptr<FruitModel>> m_fruits;
    std::shared_ptr<PacmanModel> m_pacman;


    Vector2f m_gridSize;

    float PACMAN_SIZE = 0.99;
    float GHOST_SIZE = 0.99;
    float COIN_SIZE = 0.15;
    float FRUIT_SIZE = 0.65;

    void createEntitiesFromMap();
    [[nodiscard]] Vector2f tryPositionCorrection(const Vector2f& currentPos,
                               int currentDir,
                               int bufferedDir,
                               float deltaTime) const;
    [[nodiscard]] Vector2f findClosestPositionToWall(const Vector2f& currentPos,
                                   int direction,
                                   float deltaTime) const;
    void checkDeathAnimationState();
};

#endif


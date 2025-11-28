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
#include "entities/DoorModel.h"

// Forward declarations for classes that don't need full definition
class LogicFactory;
class Vector2f;

class World {
public:
    explicit World(LogicFactory& factory);

    void initialize();
    void update(float deltaTime);

    Score& getScore() { return *m_score; }
    void setFactory(LogicFactory& factory) { m_factory = &factory; }

    // Template collision detection - works with any entity type
    template<typename T1, typename T2>
    static bool checkCollision(const T1& entity1, const T2& entity2);

    void handlePacmanGhostCollision(PacmanModel& pacman, GhostModel& ghost);
    void handlePacmanCoinCollision(CoinModel& coin);
    void handlePacmanFruitCollision(FruitModel& fruit);
    void cleanupCollectedItems();

    // Ghost movement
    void handleGhostMovement(const std::shared_ptr<GhostModel>& ghost, float deltaTime);


    // Nieuwe predictive collision methodes
    [[nodiscard]] bool wouldCollideWithWalls(const PacmanModel& pacman, const Vector2f& newPosition) const;
    void handlePredictiveMovement(float deltaTime);
    void handleCollectibleCollisions();
    [[nodiscard]] bool areAllCoinsCollected() const { return m_coins.empty() && m_fruits.empty(); }
    void advanceToNextLevel();

    // Add getters for LevelState to access entities for rendering
    [[nodiscard]] const std::vector<std::shared_ptr<WallModel>>& getWalls() const { return m_walls; }
    [[nodiscard]] const std::vector<std::shared_ptr<CoinModel>>& getCoins() const { return m_coins; }
    [[nodiscard]] const std::vector<std::shared_ptr<GhostModel>>& getGhosts() const { return m_ghosts; }
    [[nodiscard]] const std::vector<std::shared_ptr<FruitModel>>& getFruit() const { return m_fruits; }
    [[nodiscard]] const std::vector<std::shared_ptr<DoorModel>>& getDoors() const { return m_doors; }
    [[nodiscard]] const std::shared_ptr<PacmanModel>& getPacman() const { return m_pacman; }
    [[nodiscard]] std::shared_ptr<Score> Getscore() const {return m_score;}

    // Add this method to fix the LevelState error
    [[nodiscard]] int getCurrentLevel() const { return LEVEL; }

private:
    MapModel m_mapModel;
    LogicFactory* m_factory;
    std::shared_ptr<Score> m_score;

    // Entity storage
    std::vector<std::shared_ptr<WallModel>> m_walls;
    std::vector<std::shared_ptr<CoinModel>> m_coins;
    std::vector<std::shared_ptr<GhostModel>> m_ghosts;
    std::vector<std::shared_ptr<FruitModel>> m_fruits;
    std::vector<std::shared_ptr<DoorModel>> m_doors;
    std::shared_ptr<PacmanModel> m_pacman;

    Vector2f m_gridSize;
    Vector2f m_startPosition;

    float PACMAN_SIZE = 0.99f;
    float GHOST_SIZE = 0.99f;
    float COIN_SIZE = 0.15f;
    float FRUIT_SIZE = 0.65f;

    int LEVEL = 1;

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

template<typename T1, typename T2>
bool World::checkCollision(const T1& entity1, const T2& entity2) {
    // Get bounds for entity1
    float e1_left = entity1.getPosition().x - (entity1.getSize().x / 2);
    float e1_right = entity1.getPosition().x + (entity1.getSize().x / 2);
    float e1_bottom = entity1.getPosition().y - (entity1.getSize().y / 2);
    float e1_top = entity1.getPosition().y + (entity1.getSize().y / 2);

    // Get bounds for entity2
    float e2_left = entity2.getPosition().x - (entity2.getSize().x / 2);
    float e2_right = entity2.getPosition().x + (entity2.getSize().x / 2);
    float e2_bottom = entity2.getPosition().y - (entity2.getSize().y / 2);
    float e2_top = entity2.getPosition().y + (entity2.getSize().y / 2);

    // Correct AABB collision detection
    if (e1_right > e2_left &&
        e1_left < e2_right &&
        e1_top > e2_bottom &&
        e1_bottom < e2_top) {
        return true;  // Collision detected
    }

    return false;  // No collision
}

#endif
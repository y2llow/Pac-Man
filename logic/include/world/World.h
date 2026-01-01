#ifndef WORLD_H
#define WORLD_H

/**
 * @class World
 *
 * @brief
 * De World-klasse is het centrale model van de gamewereld.
 * Ze beheert alle entiteiten (Pac-Man, ghosts, walls, coins, fruits, deuren),
 * verwerkt beweging, collision detection, score-updates en levelprogressie.
 *
 * -------------------------
 * GEBRUIKTE DESIGN PATTERNS
 * -------------------------
 *
 * 1) ABSTRACT FACTORY
 *    - LogicFactory wordt gebruikt om entiteiten te creëren
 *      (Pacman, Ghosts, Walls, Coins, Fruits, Doors).
 *    - Hierdoor is World onafhankelijk van concrete implementaties.
 *
 * 2) OBSERVER
 *    - Score observeert CoinModel, FruitModel, GhostModel en PacmanModel.
 *    - World koppelt observers via attachScoreObservers().
 *
 * 3) MODEL-VIEW-SEPARATION (MVC-achtig)
 *    - World bevat enkel logica en data (Model).
 *    - Views worden extern beheerd via de factory.
 *
 * 4) STRATEGY (impliciet)
 *    - Verschillende ghost movement-methodes
 *      (Red, Blue, Pink, Scared, Standard) fungeren als strategieën.
 *
 * 5) TEMPLATE METHOD / GENERIC PROGRAMMING
 *    - checkCollision<T1, T2>() werkt voor alle entiteit-types.
 */

#include "MapModel.h"
#include "core/Stopwatch.h"

#include <memory>
#include <vector>

#include "patterns/AbstractFactory.h"
#include "scoring/Score.h"

// Entity models
#include "entities/WallModel.h"
#include "entities/CoinModel.h"
#include "entities/PacmanModel.h"
#include "entities/GhostModel.h"
#include "entities/FruitModel.h"
#include "entities/DoorModel.h"

// Forward declaration
namespace pacman::representation {
class Camera;
}
namespace pacman::logic::world {
// Import commonly used types from entities namespace
using entities::WallModel;
using entities::CoinModel;
using entities::PacmanModel;
using entities::GhostModel;
using entities::FruitModel;
using entities::DoorModel;

class World {
public:
    /**
     * Constructor
     * @param factory  Abstract factory voor het aanmaken van entiteiten
     * @param camera   Referentie naar de camera (voor consistentie met view-laag)
     */
    explicit World(patterns::LogicFactory& factory, representation::Camera& camera);

    /**
     * Initialiseert de wereld:
     * - Laadt de map
     * - Creëert entiteiten
     * - Koppelt score-observers
     */
    void initialize();

    /**
     * Hoofd update-loop van de wereld.
     * Wordt elke frame aangeroepen.
     *
     * @param deltaTime Tijd sinds vorige frame
     */
    void update(float deltaTime);

    /**
     * Koppelt observers tussen score en game-entiteiten.
     * (Observer pattern)
     */
    void attachScoreObservers();

    /// Geeft referentie naar score-object
    scoring::Score& getScore() { return *m_score; }

    /// Laat toe om factory te vervangen (bv. bij reset)
    void setFactory(patterns::LogicFactory& factory) { m_factory = &factory; }

    /**
     * Algemene AABB collision detection tussen twee entiteiten.
     * Werkt voor elk type met getPosition() en getSize().
     *
     * @return true als er overlap is
     */
    template<typename T1, typename T2>
    static bool checkCollision(const T1& entity1, const T2& entity2);

    /**
     * Detecteert tunneling bij snelle ghost-beweging.
     * Verplaatst ghost onmiddellijk indien nodig.
     */
    bool willTunnel(const std::shared_ptr<entities::GhostModel>& ghost, float deltaTime) const;

    /// Collision handlers
    void handlePacmanGhostCollision(entities::PacmanModel& pacman, entities::GhostModel& ghost);
    static void handlePacmanCoinCollision(entities::CoinModel& coin);
    void handlePacmanFruitCollision(entities::FruitModel& fruit);

    /// Verwijdert verzamelde coins en fruits
    void cleanupCollectedItems();

    // -----------------
    // COLLISION CHECKS
    // -----------------

    /// Controleert of een ghost tegen muren zou botsen
    [[nodiscard]] bool GhostWouldCollideWithWalls(const entities::GhostModel& ghost, const Vector2f& newPosition) const;
    [[nodiscard]] bool PacmanWouldCollideWithWalls(const entities::PacmanModel& pacman, const Vector2f& newPosition) const;


    // -----------------
    // GAME FLOW
    // -----------------

    /// Verwerkt Pac-Man beweging met buffering en correcties
    void handlePredictivePacmanMovement(float deltaTime);

    /// Verwerkt alle collisions met coins, fruits en ghosts
    void handleCollectibleCollisions();

    /// Controle of level klaar is
    [[nodiscard]] bool areAllCoinsCollected() const {
        return m_coins.empty() && m_fruits.empty();
    }

    /// Gaat naar het volgende level
    void advanceToNextLevel();

    // -----------------
    // GETTERS (voor rendering)
    // -----------------

    [[nodiscard]] const std::vector<std::shared_ptr<entities::WallModel>>& getWalls() const { return m_walls; }
    [[nodiscard]] const std::vector<std::shared_ptr<entities::CoinModel>>& getCoins() const { return m_coins; }
    [[nodiscard]] const std::vector<std::shared_ptr<entities::GhostModel>>& getGhosts() const { return m_ghosts; }
    [[nodiscard]] const std::vector<std::shared_ptr<entities::FruitModel>>& getFruit() const { return m_fruits; }
    [[nodiscard]] const std::vector<std::shared_ptr<entities::DoorModel>>& getDoors() const { return m_doors; }
    [[nodiscard]] const std::shared_ptr<entities::PacmanModel>& getPacman() const { return m_pacman; }
    [[nodiscard]] std::shared_ptr<scoring::Score> Getscore() const { return m_score; }
    [[nodiscard]] int getCurrentLevel() const { return LEVEL; }

    // -----------------
    // GHOST AI (Strategy)
    // -----------------

    void RedGhostMovement(const std::shared_ptr<entities::GhostModel>& ghost, float deltaTime);
    void BlueGhostMovement(const std::shared_ptr<entities::GhostModel>& ghost, float deltaTime);
    void PinkGhostMovement(const std::shared_ptr<entities::GhostModel>& ghost, float deltaTime);
    void ScaredGhostMovement(const std::shared_ptr<entities::GhostModel>& ghost, float deltaTime);
    void standardGhostMovement(const std::shared_ptr<entities::GhostModel>& ghost, float deltaTime);
    void TrappedGhostMovement(const std::shared_ptr<entities::GhostModel>& ghost, float deltaTime) ;

    /// Hulpfunctie voor Manhattan-afstand (ghost AI)
    static float getManhattanDistance(Vector2f ghostPos, Vector2f pacmanNextPos);

private:
    // -----------------
    // CORE DATA
    // -----------------

    MapModel m_mapModel;
    patterns::LogicFactory* m_factory;
    std::shared_ptr<scoring::Score> m_score;
    representation::Camera& m_camera;

    // -----------------
    // ENTITIES
    // -----------------

    std::vector<std::shared_ptr<entities::WallModel>> m_walls;
    std::vector<std::shared_ptr<entities::CoinModel>> m_coins;
    std::vector<std::shared_ptr<entities::GhostModel>> m_ghosts;
    std::vector<std::shared_ptr<entities::FruitModel>> m_fruits;
    std::vector<std::shared_ptr<entities::DoorModel>> m_doors;
    std::shared_ptr<entities::PacmanModel> m_pacman;

    // -----------------
    // CONFIG & STATE
    // -----------------

    Vector2f m_gridSize;
    Vector2f m_startPosition;

    float PACMAN_SIZE = 0.99f;
    float GHOST_SIZE  = 0.99f;
    float COIN_SIZE   = 0.15f;
    float FRUIT_SIZE  = 0.65f;

    int LEVEL = 1;

    // -----------------
    // INTERNAL HELPERS
    // -----------------

    /// Maakt entiteiten aan op basis van de map
    void createEntitiesFromMap();

    /// Probeert Pac-Man te corrigeren bij scherpe bochten
    [[nodiscard]] Vector2f tryPositionCorrection(
        const Vector2f& currentPos,
        int currentDir,
        int bufferedDir,
        float deltaTime) const;

    /// Zoekt dichtst mogelijke geldige positie tot muur (Pac-Man)
    [[nodiscard]] Vector2f findClosestPositionToWall(
        const Vector2f& currentPos,
        int direction,
        float deltaTime) const;

    /// Zelfde als hierboven maar voor ghosts
    [[nodiscard]] Vector2f findClosestPositionToWallForGhost(const Vector2f& currentPos, int direction, float deltaTime, entities::GhostModel& ghost) const;

    /// Controleert of death-animatie klaar is
    void checkDeathAnimationState();
};

// -----------------
// TEMPLATE DEFINITIE
// -----------------

template<typename T1, typename T2>
bool World::checkCollision(const T1& entity1, const T2& entity2) {
    float e1_left   = entity1.getPosition().x - (entity1.getSize().x / 2);
    float e1_right  = entity1.getPosition().x + (entity1.getSize().x / 2);
    float e1_bottom = entity1.getPosition().y - (entity1.getSize().y / 2);
    float e1_top    = entity1.getPosition().y + (entity1.getSize().y / 2);

    float e2_left   = entity2.getPosition().x - (entity2.getSize().x / 2);
    float e2_right  = entity2.getPosition().x + (entity2.getSize().x / 2);
    float e2_bottom = entity2.getPosition().y - (entity2.getSize().y / 2);
    float e2_top    = entity2.getPosition().y + (entity2.getSize().y / 2);

    return (e1_right  > e2_left &&
            e1_left   < e2_right &&
            e1_top    > e2_bottom &&
            e1_bottom < e2_top);
}

#endif
}


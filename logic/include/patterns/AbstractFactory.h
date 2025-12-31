#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include <memory>
#include <string>

// Forward declarations - avoid circular dependencies
class WallModel;
class DoorModel;
class CoinModel;
class PacmanModel;
class GhostModel;
class FruitModel;
class RedGhostModel;
class BlueGhostModel;
class OrangeGhostModel;
class PinkGhostModel;

struct Vector2f;

/**
 * @class LogicFactory
 * @brief Abstract Factory interface for creating game entities
 *
 * DESIGN PATTERN: Abstract Factory
 * Purpose: Provide an interface for creating families of related objects
 * without specifying their concrete classes.
 *
 * USAGE PATTERN:
 * 1. World receives a LogicFactory& in constructor
 * 2. World calls factory->createPacman(...) to get a model
 * 3. Factory internally creates the matching view (if SFML)
 * 4. World only sees and uses the model (platform-independent)
 *
 */
class LogicFactory {
public:
    /**
     * @brief Virtual destructor for proper polymorphic deletion
     */
    virtual ~LogicFactory() = default;

    // ========================================================================
    // STATIC ENTITY CREATION - Walls, Doors, Collectibles
    // ========================================================================

    /**
     * @brief Create a wall entity at the specified position
     * @return Shared ownership of wall model (multiple systems may reference it)
     */
    virtual std::shared_ptr<WallModel> createWall(const Vector2f& position, const Vector2f& size) = 0;

    /**
     * @brief Create a door entity (blocks ghosts initially, not Pacman)
     * @return Shared ownership of door model
     */
    virtual std::shared_ptr<DoorModel> createDoor(const Vector2f& position, const Vector2f& size) = 0;

    /**
     * @brief Create a collectible coin entity
     * @return Shared ownership of coin model
     *
     * Note: Coins notify observers when collected (for scoring)
     */
    virtual std::shared_ptr<CoinModel> createCoin(const Vector2f& position, const Vector2f& size) = 0;

    /**
     * @brief Create a collectible fruit entity
     * @return Shared ownership of fruit model
     *
     * Note: Fruits trigger "scared mode" for ghosts when collected
     */
    virtual std::shared_ptr<FruitModel> createFruit(const Vector2f& position, const Vector2f& size) = 0;

    // ========================================================================
    // DYNAMIC ENTITY CREATION - Characters
    // ========================================================================

    /**
     * @brief Create the player-controlled Pacman entity
     * @return Shared ownership of Pacman model
     *
     * Only one Pacman should exist per game instance
     */
    virtual std::shared_ptr<PacmanModel> createPacman(const Vector2f& position, const Vector2f& size) = 0;

    /**
     * @brief Create a red ghost with specific AI behavior
     * @return Shared ownership of ghost model
     *
     * Red ghost: Random direction changes at intersections (50% probability)
     */
    virtual std::shared_ptr<RedGhostModel> createRedGhost(const Vector2f& position, const Vector2f& size) = 0;

    /**
     * @brief Create a blue ghost with specific AI behavior
     * @return Shared ownership of ghost model
     *
     * Blue ghost: Chases Pacman by moving toward position in front of Pacman
     */
    virtual std::shared_ptr<BlueGhostModel> createBlueGhost(const Vector2f& position, const Vector2f& size) = 0;

    /**
     * @brief Create an orange ghost with specific AI behavior
     * @return Shared ownership of ghost model
     *
     * Orange ghost: Uses same AI as blue ghost (chases ahead of Pacman)
     */
    virtual std::shared_ptr<OrangeGhostModel> createOrangeGhost(const Vector2f& position, const Vector2f& size) = 0;

    /**
     * @brief Create a pink ghost with specific AI behavior
     * @return Shared ownership of ghost model
     *
     * Pink ghost: Directly chases Pacman (minimizes Manhattan distance)
     */
    virtual std::shared_ptr<PinkGhostModel> createPinkGhost(const Vector2f& position, const Vector2f& size) = 0;
    /**
     * @brief Clear all views except Pacman's view (used for level transitions)
     *
     * When advancing to next level:
     * - Keep Pacman model and view (player persists)
     * - Destroy all other entities (walls, ghosts, coins rebuilt from new map)
     */
    virtual void clearNonPacmanViews() = 0;
};

#endif
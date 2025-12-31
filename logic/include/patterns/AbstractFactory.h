#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include <memory>
#include <string>

// Forward declarations
namespace pacman::logic {
    struct Vector2f;
}

namespace pacman::logic::entities {
    class WallModel;
    class DoorModel;
    class CoinModel;
    class PacmanModel;
    class FruitModel;
    class RedGhostModel;
    class BlueGhostModel;
    class OrangeGhostModel;
    class PinkGhostModel;
}

namespace pacman::logic::patterns {

/**
 * @class LogicFactory
 * @brief Abstract Factory interface for creating game entities
 *
 * DESIGN PATTERN: Abstract Factory
 * Purpose: Provide an interface for creating families of related objects
 * without specifying their concrete classes.
 */
class LogicFactory {
public:
    virtual ~LogicFactory() = default;

    // Static entity creation
    virtual std::shared_ptr<entities::WallModel> createWall(
        const Vector2f& position, const Vector2f& size) = 0;

    virtual std::shared_ptr<entities::DoorModel> createDoor(
        const Vector2f& position, const Vector2f& size) = 0;

    virtual std::shared_ptr<entities::CoinModel> createCoin(
        const Vector2f& position, const Vector2f& size) = 0;

    virtual std::shared_ptr<entities::FruitModel> createFruit(
        const Vector2f& position, const Vector2f& size) = 0;

    // Dynamic entity creation
    virtual std::shared_ptr<entities::PacmanModel> createPacman(
        const Vector2f& position, const Vector2f& size) = 0;

    virtual std::shared_ptr<entities::RedGhostModel> createRedGhost(
        const Vector2f& position, const Vector2f& size) = 0;

    virtual std::shared_ptr<entities::BlueGhostModel> createBlueGhost(
        const Vector2f& position, const Vector2f& size) = 0;

    virtual std::shared_ptr<entities::OrangeGhostModel> createOrangeGhost(
        const Vector2f& position, const Vector2f& size) = 0;

    virtual std::shared_ptr<entities::PinkGhostModel> createPinkGhost(
        const Vector2f& position, const Vector2f& size) = 0;

    // View management (for level transitions)
    virtual void clearNonPacmanViews() = 0;
};

} // namespace pacman::logic::patterns

#endif // ABSTRACT_FACTORY_H
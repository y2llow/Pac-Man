#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include "entities/GhostModel.h"


#include <memory>
#include <string>
#include"entities/WallModel.h"

class EntityView;
// Use logic-layer Vector2, not SFML
struct Vector2f { float x, y; };

// Forward declarations (logic layer only knows about models)
class Entity;
class CoinModel;
class PacmanModel;
class GhostModel;
class FruitModel;

class LogicFactory {
public:
    virtual ~LogicFactory() = default;

    virtual std::unique_ptr<WallModel> createWall(
        const sf::Vector2f& position,
        const sf::Vector2f& size,
        const std::string& textureId = std::string("")
    ) = 0;

    virtual std::unique_ptr<CoinModel> createCoin(
        const sf::Vector2f& position,
        const sf::Vector2f& size,
        const std::string& textureId = std::string("")
    ) = 0;

    virtual std::unique_ptr<PacmanModel> createPacman(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const std::string& textureId = std::string("")
    ) = 0;

    virtual std::unique_ptr<RedGhostModel> createRedGhost(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const std::string& textureId = std::string("")
    ) = 0;

    virtual std::unique_ptr<BlueGhostModel> createBlueGhost(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const std::string& textureId = std::string("")
    ) = 0;

    virtual std::unique_ptr<OrangeGhostModel> createOrangeGhost(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const std::string& textureId = std::string("")
    ) = 0;

    virtual std::unique_ptr<PinkGhostModel> createPinkGhost(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const std::string& textureId = std::string("")
    ) = 0;

    virtual std::unique_ptr<FruitModel> createFruit(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const std::string& textureId = std::string("")
    ) = 0;


};

#endif //ABSTRACTFACTORY_H

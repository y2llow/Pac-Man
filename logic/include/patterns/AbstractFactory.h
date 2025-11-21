#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include "entities/GhostModel.h"


#include <memory>
#include <string>
#include"entities/WallModel.h"

class EntityView;
// Use logic-layer Vector2, not SFML

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
        const Vector2f& position,
        const Vector2f& size,
        const std::string& textureId = std::string("")
    ) = 0;

    virtual std::unique_ptr<CoinModel> createCoin(
        const Vector2f& position,
        const Vector2f& size,
        const std::string& textureId = std::string("")
    ) = 0;

    virtual std::unique_ptr<PacmanModel> createPacman(
    const Vector2f& position,
    const Vector2f& size,
    const std::string& textureId = std::string("")
    ) = 0;

    virtual std::unique_ptr<RedGhostModel> createRedGhost(
    const Vector2f& position,
    const Vector2f& size,
    const std::string& textureId = std::string("")
    ) = 0;

    virtual std::unique_ptr<BlueGhostModel> createBlueGhost(
    const Vector2f& position,
    const Vector2f& size,
    const std::string& textureId = std::string("")
    ) = 0;

    virtual std::unique_ptr<OrangeGhostModel> createOrangeGhost(
    const Vector2f& position,
    const Vector2f& size,
    const std::string& textureId = std::string("")
    ) = 0;

    virtual std::unique_ptr<PinkGhostModel> createPinkGhost(
    const Vector2f& position,
    const Vector2f& size,
    const std::string& textureId = std::string("")
    ) = 0;

    virtual std::unique_ptr<FruitModel> createFruit(
    const Vector2f& position,
    const Vector2f& size,
    const std::string& textureId = std::string("")
    ) = 0;


};

#endif //ABSTRACTFACTORY_H

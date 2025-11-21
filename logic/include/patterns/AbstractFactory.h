#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include <memory>
#include <string>

// Forward declarations
class WallModel;
class CoinModel;
class PacmanModel;
class GhostModel;
class FruitModel;
class RedGhostModel;
class BlueGhostModel;
class OrangeGhostModel;
class PinkGhostModel;

struct Vector2f;

class LogicFactory {
public:
    virtual ~LogicFactory() = default;

    virtual std::shared_ptr<WallModel> createWall(const Vector2f& position, const Vector2f& size, const std::string& textureId) = 0;
    virtual std::shared_ptr<CoinModel> createCoin(const Vector2f& position, const Vector2f& size, const std::string& textureId) = 0;
    virtual std::shared_ptr<PacmanModel> createPacman(const Vector2f& position, const Vector2f& size, const std::string& textureId) = 0;
    virtual std::shared_ptr<RedGhostModel> createRedGhost(const Vector2f& position, const Vector2f& size, const std::string& textureId) = 0;
    virtual std::shared_ptr<BlueGhostModel> createBlueGhost(const Vector2f& position, const Vector2f& size, const std::string& textureId) = 0;
    virtual std::shared_ptr<OrangeGhostModel> createOrangeGhost(const Vector2f& position, const Vector2f& size, const std::string& textureId) = 0;
    virtual std::shared_ptr<PinkGhostModel> createPinkGhost(const Vector2f& position, const Vector2f& size, const std::string& textureId) = 0;
    virtual std::shared_ptr<FruitModel> createFruit(const Vector2f& position, const Vector2f& size, const std::string& textureId) = 0;
};

#endif
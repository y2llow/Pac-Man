#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H
#include "views/EntityView.h"


#include <memory>

// Use logic-layer Vector2, not SFML
struct Vector2f { float x, y; };

// Forward declarations (logic layer only knows about models)
class Entity;
class WallModel;
class CoinModel;
class PacManModel;
class GhostModel;
class FruitModel;

class LogicFactory {
public:
    virtual ~LogicFactory() = default;

    // Return both model and view as a package
    virtual std::pair<std::unique_ptr<WallModel>, std::unique_ptr<EntityView>>
        createWall(const Vector2f& position, const Vector2f& size) = 0;

    virtual std::pair<std::unique_ptr<CoinModel>, std::unique_ptr<EntityView>>
        createCoin(const Vector2f& position, const Vector2f& size) = 0;

    // Later add:
    // virtual std::unique_ptr<PacManModel> createPacMan(...) = 0;
    // virtual std::unique_ptr<GhostModel> createGhost(...) = 0;
};

#endif //ABSTRACTFACTORY_H

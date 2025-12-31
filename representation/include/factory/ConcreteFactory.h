#ifndef CONCRETE_FACTORY_H
#define CONCRETE_FACTORY_H

#include "patterns/AbstractFactory.h"
#include "views/EntityView.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Camera;

/**
 * @brief SFML implementation of Abstract Factory pattern
 *
 * Creates Model-View pairs: each entity gets a logic model + visual view.
 * Bridges logic layer (platform-independent) with representation layer (SFML).
 */
class SFMLFactory : public LogicFactory {
public:
    SFMLFactory(sf::RenderWindow& window, Camera& camera);

    // Factory methods - create models and automatically create matching views
    std::shared_ptr<WallModel> createWall(const Vector2f& position, const Vector2f& size) override;
    std::shared_ptr<DoorModel> createDoor(const Vector2f& position, const Vector2f& size) override;
    std::shared_ptr<CoinModel> createCoin(const Vector2f& position, const Vector2f& size) override;
    std::shared_ptr<PacmanModel> createPacman(const Vector2f& position, const Vector2f& size) override;
    std::shared_ptr<RedGhostModel> createRedGhost(const Vector2f& position, const Vector2f& size) override;
    std::shared_ptr<BlueGhostModel> createBlueGhost(const Vector2f& position, const Vector2f& size) override;
    std::shared_ptr<OrangeGhostModel> createOrangeGhost(const Vector2f& position, const Vector2f& size) override;
    std::shared_ptr<PinkGhostModel> createPinkGhost(const Vector2f& position, const Vector2f& size) override;
    std::shared_ptr<FruitModel> createFruit(const Vector2f& position, const Vector2f& size) override;

    // View management
    const std::vector<std::unique_ptr<EntityView>>& getViews() const { return m_views; }
    void handleResize(const Vector2f& newSize);
    void cleanupCollectedViews();  // Remove views for collected coins/fruits
    void clearNonPacmanViews() override;  // Used when advancing to next level

private:
    sf::RenderWindow& m_window;
    Camera& m_camera;
    std::vector<std::unique_ptr<EntityView>> m_views;  // Factory owns all views

    // Template helper - creates model + view pair, attaches observer
    template<typename ModelType, typename ViewType>
    std::shared_ptr<ModelType> createEntity(const Vector2f& position, const Vector2f& size);
};

#endif
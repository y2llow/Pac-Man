#ifndef CONCRETE_FACTORY_H
#define CONCRETE_FACTORY_H

#include "patterns/AbstractFactory.h"
#include "views/EntityView.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Camera;

class SFMLFactory : public LogicFactory {
public:
    SFMLFactory(sf::RenderWindow& window, Camera& camera);

    // Change return types to shared_ptr
    std::shared_ptr<WallModel> createWall(const Vector2f& position, const Vector2f& size, const std::string& textureId) override;
    std::shared_ptr<CoinModel> createCoin(const Vector2f& position, const Vector2f& size, const std::string& textureId) override;
    std::shared_ptr<PacmanModel> createPacman(const Vector2f& position, const Vector2f& size, const std::string& textureId) override;
    std::shared_ptr<RedGhostModel> createRedGhost(const Vector2f& position, const Vector2f& size, const std::string& textureId) override;
    std::shared_ptr<BlueGhostModel> createBlueGhost(const Vector2f& position, const Vector2f& size, const std::string& textureId) override;
    std::shared_ptr<OrangeGhostModel> createOrangeGhost(const Vector2f& position, const Vector2f& size, const std::string& textureId) override;
    std::shared_ptr<PinkGhostModel> createPinkGhost(const Vector2f& position, const Vector2f& size, const std::string& textureId) override;
    std::shared_ptr<FruitModel> createFruit(const Vector2f& position, const Vector2f& size, const std::string& textureId) override;

    // View management
    const std::vector<std::unique_ptr<EntityView>>& getViews() const { return m_views; }
    void handleResize(const Vector2f& newSize);
    void cleanupCollectedViews();

private:
    sf::RenderWindow& m_window;
    Camera& m_camera;
    std::vector<std::unique_ptr<EntityView>> m_views;

    // Template helper - return shared_ptr
    template<typename ModelType, typename ViewType, typename... Args>
    std::shared_ptr<ModelType> createEntity(const Vector2f& position, const Vector2f& size, const std::string& textureId, Args&&... args);
};

#endif
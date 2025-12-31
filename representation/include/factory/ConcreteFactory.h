#ifndef CONCRETE_FACTORY_H
#define CONCRETE_FACTORY_H

#include "patterns/AbstractFactory.h"
#include "views/EntityView.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace pacman::representation {
class Camera;
namespace factory {
/**
 * @brief SFML implementation of Abstract Factory pattern
 *
 * Creates Model-View pairs: each entity gets a logic model + visual view.
 * Bridges logic layer (platform-independent) with representation layer (SFML).
 */
class SFMLFactory : public logic::patterns::LogicFactory {
public:
    SFMLFactory(sf::RenderWindow& window, Camera& camera);

    // Factory methods - create models and automatically create matching views
    std::shared_ptr<logic::entities::WallModel> createWall(const logic::Vector2f& position, const logic::Vector2f& size) override;
    std::shared_ptr<logic::entities::DoorModel> createDoor(const logic::Vector2f& position, const logic::Vector2f& size) override;
    std::shared_ptr<logic::entities::CoinModel> createCoin(const logic::Vector2f& position, const logic::Vector2f& size) override;
    std::shared_ptr<logic::entities::PacmanModel> createPacman(const logic::Vector2f& position, const logic::Vector2f& size) override;
    std::shared_ptr<logic::entities::RedGhostModel> createRedGhost(const logic::Vector2f& position, const logic::Vector2f& size) override;
    std::shared_ptr<logic::entities::BlueGhostModel> createBlueGhost(const logic::Vector2f& position, const logic::Vector2f& size) override;
    std::shared_ptr<logic::entities::OrangeGhostModel> createOrangeGhost(const logic::Vector2f& position, const logic::Vector2f& size) override;
    std::shared_ptr<logic::entities::PinkGhostModel> createPinkGhost(const logic::Vector2f& position, const logic::Vector2f& size) override;
    std::shared_ptr<logic::entities::FruitModel> createFruit(const logic::Vector2f& position, const logic::Vector2f& size) override;

    // View management
    [[nodiscard]] const std::vector<std::unique_ptr<views::EntityView>>& getViews() const { return m_views; }
    void handleResize(const logic::Vector2f& newSize);
    void cleanupCollectedViews();  // Remove views for collected coins/fruits
    void clearNonPacmanViews() override;  // Used when advancing to next level

private:
    sf::RenderWindow& m_window;
    Camera& m_camera;
    std::vector<std::unique_ptr<views::EntityView>> m_views;  // Factory owns all views

    // Template helper - creates model + view pair, attaches observer
    template<typename ModelType, typename ViewType>
    std::shared_ptr<ModelType> createEntity(const logic::Vector2f& position, const logic::Vector2f& size);
};
}
}
#endif
#include "factory/ConcreteFactory.h"
#include "entities/WallModel.h"
#include "entities/DoorModel.h"
#include "entities/CoinModel.h"
#include "entities/FruitModel.h"
#include "entities/GhostModel.h"
#include "entities/PacmanModel.h"
#include "views/WallView.h"
#include "views/CollectibleView/CoinView.h"
#include "views/CollectibleView/FruitView.h"
#include "views/characterview/GhostView.h"
#include "views/characterview/PacmanView.h"
#include "Camera.h"
#include "views/DoorView.h"


#include <memory>

SFMLFactory::SFMLFactory(sf::RenderWindow& window, Camera& camera)
    : m_window(window), m_camera(camera) {
}

template<typename ModelType, typename ViewType>
std::shared_ptr<ModelType> SFMLFactory::createEntity(const Vector2f& position, const Vector2f& size) {
    // 1. Create model with shared ownership
    auto model = std::make_shared<ModelType>(position, size);

    // 2. Create view with shared model reference
    auto view = std::make_unique<ViewType>(model, m_camera);

    // 3. **NEW**: Attach view's update callback to model as observer
    auto viewPtr = view.get(); // Safe - view is stored in m_views
    model->attachObserver([viewPtr]() {
        // This lambda will be called whenever the model notifies
        // ViewType doesn't need explicit update() for now - it updates in main loop
        // But this keeps the observer pattern intact for future use
    });

    // 4. Store view in factory
    m_views.push_back(std::move(view));

    return model;
}

std::shared_ptr<WallModel> SFMLFactory::createWall(const Vector2f& position, const Vector2f& size) {
    return createEntity<WallModel, WallView>(position, size);
}

std::shared_ptr<DoorModel> SFMLFactory::createDoor(const Vector2f& position, const Vector2f& size) {
    return createEntity<DoorModel, DoorView>(position, size);
}

std::shared_ptr<CoinModel> SFMLFactory::createCoin(const Vector2f& position, const Vector2f& size) {
    return createEntity<CoinModel, CoinView>(position, size);
}

std::shared_ptr<PacmanModel> SFMLFactory::createPacman(const Vector2f& position, const Vector2f& size) {
    return createEntity<PacmanModel, PacmanView>(position, size);
}

std::shared_ptr<RedGhostModel> SFMLFactory::createRedGhost(const Vector2f& position, const Vector2f& size) {
    m_camera.updateWindowSize();
    return createEntity<RedGhostModel, RedGhostView>(position, size);
}

std::shared_ptr<BlueGhostModel> SFMLFactory::createBlueGhost(const Vector2f& position, const Vector2f& size) {
    return createEntity<BlueGhostModel, BlueGhostView>(position, size);
}

std::shared_ptr<OrangeGhostModel> SFMLFactory::createOrangeGhost(const Vector2f& position, const Vector2f& size) {
    return createEntity<OrangeGhostModel, OrangeGhostView>(position, size);
}

std::shared_ptr<PinkGhostModel> SFMLFactory::createPinkGhost(const Vector2f& position, const Vector2f& size) {
    return createEntity<PinkGhostModel, PinkGhostView>(position, size);
}

std::shared_ptr<FruitModel> SFMLFactory::createFruit(const Vector2f& position, const Vector2f& size) {
    return createEntity<FruitModel, FruitView>(position, size);
}

void SFMLFactory::handleResize(const Vector2f& newSize) {
    m_camera.updateWindowSize(newSize);
}

void SFMLFactory::cleanupCollectedViews() {
    m_views.erase(std::remove_if(m_views.begin(), m_views.end(),
        [](const std::unique_ptr<EntityView>& view) {
            // Cast to check if it's a collectible view
            if (auto* coinView = dynamic_cast<CoinView*>(view.get())) {
                return !coinView->shouldRender();
            }
            if (auto* fruitView = dynamic_cast<FruitView*>(view.get())) {
                return !fruitView->shouldRender();
            }
            // Keep walls, ghosts, pacman - they're never "collected"
            return false;
        }), m_views.end());
}

void SFMLFactory::clearNonPacmanViews() {
    // Remove all views except PacmanView
    m_views.clear();
}
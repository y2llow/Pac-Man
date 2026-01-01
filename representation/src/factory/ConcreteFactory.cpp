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
#include "views/DoorView.h"
#include "Camera.h"

#include <memory>

namespace pacman::representation::factory {

// Type aliases voor leesbaarheid
using logic::Vector2f;
using logic::entities::WallModel;
using logic::entities::DoorModel;
using logic::entities::CoinModel;
using logic::entities::FruitModel;
using logic::entities::PacmanModel;
using logic::entities::RedGhostModel;
using logic::entities::BlueGhostModel;
using logic::entities::OrangeGhostModel;
using logic::entities::PinkGhostModel;

using views::WallView;
using views::DoorView;
using views::CoinView;
using views::FruitView;
using views::PacmanView;
using views::RedGhostView;
using views::BlueGhostView;
using views::OrangeGhostView;
using views::PinkGhostView;

SFMLFactory::SFMLFactory(sf::RenderWindow& window, Camera& camera)
    : m_window(window), m_camera(camera) {
}

template<typename ModelType, typename ViewType>
std::shared_ptr<ModelType> SFMLFactory::createEntity(
    const Vector2f& position,
    const Vector2f& size
) {
    // STAP 1: Maak het MODEL
    auto model = std::make_shared<ModelType>(position, size);

    // STAP 2: Maak de VIEW
    auto view = std::make_unique<ViewType>(model, m_camera);

    // STAP 3: Koppel View aan Model via Observer
    // We hebben een raw pointer nodig voor in de lambda
    auto* viewPtr = view.get();

    // Attach observer: wanneer model verandert, update de view
    model->attachObserver([viewPtr]() {
        // View wordt genotificeerd bij model changes
        // Maar we updaten alleen de shape/sprite, geen deltaTime nodig
        viewPtr->onModelChanged();
    });

    // STAP 4: Bewaar view in factory
    m_views.push_back(std::move(view));

    // STAP 5: Return model
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
        [](const std::unique_ptr<views::EntityView>& view) {
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

} // namespace pacman::representation::factory
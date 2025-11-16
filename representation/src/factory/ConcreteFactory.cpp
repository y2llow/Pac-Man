#include "factory/ConcreteFactory.h"
#include "entities/WallModel.h"
#include "entities/CoinModel.h"
#include "entities/FruitModel.h"
#include "entities/GhostModel.h"
#include "entities/PacmanModel.h"
#include "views/WallView.h"
#include "views/CollectibleView/CoinView.h"
#include "patterns/Subject.h"
#include "views/CollectibleView/FruitView.h"
#include "views/characterview/GhostView.h"
#include "views/characterview/PacmanView.h"

SFMLFactory::SFMLFactory(sf::RenderWindow& window) 
    : m_window(window) {
}

 std::unique_ptr<WallModel> SFMLFactory::createWall(
    const sf::Vector2f&position,
    const sf::Vector2f&size,
    const std::string& textureId ) {

    // 1. Create the Model (logic)
    auto wallModel = std::make_unique<WallModel>(position, size, textureId);

    // // 2. Create the View (representation)
    auto wallView = std::make_unique<WallView>(*wallModel, m_window);

    // Attach raw pointer (temporary - views are owned by factory)
    wallModel->attachObserver([view = wallView.get()]() {
        if (view) {
            view->update();
        }
    });

    // Store the view in factory
    m_views.push_back(std::move(wallView));

    return wallModel;
}
std::unique_ptr<CoinModel> SFMLFactory::createCoin(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const std::string& textureId) {

    // 1. Create the Model (logic)
    auto coinModel = std::make_unique<CoinModel>(position, size, textureId);

    // 2. Create the View (representation)
    auto coinView = std::make_unique<CoinView>(*coinModel, m_window);

    // 3. PDF: "attach the View observers to the Model subjects directly when they are created"
    coinModel->attachObserver([view = coinView.get()]() {
        if (view) {
            view->update();
        }
    });

    m_views.push_back(std::move(coinView));


    // 4. Return only the Model to World
    return coinModel;
}

std::unique_ptr<PacmanModel> SFMLFactory::createPacman(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const std::string& textureId) {

    // 1. Create the Model (logic)
    auto pacmanModel = std::make_unique<PacmanModel>(position, size, textureId);

    // 2. Create the View (representation)
    auto pacmanView = std::make_unique<PacmanView>(*pacmanModel, m_window);

    // 3. PDF: "attach the View observers to the Model subjects directly when they are created"
    pacmanModel->attachObserver([view = pacmanView.get()]() {
        if (view) {
            view->update();
        }
    });

    m_views.push_back(std::move(pacmanView));


    // 4. Return only the Model to World
    return pacmanModel;
}

std::unique_ptr<RedGhostModel> SFMLFactory::createRedGhost(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const std::string& textureId) {

    // 1. Create the Model (logic)
    auto ghostModel = std::make_unique<RedGhostModel>(position, size, textureId);

    // 2. Create the View (representation)
    auto ghostView = std::make_unique<RedGhostView>(*ghostModel, m_window);

    // 3. PDF: "attach the View observers to the Model subjects directly when they are created"
    ghostModel->attachObserver([view = ghostView.get()]() {
        if (view) {
            view->update();
        }
    });

    m_views.push_back(std::move(ghostView));


    // 4. Return only the Model to World
    return ghostModel;
}

std::unique_ptr<BlueGhostModel> SFMLFactory::createBlueGhost(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const std::string& textureId) {

    // 1. Create the Model (logic)
    auto ghostModel = std::make_unique<BlueGhostModel>(position, size, textureId);

    // 2. Create the View (representation)
    auto ghostView = std::make_unique<BlueGhostView>(*ghostModel, m_window);

    // 3. PDF: "attach the View observers to the Model subjects directly when they are created"
    ghostModel->attachObserver([view = ghostView.get()]() {
        if (view) {
            view->update();
        }
    });

    m_views.push_back(std::move(ghostView));


    // 4. Return only the Model to World
    return ghostModel;
}

std::unique_ptr<OrangeGhostModel> SFMLFactory::createOrangeGhost(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const std::string& textureId) {

    // 1. Create the Model (logic)
    auto ghostModel = std::make_unique<OrangeGhostModel>(position, size, textureId);

    // 2. Create the View (representation)
    auto ghostView = std::make_unique<OrangeGhostView>(*ghostModel, m_window);

    // 3. PDF: "attach the View observers to the Model subjects directly when they are created"
    ghostModel->attachObserver([view = ghostView.get()]() {
        if (view) {
            view->update();
        }
    });

    m_views.push_back(std::move(ghostView));


    // 4. Return only the Model to World
    return ghostModel;
}

std::unique_ptr<PinkGhostModel> SFMLFactory::createPinkGhost(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const std::string& textureId) {

    // 1. Create the Model (logic)
    auto ghostModel = std::make_unique<PinkGhostModel>(position, size, textureId);

    // 2. Create the View (representation)
    auto ghostView = std::make_unique<PinkGhostView>(*ghostModel, m_window);

    // 3. PDF: "attach the View observers to the Model subjects directly when they are created"
    ghostModel->attachObserver([view = ghostView.get()]() {
        if (view) {
            view->update();
        }
    });

    m_views.push_back(std::move(ghostView));


    // 4. Return only the Model to World
    return ghostModel;
}

std::unique_ptr<FruitModel> SFMLFactory::createFruit(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const std::string& textureId) {

    // 1. Create the Model (logic)
    auto fruitModel = std::make_unique<FruitModel>(position, size, textureId);

    // 2. Create the View (representation)
    auto fruitView = std::make_unique<FruitView>(*fruitModel, m_window);

    // 3. PDF: "attach the View observers to the Model subjects directly when they are created"
    fruitModel->attachObserver([view = fruitView.get()]() {
        if (view) {
            view->update();
        }
    });

    m_views.push_back(std::move(fruitView));


    // 4. Return only the Model to World
    return fruitModel;
}
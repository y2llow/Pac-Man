#include "factory/ConcreteFactory.h"
#include "entities/WallModel.h"
#include "entities/CoinModel.h"
#include "views/WallView.h"
#include "views/CollectibleView/CoinView.h"
#include "patterns/Subject.h"

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

    // Store the view in factory
    m_observers.push_back(std::move(wallView));

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
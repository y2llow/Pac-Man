#ifndef CONCRETEFACTORY_H
#define CONCRETEFACTORY_H
#include "patterns/AbstractFactory.h"
#include "views/EntityView.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Observer;
class WallView;
class CoinView;

class SFMLFactory : public LogicFactory {
public:
    explicit SFMLFactory(sf::RenderWindow& window);

    std::unique_ptr<WallModel> createWall(
        const sf::Vector2f& position,
        const sf::Vector2f& size,
        const std::string& textureId = std::string("")
    ) override;

    std::unique_ptr<CoinModel> createCoin(
        const sf::Vector2f& position,
        const sf::Vector2f& size,
        const std::string& textureId = std::string("")
    ) override;

    std::unique_ptr<PacmanModel>createPacman(
        const sf::Vector2f&position,
        const sf::Vector2f&size,
        const std::string&textureId= std::string("")
        ) override;

    // NEW: Method to access views for rendering
    const std::vector<std::unique_ptr<EntityView>>& getViews() const { return m_views; }

private:
    sf::RenderWindow& m_window;
    std::vector<std::unique_ptr<EntityView>> m_views; // Store views!
    std::vector<std::unique_ptr<Observer>> m_observers;

};
#endif //CONCRETEFACTORY_H

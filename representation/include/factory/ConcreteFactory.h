#ifndef CONCRETEFACTORY_H
#define CONCRETEFACTORY_H
#include "patterns/AbstractFactory.h"
#include <SFML/Graphics.hpp>
#include <memory>

// Forward declarations
class WallView;
class CoinView;
class EntityView;

class SFMLFactory : public LogicFactory {
public:
    SFMLFactory(sf::RenderWindow& window);

    // Implement LogicFactory interface
    std::unique_ptr<WallModel> createWall(
        const sf::Vector2f& position,
        const sf::Vector2f& size) override;

    std::unique_ptr<CoinModel> createCoin(
        const sf::Vector2f& position,
        const sf::Vector2f& size,
        const std::string& textureId = ""
    ) override;

private:
    sf::RenderWindow& m_window;
    std::vector<std::unique_ptr<EntityView>> m_views; // Store views!

};
#endif //CONCRETEFACTORY_H

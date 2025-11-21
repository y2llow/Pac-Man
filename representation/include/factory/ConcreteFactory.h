#ifndef CONCRETEFACTORY_H
#define CONCRETEFACTORY_H
#include "Camera.h"
#include "patterns/AbstractFactory.h"
#include "views/EntityView.h"
#include "views/CollectibleView/CoinView.h"

#include <SFML/Graphics.hpp>
#include <memory>

class Observer;
class WallView;
class CoinView;

class SFMLFactory : public LogicFactory {
public:
    explicit SFMLFactory(sf::RenderWindow& window, Camera& camera);


    std::unique_ptr<WallModel> createWall(
        const Vector2f& position,
        const Vector2f& size,
        const std::string& textureId = std::string("")
    ) ;

    std::unique_ptr<CoinModel> createCoin(
        const Vector2f& position,
        const Vector2f& size,
        const std::string& textureId = std::string("")
    ) ;

    std::unique_ptr<PacmanModel>createPacman(
        const Vector2f&position,
        const Vector2f&size,
        const std::string&textureId= std::string("")
        ) ;

    std::unique_ptr<RedGhostModel> createRedGhost(
        const Vector2f& position,
        const Vector2f& size,
        const std::string& textureId = std::string("")
        )  ;

    std::unique_ptr<BlueGhostModel> createBlueGhost(
    const Vector2f& position,
    const Vector2f& size,
    const std::string& textureId = std::string("")
    )  ;

    std::unique_ptr<OrangeGhostModel> createOrangeGhost(
    const Vector2f& position,
    const Vector2f& size,
    const std::string& textureId = std::string("")
    )  ;

    std::unique_ptr<PinkGhostModel> createPinkGhost(
    const Vector2f& position,
    const Vector2f& size,
    const std::string& textureId = std::string("")
    )  ;

    std::unique_ptr<FruitModel> createFruit(
        const Vector2f& position,
        const Vector2f& size,
        const std::string& textureId = std::string("")
        )  ;

    [[nodiscard]] const std::vector<std::unique_ptr<EntityView>>& getViews() const { return m_views; }

    void handleResize(const Vector2f& position);
    void cleanupCollectedViews();

private:
    sf::RenderWindow& m_window;
    Camera& m_camera;
    std::vector<std::unique_ptr<EntityView>> m_views; // Store views!
    std::vector<std::unique_ptr<Observer>> m_observers;

};
#endif //CONCRETEFACTORY_H

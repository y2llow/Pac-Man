#ifndef COIN_VIEW_H
#define COIN_VIEW_H

#include "Camera.h"
#include "views/EntityView.h"
#include <SFML/Graphics.hpp>

// Forward declarations
namespace pacman::logic::entities {
class CoinModel;
}

namespace pacman::representation::views {

class CoinView : public EntityView {
public:
    explicit CoinView(std::shared_ptr<logic::entities::CoinModel> coinModel, Camera& camera);
    ~CoinView() override = default;

    // EntityView interface
    void update(float deltaTime) override;
    void onModelChanged() override;
    void draw(sf::RenderWindow& window) override;

    bool shouldRender() const;

private:
    std::shared_ptr<logic::entities::CoinModel> m_coinModel;
    Camera& m_camera;
    sf::Sprite m_sprite;

    void updateSprite();
    void updateShape();
};

} // namespace pacman::representation::views

#endif // COIN_VIEW_H
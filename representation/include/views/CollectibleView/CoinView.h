#ifndef COIN_VIEW_H
#define COIN_VIEW_H

#include "Camera.h"
#include "views/EntityView.h"
#include <SFML/Graphics.hpp>

// Forward declarations
class CoinModel;

class CoinView : public EntityView {
public:
    explicit CoinView(std::shared_ptr<CoinModel> coinModel, Camera& camera);
    ~CoinView() override = default;

    // EntityView interface
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    bool shouldRender() const;

private:
    std::shared_ptr<CoinModel> m_coinModel;
    Camera& m_camera;
    sf::Sprite m_sprite;  // CHANGED: gebruik sprite ipv circle

    void updateSprite();
    void updateShape();
};

#endif // COIN_VIEW_H
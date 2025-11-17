#ifndef COIN_VIEW_H
#define COIN_VIEW_H

#include "Camera.h"
#include "views/EntityView.h"
#include <SFML/Graphics.hpp>

// Forward declarations
class CoinModel;

class CoinView : public EntityView {
public:
    CoinView(CoinModel& coinModel, sf::RenderWindow& window, Camera& camera);
    ~CoinView() override = default;

    // Observer interface
    void update() override;

    // Rendering
    void draw(sf::RenderWindow& window) override;
    bool shouldRender() const;

private:
    CoinModel& m_coinModel;
    sf::RenderWindow& m_window;
    Camera& m_camera;
    sf::CircleShape m_circle;

    static constexpr float PELLET_SIZE = 5.0f;

    void updateSprite();
    void updateShape();
};

#endif // COIN_VIEW_H
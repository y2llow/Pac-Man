#ifndef COIN_VIEW_H
#define COIN_VIEW_H

#include "Camera.h"
#include "views/EntityView.h"

#include <SFML/Graphics.hpp>

// Forward declarations
class CoinModel;
class TextureManager;

class CoinView : public EntityView {
public:
    CoinView(CoinModel& coinModel, sf::RenderWindow& window, Camera& camera);
    ~CoinView() override = default;

    // Observer interface
    void update() override;

    // Rendering
    void draw(sf::RenderWindow& window);
    bool shouldRender() const;

private:
    CoinModel& m_coinModel;  // Reference to the model we're observing
    sf::RenderWindow& m_window;  // PDF: "hold a pointer to your window object in your View"
    Camera& m_camera;
    sf::Sprite m_sprite;
    sf::CircleShape m_circle;

    float PELLET_SIZE = 0.75f;
    void updateSprite();  // Update graphics based on model state
    void updateShape();

};

#endif
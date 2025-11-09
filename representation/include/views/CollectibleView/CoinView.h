#ifndef COIN_VIEW_H
#define COIN_VIEW_H

#include "patterns/Observer.h"
#include <SFML/Graphics.hpp>

// Forward declarations
class CoinModel;
class TextureManager;

class CoinView : public Observer {
public:
    CoinView(CoinModel& coinModel, sf::RenderWindow& window);
    ~CoinView() override = default;

    // Observer interface
    void update() override;

    // Rendering
    void draw(sf::RenderWindow& window);
    bool shouldRender() const;

private:
    CoinModel& m_coinModel;  // Reference to the model we're observing
    sf::RenderWindow& m_window;  // PDF: "hold a pointer to your window object in your View"
    sf::Sprite m_sprite;

    void updateSprite();  // Update graphics based on model state
};

#endif
#include "views/CollectibleView/CoinView.h"

#include "Game.h"
#include "entities/CoinModel.h"
#include "rendering/SpriteManager.h"

CoinView::CoinView(CoinModel& coinModel, sf::RenderWindow& window)
    : m_coinModel(coinModel), m_window(window) {
    // Setup circle shape for coin
    m_circle.setFillColor(sf::Color(255, 184, 144));
    float pellet = 1.15f;
    m_circle.setRadius(pellet);  // Small radius for coins
    m_circle.setOrigin(pellet, pellet);  // Center the circle

    updateShape();

    // Setup sprite...
    updateSprite();  // Initial sync with model
}

void CoinView::update() {
    // PDF: "A View can then receive an event for every update step (tick)"
    // PDF: "updating the View when the Model state changes"
    updateSprite();

    // Example: handle different events
    if (m_coinModel.isCollected()) {
        // PDF: "when a coin or fruit is collected"
        // Could trigger collection animation
    }
}

void CoinView::updateSprite() {
    // Sync sprite with model state
    // - Update position based on model.getPosition()
    // - Update texture/animation based on model state
    // - Handle visibility based on model.isActive() or model.isCollected()
}

void CoinView::draw(sf::RenderWindow& window) {
    window.draw(m_circle);
    if (shouldRender()) {
        window.draw(m_circle);
    }
}

bool CoinView::shouldRender() const {
    return !m_coinModel.isCollected();  // Don't render collected coins
}

void CoinView::updateShape() {
    // Convert normalized coordinates [-1, 1] to pixel coordinates
    sf::Vector2f logicPos = m_coinModel.getPosition();

    const float windowWidth = pacman::representation::Game::WINDOW_WIDTH;
    const float windowHeight = pacman::representation::Game::WINDOW_HEIGHT;

    // Convert from normalized [-1,1] to pixel coordinates [0,800]
    float pixelX = (logicPos.x + 1.0f) * (windowWidth / 2.0f);
    float pixelY = (logicPos.y + 1.0f) * (windowHeight / 2.0f);

    // Set position - circle is already centered due to setOrigin
    m_circle.setPosition(pixelX, pixelY);

    // Optional: Scale based on coin size if needed
    sf::Vector2f logicSize = m_coinModel.getSize();
    float scaleX = logicSize.x * 20.0f;  // Adjust scaling factor as needed
    float scaleY = logicSize.y * 20.0f;
    m_circle.setScale(scaleX, scaleY);
}
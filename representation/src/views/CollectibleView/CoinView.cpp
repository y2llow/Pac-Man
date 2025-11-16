#include "views/CollectibleView/CoinView.h"

#include "Game.h"
#include "entities/CoinModel.h"
#include "rendering/SpriteManager.h"

CoinView::CoinView(CoinModel& coinModel, sf::RenderWindow& window, Camera& camera)
    : m_coinModel(coinModel), m_window(window), m_camera(camera){
    // Setup circle shape for coin
    m_circle.setFillColor(sf::Color(255, 184, 144));

    m_circle.setRadius(PELLET_SIZE);  // Small radius for coins
    m_circle.setOrigin(PELLET_SIZE, PELLET_SIZE);  // Center the circle

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

void    CoinView::updateShape() {
    // Convert normalized coordinates to pixel coordinates using camera
    sf::Vector2f logicPos = m_coinModel.getPosition();
    sf::Vector2f pixelPos = m_camera.worldToPixel(logicPos);

    // Convert normalized size to pixel size
    sf::Vector2f logicSize = m_coinModel.getSize();
    sf::Vector2f pixelSize = m_camera.worldToPixelSize(logicSize);

    // Set position
    m_circle.setPosition(pixelPos);

    // Scale based on converted size
    float baseRadius = 10.0f;  // Base radius in pixels
    float scaleX = pixelSize.x / baseRadius;
    float scaleY = pixelSize.y / baseRadius;
    m_circle.setScale(scaleX, scaleY);
}

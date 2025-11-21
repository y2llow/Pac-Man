#include "views/CollectibleView/CoinView.h"

#include "Game.h"
#include "entities/CoinModel.h"
#include "rendering/SpriteManager.h"

CoinView::CoinView(CoinModel& coinModel, Camera& camera)
    : m_coinModel(coinModel), m_camera(camera) {

    // Setup circle shape for coin
    m_circle.setFillColor(sf::Color(255, 184, 144));

    updateShape();
    updateSprite();
}

void CoinView::update() {
    // Update graphics based on model state changes
    updateSprite();

    // Handle collection state
    if (m_coinModel.isCollected()) {
        // Could trigger collection animation or effects here
    }
}

void CoinView::updateSprite() {
    // Sync visual representation with model state
    // Update position, visibility, etc.
    updateShape();
}

void CoinView::draw(sf::RenderWindow& window) {
    if (shouldRender()) {
        window.draw(m_circle);
    }
}

bool CoinView::shouldRender() const {
    return !m_coinModel.isCollected();
}

void CoinView::updateShape() {
    // Convert normalized coordinates to pixel coordinates using camera
    Vector2f logicPos = m_coinModel.getPosition();
    Vector2f pixelPos = m_camera.worldToPixel(logicPos);

    // Convert normalized size to pixel size
    Vector2f logicSize = m_coinModel.getSize();
    Vector2f pixelSize = m_camera.worldToPixelSize(logicSize);

    // Fixed base radius
    float newRadius = std::min(pixelSize.x, pixelSize.y);
    m_circle.setRadius(newRadius);
    m_circle.setOrigin(newRadius, newRadius);
    m_circle.setPosition(pixelPos.x , pixelPos.y); // Use world coordinates directly

    // Scale transforms world coordinates to screen coordinates
    // This will stretch the circle into an oval
    float scaleX = pixelSize.x / (newRadius * 2.0f);
    float scaleY = pixelSize.y / (newRadius * 2.0f);
    m_circle.setScale(scaleX, scaleY);

}
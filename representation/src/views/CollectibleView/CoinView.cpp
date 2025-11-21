#include "views/CollectibleView/CoinView.h"

#include "Game.h"
#include "entities/CoinModel.h"
#include "rendering/SpriteManager.h"

CoinView::CoinView(std::shared_ptr<CoinModel> coinModel, Camera& camera)
    : m_coinModel(std::move(coinModel)), m_camera(camera) {

    // Setup circle shape for coin
    m_circle.setFillColor(sf::Color(255, 184, 144));
    updateShape();
    updateSprite();
}

void CoinView::update() {
    // Update graphics based on model state changes
    updateSprite();
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
    return m_coinModel && !m_coinModel->isCollected();
}

void CoinView::updateShape() {
    if (!m_coinModel) return;

    if (m_coinModel->isCollected()) {
        return;
    }

    // Convert normalized coordinates to pixel coordinates using camera
    Vector2f logicPos = m_coinModel->getPosition();
    Vector2f pixelPos = m_camera.worldToPixel(logicPos);

    // Convert normalized size to pixel size
    Vector2f logicSize = m_coinModel->getSize();
    Vector2f pixelSize = m_camera.worldToPixelSize(logicSize);

    // Fixed base radius
    float newRadius = std::min(pixelSize.x, pixelSize.y);
    m_circle.setRadius(newRadius);
    m_circle.setOrigin(newRadius, newRadius);
    m_circle.setPosition(pixelPos.x, pixelPos.y);

    float scaleX = pixelSize.x / (newRadius * 2.0f);
    float scaleY = pixelSize.y / (newRadius * 2.0f);
    m_circle.setScale(scaleX, scaleY);
}
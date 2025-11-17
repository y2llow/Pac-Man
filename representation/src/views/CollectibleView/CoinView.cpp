#include "views/CollectibleView/CoinView.h"

#include "Game.h"
#include "entities/CoinModel.h"
#include "rendering/SpriteManager.h"

CoinView::CoinView(CoinModel& coinModel, sf::RenderWindow& window, Camera& camera)
    : m_coinModel(coinModel), m_window(window), m_camera(camera) {

    // Setup circle shape for coin
    m_circle.setFillColor(sf::Color(255, 184, 144));
    m_circle.setRadius(PELLET_SIZE);
    m_circle.setOrigin(PELLET_SIZE, PELLET_SIZE);

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
    sf::Vector2f logicPos = m_coinModel.getPosition();
    sf::Vector2f pixelPos = m_camera.worldToPixel(logicPos);

    // Convert normalized size to pixel size
    sf::Vector2f logicSize = m_coinModel.getSize();
    sf::Vector2f pixelSize = m_camera.worldToPixelSize(logicSize);

    // Set position
    m_circle.setPosition(pixelPos);

    float newRadius = std::min(pixelSize.x, pixelSize.y) / (PELLET_SIZE * 2.0f);
    m_circle.setRadius(newRadius);
    m_circle.setOrigin(newRadius, newRadius); // Origin opnieuw centreren

    // Scale based on converted size
    float baseRadius = PELLET_SIZE;
    float scaleX = pixelSize.x / (baseRadius * 2.0f);
    float scaleY = pixelSize.y / (baseRadius * 2.0f);
    m_circle.setScale(scaleX, scaleY);
}
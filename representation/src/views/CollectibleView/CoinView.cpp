#include "views/CollectibleView/CoinView.h"

#include "entities/CoinModel.h"
#include "rendering/SpriteManager.h"

CoinView::CoinView(CoinModel& coinModel, sf::RenderWindow& window)
    : m_coinModel(coinModel), m_window(window) {

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
    if (shouldRender()) {
        window.draw(m_sprite);
    }
}

bool CoinView::shouldRender() const {
    return !m_coinModel.isCollected();  // Don't render collected coins
}
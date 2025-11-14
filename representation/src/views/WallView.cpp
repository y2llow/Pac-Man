#include "views/WallView.h"

#include "Game.h"
#include "../../../logic/include/entities/WallModel.h"

WallView::WallView(WallModel& model, sf::RenderWindow& window) 
    : m_model(model) {
    m_shape.setFillColor(((sf::Color(33,33,255))));
    updateShape(); // Initial setup
}

void WallView::update() {
    // Called when WallModel notifies observers
    updateShape();
}

void WallView::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
}

void WallView::updateShape() {
    // Convert normalized coordinates [-1, 1] to pixel coordinates
    sf::Vector2f logicPos = m_model.getPosition();
    sf::Vector2f logicSize = m_model.getSize();

    // Use proper coordinate conversion (you'll need to pass Camera to WallView)
    // For now, use the same conversion but make it consistent
    const float windowWidth = pacman::representation::Game::WINDOW_WIDTH;  // Match your window size
    const float windowHeight = pacman::representation::Game::WINDOW_HEIGHT;

    float pixelX = (logicPos.x + 1.0f) * (windowWidth / 2.0f);
    float pixelY = (logicPos.y + 1.0f) * (windowHeight / 2.0f);
    float pixelWidth = logicSize.x * (windowWidth / 2.0f);
    float pixelHeight = logicSize.y * (windowHeight / 2.0f);

    m_shape.setPosition(pixelX - pixelWidth / 2, pixelY - pixelHeight / 2); // Center
    m_shape.setSize(sf::Vector2f(pixelWidth, pixelHeight));
}
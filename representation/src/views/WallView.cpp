#include "views/WallView.h"
#include "../../../logic/include/entities/WallModel.h"

WallView::WallView(WallModel& model, sf::RenderWindow& window) 
    : m_model(model) {
    m_shape.setFillColor(sf::Color::Blue);
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
    // Convert logic coordinates to pixel coordinates
    // For now, we'll use a simple conversion
    sf::Vector2f logicPos = m_model.getPosition();
    sf::Vector2f logicSize = m_model.getSize();
    
    // Simple conversion: logic [-1,1] to pixels [0,800]
    float pixelX = (logicPos.x + 1.0f) * 400.0f;
    float pixelY = (logicPos.y + 1.0f) * 300.0f;
    float pixelWidth = logicSize.x * 400.0f;
    float pixelHeight = logicSize.y * 300.0f;
    
    m_shape.setPosition(pixelX, pixelY);
    m_shape.setSize(sf::Vector2f(pixelWidth, pixelHeight));
}
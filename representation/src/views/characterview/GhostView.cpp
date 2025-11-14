#include "views/characterview/GhostView.h"

GhostView::GhostView(GhostModel& ghostmodel, sf::RenderWindow& window):m_ghostmodel(ghostmodel), m_window(window) {

    //set shape

    m_circle.setFillColor(sf::Color(255,0,0));
    m_circle.setRadius(10);
    m_circle.setOrigin(10.0f, 10.0f);

    updateShape();

}

void GhostView::update() {

}

void GhostView::draw(sf::RenderWindow& window) {
    m_window.draw(m_circle);
}

void GhostView::updateShape() {
    // Convert normalized coordinates [-1, 1] to pixel coordinates
    sf::Vector2f logicPos = m_ghostmodel.getPosition();

    const float windowWidth = 800.0f;
    const float windowHeight = 600.0f;

    // Convert from normalized [-1,1] to pixel coordinates [0,800]
    float pixelX = (logicPos.x + 1.0f) * (windowWidth / 2.0f);
    float pixelY = (logicPos.y + 1.0f) * (windowHeight / 2.0f);

    // Set position - circle is already centered due to setOrigin
    m_circle.setPosition(pixelX, pixelY);

    // Optional: Scale based on coin size if needed
    sf::Vector2f logicSize = m_ghostmodel.getSize();
    float scaleX = logicSize.x * 15.0f;  // Adjust scaling factor as needed
    float scaleY = logicSize.y * 15.0f;
    m_circle.setScale(scaleX, scaleY);
}


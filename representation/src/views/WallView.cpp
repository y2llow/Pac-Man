#include "views/WallView.h"
#include "Game.h"
#include "../../../logic/include/entities/WallModel.h"

WallView::WallView(WallModel& model, sf::RenderWindow& window, Camera& camera)
    : m_window(window), m_model(model), m_camera(camera) {
    setupRectangle();
    updateShape(); // Initial setup
}

void WallView::setupRectangle() {
    m_shape.setFillColor(sf::Color::Blue);

    // Center the origin (we'll set the actual size in updateShape)
    m_shape.setOrigin(0.5f, 0.5f); // This will be relative to whatever size we set later
}

void WallView::update() {
    updateShape();
}

void WallView::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
}

void WallView::updateShape() {
    // Convert normalized coordinates [-1, 1] to pixel coordinates
    sf::Vector2f logicPos = m_model.getPosition();
    sf::Vector2f pixelPos = m_camera.worldToPixel(logicPos);

    // Convert normalized size to pixel size
    sf::Vector2f logicSize = m_model.getSize();
    sf::Vector2f pixelSize = m_camera.worldToPixelSize(logicSize);

    // Set the actual size - this determines the rectangle dimensions
    m_shape.setSize(pixelSize);

    // Update origin to be centered based on current size
    m_shape.setOrigin(pixelSize.x / 2.0f, pixelSize.y / 2.0f);

    // Set position
    m_shape.setPosition(pixelPos);

    // NO SCALING - we already set the correct size above
    // Remove this line: m_shape.setScale(scaleX, scaleY);
}
#include "views/WallView.h"
#include "Game.h"
#include "../../../logic/include/entities/WallModel.h"

WallView::WallView(WallModel& model, sf::RenderWindow& window, Camera& camera)
    : m_window(window), m_model(model), m_camera(camera) {
    setupRectangle();
    updateShape();
}

void WallView::setupRectangle() {
    m_shape.setFillColor(sf::Color(33, 33, 255));
    // Laat de origin leeg - wordt in updateShape gezet
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

    // **CRUCIAAL: Gebruik de pixelSize direct als grootte**
    m_shape.setSize(pixelSize);

    // Center de origin op de werkelijke grootte
    m_shape.setOrigin(pixelSize.x / 2.0f, pixelSize.y / 2.0f);

    // Zet positie
    m_shape.setPosition(pixelPos);
}
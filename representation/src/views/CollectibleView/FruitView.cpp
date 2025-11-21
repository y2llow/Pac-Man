#include "views/CollectibleView/FruitView.h"

#include "Game.h"
#include "entities/FruitModel.h"

FruitView::FruitView(FruitModel& fruitmodel, Camera& camera)
    : m_fruitmodel(fruitmodel), m_camera(camera) {

    // Setup circle shape for fruit
    m_circle.setFillColor(sf::Color(0, 255, 0));

    updateShape();
}

void FruitView::update() {
    updateShape();

    // You can add additional update logic here for:
    // - Animation states
    // - Collection effects
    // - Visibility based on model state
    // Handle collection state
    if (m_fruitmodel.isCollected()) {
        // Could trigger collection animation or effects here
    }
}

void FruitView::draw(sf::RenderWindow& window) {
    // Only draw if the fruit is active/not collected
    // if (!m_fruitmodel.isCollected()) {
    //     window.draw(m_circle);
    // }
    if (shouldRender()) {
        window.draw(m_circle);
    }
}
bool FruitView::shouldRender() const {
    return !m_fruitmodel.isCollected();
}


void FruitView::updateShape() {
    // Convert normalized coordinates to pixel coordinates using camera
    Vector2f logicPos = m_fruitmodel.getPosition();
    Vector2f pixelPos = m_camera.worldToPixel(logicPos);

    // Convert normalized size to pixel size
    Vector2f logicSize = m_fruitmodel.getSize();
    Vector2f pixelSize = m_camera.worldToPixelSize(logicSize);

    // Fixed base radius
    float newRadius = std::min(pixelSize.x, pixelSize.y);
    m_circle.setRadius(newRadius);
    m_circle.setOrigin(newRadius, newRadius);
    m_circle.setPosition(pixelPos.x, pixelPos.y); // Use world coordinates directly

    // Scale transforms world coordinates to screen coordinates
    // This will stretch the circle into an oval
    float scaleX = pixelSize.x / (newRadius * 2.0f);
    float scaleY = pixelSize.y / (newRadius * 2.0f);
    m_circle.setScale(scaleX, scaleY);
}







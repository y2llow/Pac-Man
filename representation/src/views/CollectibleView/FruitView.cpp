#include "views/CollectibleView/FruitView.h"

#include "Game.h"
#include "entities/FruitModel.h"

FruitView::FruitView(FruitModel& fruitmodel, sf::RenderWindow& window, Camera& camera)
    : m_fruitmodel(fruitmodel), m_window(window), m_camera(camera) {

    // Setup circle shape for fruit
    m_circle.setFillColor(sf::Color(0, 255, 0));
    m_circle.setRadius(FRUIT_SIZE);
    m_circle.setOrigin(FRUIT_SIZE, FRUIT_SIZE);

    updateShape();
}

void FruitView::update() {
    updateShape();

    // You can add additional update logic here for:
    // - Animation states
    // - Collection effects
    // - Visibility based on model state
}

void FruitView::draw(sf::RenderWindow& window) {
    // Only draw if the fruit is active/not collected
    // if (!m_fruitmodel.isCollected()) {
    //     window.draw(m_circle);
    // }
    window.draw(m_circle);
}

void FruitView::updateShape() {
    // Convert normalized coordinates to pixel coordinates using camera
    sf::Vector2f logicPos = m_fruitmodel.getPosition();
    sf::Vector2f pixelPos = m_camera.worldToPixel(logicPos);

    // Convert normalized size to pixel size
    sf::Vector2f logicSize = m_fruitmodel.getSize();
    sf::Vector2f pixelSize = m_camera.worldToPixelSize(logicSize);

    // Set position
    m_circle.setPosition(pixelPos);

    // Scale based on converted size - use FRUIT_SIZE as base
    float scaleX = pixelSize.x / (FRUIT_SIZE * 2.0f);
    float scaleY = pixelSize.y / (FRUIT_SIZE * 2.0f);
    m_circle.setScale(scaleX, scaleY);
}







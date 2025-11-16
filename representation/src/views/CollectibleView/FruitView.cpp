#include "views/CollectibleView/FruitView.h"

#include "Game.h"
FruitView::FruitView(FruitModel& fruitmodel, sf::RenderWindow& window, Camera& camera): m_fruitmodel(fruitmodel), m_window(window), m_camera(camera) {
    //set shape
    m_circle.setFillColor(sf::Color(0,255,0));
    m_circle.setRadius(FRUIT_SIZE);
    m_circle.setOrigin(FRUIT_SIZE, FRUIT_SIZE);

    updateShape();
}


void FruitView::update(){
    // Update sprite when moving left or right

    // Update sprite when dying

}

void FruitView::draw(sf::RenderWindow& window) {
    m_window.draw(m_circle);
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

    // Scale based on converted size
    float baseRadius = 10.0f;  // Base radius in pixels
    float scaleX = pixelSize.x / baseRadius;
    float scaleY = pixelSize.y / baseRadius;
    m_circle.setScale(scaleX, scaleY);
}







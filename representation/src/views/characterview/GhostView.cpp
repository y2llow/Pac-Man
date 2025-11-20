#include "views/characterview/GhostView.h"

#include "Game.h"

// Base GhostView implementation
GhostView::GhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera)
    : m_ghostmodel(ghostmodel), m_window(window), m_camera(camera) {
    GhostView::setupShape();
    GhostView::updateShape();
}

void GhostView::setupShape() {
    // Default ghost shape - white
    m_circle.setFillColor(sf::Color(255, 255, 255));
}

void GhostView::update() {
    updateShape();
}

void GhostView::draw(sf::RenderWindow& window) {
    window.draw(m_circle);
}

void GhostView::updateShape() {
    sf::Vector2f logicPos = m_ghostmodel.getPosition();
    sf::Vector2f pixelPos = m_camera.worldToPixel(logicPos);

    sf::Vector2f logicSize = m_ghostmodel.getSize();
    sf::Vector2f pixelSize = m_camera.worldToPixelSize(logicSize);


    // Fixed base radius
    float newRadius = std::min(pixelSize.x, pixelSize.y);
    m_circle.setRadius(newRadius);
    m_circle.setOrigin(newRadius, newRadius);
    m_circle.setPosition(pixelPos); // Use world coordinates directly

    // Scale transforms world coordinates to screen coordinates
    // This will stretch the circle into an oval
    float scaleX = pixelSize.x / (newRadius * 2.0f);
    float scaleY = pixelSize.y / (newRadius * 2.0f);
    m_circle.setScale(scaleX, scaleY);
}

// RedGhostView implementation
RedGhostView::RedGhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera)
    : GhostView(ghostmodel, window, camera) {
    RedGhostView::setupShape();
    GhostView::updateShape();
}

void RedGhostView::setupShape() {
    m_circle.setFillColor(sf::Color(233, 3, 8));

}

void RedGhostView::update() {
    GhostView::update();
}

void RedGhostView::draw(sf::RenderWindow& window) {
    GhostView::draw(window);
}

// BlueGhostView implementation
BlueGhostView::BlueGhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera)
    : GhostView(ghostmodel, window, camera) {
    BlueGhostView::setupShape();
    GhostView::updateShape();
}

void BlueGhostView::setupShape() {
    m_circle.setFillColor(sf::Color(6, 176, 232));

}

void BlueGhostView::update() {
    GhostView::update();
}

void BlueGhostView::draw(sf::RenderWindow& window) {
    GhostView::draw(window);
}

// OrangeGhostView implementation
OrangeGhostView::OrangeGhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera)
    : GhostView(ghostmodel, window, camera) {
    OrangeGhostView::setupShape();
    GhostView::updateShape();
}

void OrangeGhostView::setupShape() {
    m_circle.setFillColor(sf::Color(234, 133, 12));
}

void OrangeGhostView::update() {
    GhostView::update();
}

void OrangeGhostView::draw(sf::RenderWindow& window) {
    GhostView::draw(window);
}

// PinkGhostView implementation
PinkGhostView::PinkGhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera)
    : GhostView(ghostmodel, window, camera) {
    PinkGhostView::setupShape();
    GhostView::updateShape();
}

void PinkGhostView::setupShape() {
    m_circle.setFillColor(sf::Color(240, 157, 178));

}

void PinkGhostView::update() {
    GhostView::update();
}

void PinkGhostView::draw(sf::RenderWindow& window) {
    GhostView::draw(window);
}
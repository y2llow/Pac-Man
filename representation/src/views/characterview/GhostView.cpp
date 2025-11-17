#include "views/characterview/GhostView.h"

#include "Game.h"

// Base GhostView implementation
GhostView::GhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera)
    : m_ghostmodel(ghostmodel), m_window(window), m_camera(camera) {
    setupShape();
    updateShape();
}

void GhostView::setupShape() {
    // Default ghost shape - white
    m_circle.setFillColor(sf::Color(255, 255, 255));
    m_circle.setRadius(GHOST_SIZE);
    m_circle.setOrigin(GHOST_SIZE, GHOST_SIZE);
}

void GhostView::update() {
    updateShape();
}

void GhostView::draw(sf::RenderWindow& window) {
    m_window.draw(m_circle);
}

void GhostView::updateShape() {
    // Convert normalized coordinates to pixel coordinates using camera
    sf::Vector2f logicPos = m_ghostmodel.getPosition();
    sf::Vector2f pixelPos = m_camera.worldToPixel(logicPos);

    // Convert normalized size to pixel size
    sf::Vector2f logicSize = m_ghostmodel.getSize();
    sf::Vector2f pixelSize = m_camera.worldToPixelSize(logicSize);

    // Set position
    m_circle.setPosition(pixelPos);

    float newRadius = std::min(pixelSize.x, pixelSize.y) / (GHOST_SIZE * 2.0f);
    m_circle.setRadius(newRadius);
    m_circle.setOrigin(newRadius, newRadius); // Origin opnieuw centreren
}

// RedGhostView implementation
RedGhostView::RedGhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera)
    : GhostView(ghostmodel, window, camera) {
    setupShape();
    updateShape();
}

void RedGhostView::setupShape() {
    m_circle.setFillColor(sf::Color(233, 3, 8));
    m_circle.setRadius(GHOST_SIZE);
    m_circle.setOrigin(GHOST_SIZE, GHOST_SIZE);
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
    setupShape();
    updateShape();
}

void BlueGhostView::setupShape() {
    m_circle.setFillColor(sf::Color(6, 176, 232));
    m_circle.setRadius(GHOST_SIZE);
    m_circle.setOrigin(GHOST_SIZE, GHOST_SIZE);
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
    setupShape();
    updateShape();
}

void OrangeGhostView::setupShape() {
    m_circle.setFillColor(sf::Color(234, 133, 12));
    m_circle.setRadius(GHOST_SIZE);
    m_circle.setOrigin(GHOST_SIZE, GHOST_SIZE);
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
    setupShape();
    updateShape();
}

void PinkGhostView::setupShape() {
    m_circle.setFillColor(sf::Color(240, 157, 178));
    m_circle.setRadius(GHOST_SIZE);
    m_circle.setOrigin(GHOST_SIZE, GHOST_SIZE);
}

void PinkGhostView::update() {
    GhostView::update();
}

void PinkGhostView::draw(sf::RenderWindow& window) {
    GhostView::draw(window);
}
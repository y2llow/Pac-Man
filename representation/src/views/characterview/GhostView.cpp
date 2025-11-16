#include "views/characterview/GhostView.h"

#include "Game.h"

GhostView::GhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera)
    :m_ghostmodel(ghostmodel), m_window(window),m_camera(camera) {

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

    // Scale based on converted size
    float baseRadius = 10.0f;  // Base radius in pixels
    float scaleX = pixelSize.x / baseRadius;
    float scaleY = pixelSize.y / baseRadius;
    m_circle.setScale(scaleX, scaleY);
}

// ---------------------------------------------REDGHOST--------------------------------------------
RedGhostView::RedGhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera)
    : GhostView(ghostmodel, window, camera) {  // Initialize base members

    // Now re-setup with red color (overrides base setup)
    setupShape();
    updateShape();
}

void RedGhostView::setupShape() {
    //set shape
    m_circle.setFillColor(sf::Color(233, 3, 8));
    m_circle.setRadius(GHOST_SIZE);
    m_circle.setOrigin(GHOST_SIZE, GHOST_SIZE);
}

void RedGhostView::update() {
    // Call base update which calls updateShape()
    GhostView::update();
    // auto x = m_ghostmodel.getPosition().x +1;
    // auto y = m_ghostmodel.getPosition().y +1;
    //
    // m_ghostmodel.setPosition(sf::Vector2f(x, y));
}

void RedGhostView::draw(sf::RenderWindow& window) {
    // Use base implementation or add custom drawing logic
    GhostView::draw(window);
}

// ---------------------------------------------BLUEGHOST--------------------------------------------
BlueGhostView::BlueGhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera)
    : GhostView(ghostmodel, window, camera) {  // Initialize base members

    // Now re-setup with red color (overrides base setup)
    setupShape();
    updateShape();
}

void BlueGhostView::setupShape() {
    //set shape
    m_circle.setFillColor(sf::Color(6, 176, 232));
    m_circle.setRadius(GHOST_SIZE);
    m_circle.setOrigin(GHOST_SIZE, GHOST_SIZE);
}

void BlueGhostView::update() {
    // Call base update which calls updateShape()
    GhostView::update();
    // auto x = m_ghostmodel.getPosition().x +1;
    // auto y = m_ghostmodel.getPosition().y +1;
    //
    // m_ghostmodel.setPosition(sf::Vector2f(x, y));
}

void BlueGhostView::draw(sf::RenderWindow& window) {
    // Use base implementation or add custom drawing logic
    GhostView::draw(window);
}

// ---------------------------------------------ORANGEGHOST--------------------------------------------
OrangeGhostView::OrangeGhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera)
    : GhostView(ghostmodel, window,camera) {  // Initialize base members

    // Now re-setup with red color (overrides base setup)
    setupShape();
    updateShape();
}

void OrangeGhostView::setupShape() {
    //set shape
    m_circle.setFillColor(sf::Color(234, 133, 12));
    m_circle.setRadius(GHOST_SIZE);
    m_circle.setOrigin(GHOST_SIZE, GHOST_SIZE);
}

void OrangeGhostView::update() {
    // Call base update which calls updateShape()
    GhostView::update();
    // auto x = m_ghostmodel.getPosition().x +1;
    // auto y = m_ghostmodel.getPosition().y +1;
    //
    // m_ghostmodel.setPosition(sf::Vector2f(x, y));
}

void OrangeGhostView::draw(sf::RenderWindow& window) {
    // Use base implementation or add custom drawing logic
    GhostView::draw(window);
}

// ---------------------------------------------PINKGHOST--------------------------------------------
PinkGhostView::PinkGhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera)
    : GhostView(ghostmodel, window,camera) {  // Initialize base members

    // Now re-setup with red color (overrides base setup)
    setupShape();
    updateShape();
}

void PinkGhostView::setupShape() {
    //set shape
    m_circle.setFillColor(sf::Color(240, 157, 178));
    m_circle.setRadius(GHOST_SIZE);
    m_circle.setOrigin(GHOST_SIZE, GHOST_SIZE);
}

void PinkGhostView::update() {
    // Call base update which calls updateShape()
    GhostView::update();
    // auto x = m_ghostmodel.getPosition().x +1;
    // auto y = m_ghostmodel.getPosition().y +1;
    //
    // m_ghostmodel.setPosition(sf::Vector2f(x, y));
}

void PinkGhostView::draw(sf::RenderWindow& window) {
    // Use base implementation or add custom drawing logic
    GhostView::draw(window);
}

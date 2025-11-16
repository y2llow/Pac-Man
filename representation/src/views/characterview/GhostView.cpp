#include "views/characterview/GhostView.h"

#include "Game.h"

GhostView::GhostView(GhostModel& ghostmodel, sf::RenderWindow& window)
    :m_ghostmodel(ghostmodel), m_window(window) {

    setupShape();
    updateShape();
}

void GhostView::setupShape() {
    // Default ghost shape - white
    m_circle.setFillColor(sf::Color(255, 255, 255));
    m_circle.setRadius(10);
    m_circle.setOrigin(10.0f, 10.0f);
}

void GhostView::update() {
    updateShape();
}

void GhostView::draw(sf::RenderWindow& window) {
    m_window.draw(m_circle);
}

void GhostView::updateShape() {
    // Convert normalized coordinates [-1, 1] to pixel coordinates
    sf::Vector2f logicPos = m_ghostmodel.getPosition();

    const float windowWidth = pacman::representation::Game::WINDOW_WIDTH;
    const float windowHeight = pacman::representation::Game::WINDOW_HEIGHT;

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

// ---------------------------------------------REDGHOST--------------------------------------------
RedGhostView::RedGhostView(GhostModel& ghostmodel, sf::RenderWindow& window)
    : GhostView(ghostmodel, window) {  // Initialize base members

    // Now re-setup with red color (overrides base setup)
    setupShape();
    updateShape();
}

void RedGhostView::setupShape() {
    //set shape
    m_circle.setFillColor(sf::Color(233, 3, 8));
    m_circle.setRadius(10);
    m_circle.setOrigin(10.0f, 10.0f);
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
BlueGhostView::BlueGhostView(GhostModel& ghostmodel, sf::RenderWindow& window)
    : GhostView(ghostmodel, window) {  // Initialize base members

    // Now re-setup with red color (overrides base setup)
    setupShape();
    updateShape();
}

void BlueGhostView::setupShape() {
    //set shape
    m_circle.setFillColor(sf::Color(6, 176, 232));
    m_circle.setRadius(10);
    m_circle.setOrigin(10.0f, 10.0f);
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
OrangeGhostView::OrangeGhostView(GhostModel& ghostmodel, sf::RenderWindow& window)
    : GhostView(ghostmodel, window) {  // Initialize base members

    // Now re-setup with red color (overrides base setup)
    setupShape();
    updateShape();
}

void OrangeGhostView::setupShape() {
    //set shape
    m_circle.setFillColor(sf::Color(234, 133, 12));
    m_circle.setRadius(10);
    m_circle.setOrigin(10.0f, 10.0f);
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
PinkGhostView::PinkGhostView(GhostModel& ghostmodel, sf::RenderWindow& window)
    : GhostView(ghostmodel, window) {  // Initialize base members

    // Now re-setup with red color (overrides base setup)
    setupShape();
    updateShape();
}

void PinkGhostView::setupShape() {
    //set shape
    m_circle.setFillColor(sf::Color(240, 157, 178));
    m_circle.setRadius(10);
    m_circle.setOrigin(10.0f, 10.0f);
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

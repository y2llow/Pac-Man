#include "views/characterview/GhostView.h"
#include "Game.h"

// Base GhostView implementation
GhostView::GhostView(GhostModel& ghostmodel,  Camera& camera)
    : m_ghostmodel(ghostmodel),  m_camera(camera) {
    GhostView::setupShape();
    GhostView::updateShape();
}

void GhostView::setupShape() {
    // Default ghost shape - will be set by derived classes
    m_circle.setFillColor(sf::Color(255, 255, 255));
    m_normalColor = sf::Color(255, 255, 255); // Store normal color
}

void GhostView::update() {
    updateShape();

    if (m_ghostmodel.isScared()) {
        float scaredTimer = m_ghostmodel.getScaredTimer();

        // Blink between blue and white when timer is below 3 seconds
        if (scaredTimer <= 3.0f) {
            // Accelerating blink speed as timer approaches 0
            // Start slow (0.5s per phase) and speed up to very fast (0.1s per phase)
            float timeRemaining = scaredTimer; // 3.0 to 0.0
            float blinkSpeed = 0.1f + (timeRemaining / 3.0f) * 0.4f; // 0.1s to 0.5s

            // Calculate blink phase with accelerating speed
            float blinkTime = 3.0f - timeRemaining; // Time since blinking started (0.0 to 3.0)
            int blinkPhase = static_cast<int>(blinkTime / blinkSpeed) % 2;

            if (blinkPhase == 0) {
                m_circle.setFillColor(sf::Color(0, 0, 255)); // Blue
            } else {
                m_circle.setFillColor(sf::Color(255, 255, 255)); // White
            }
        } else {
            m_circle.setFillColor(sf::Color(0, 0, 255)); // Solid blue
        }
    } else {
        m_circle.setFillColor(m_normalColor); // Revert to normal color
    }
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
    m_circle.setPosition(pixelPos);

    // Scale transforms world coordinates to screen coordinates
    float scaleX = pixelSize.x / (newRadius * 2.0f);
    float scaleY = pixelSize.y / (newRadius * 2.0f);
    m_circle.setScale(scaleX, scaleY);
}

// RedGhostView implementation
RedGhostView::RedGhostView(GhostModel& ghostmodel,  Camera& camera)
    : GhostView(ghostmodel,camera) {
    RedGhostView::setupShape();
    GhostView::updateShape();
}

void RedGhostView::setupShape() {
    m_normalColor = sf::Color(233, 3, 8);
    m_circle.setFillColor(m_normalColor);
}

void RedGhostView::update() {
    GhostView::update();
}

void RedGhostView::draw(sf::RenderWindow& window) {
    GhostView::draw(window);
}

// BlueGhostView implementation
BlueGhostView::BlueGhostView(GhostModel& ghostmodel, Camera& camera)
    : GhostView(ghostmodel,  camera) {
    BlueGhostView::setupShape();
    GhostView::updateShape();
}

void BlueGhostView::setupShape() {
    m_normalColor = sf::Color(6, 176, 232);
    m_circle.setFillColor(m_normalColor);
}

void BlueGhostView::update() {
    GhostView::update();
}

void BlueGhostView::draw(sf::RenderWindow& window) {
    GhostView::draw(window);
}

// OrangeGhostView implementation
OrangeGhostView::OrangeGhostView(GhostModel& ghostmodel,  Camera& camera)
    : GhostView(ghostmodel,  camera) {
    OrangeGhostView::setupShape();
    GhostView::updateShape();
}

void OrangeGhostView::setupShape() {
    m_normalColor = sf::Color(234, 133, 12);
    m_circle.setFillColor(m_normalColor);
}

void OrangeGhostView::update() {
    GhostView::update();
}

void OrangeGhostView::draw(sf::RenderWindow& window) {
    GhostView::draw(window);
}

// PinkGhostView implementation
PinkGhostView::PinkGhostView(GhostModel& ghostmodel,  Camera& camera)
    : GhostView(ghostmodel, camera) {
    PinkGhostView::setupShape();
    GhostView::updateShape();
}

void PinkGhostView::setupShape() {
    m_normalColor = sf::Color(240, 157, 178);
    m_circle.setFillColor(m_normalColor);
}

void PinkGhostView::update() {
    GhostView::update();
}

void PinkGhostView::draw(sf::RenderWindow& window) {
    GhostView::draw(window);
}
#include "views/characterview/GhostView.h"
#include <utility>
#include "Game.h"
#include "rendering/SpriteSheet.h"

namespace pacman::representation::views {

using logic::entities::GhostModel;
using logic::Vector2f;

// Base GhostView implementation
GhostView::GhostView(std::shared_ptr<GhostModel> ghostmodel, Camera& camera)
    : m_ghostmodel(std::move(ghostmodel)), m_camera(camera), m_animationTimer(0.0f) {

    auto& spriteSheet = rendering::SpriteSheet::getInstance();
    m_sprite.setTexture(spriteSheet.getTexture());

    GhostView::updateSprite();
}

void GhostView::setupSprite() {
    // Default - will be overridden by derived classes
    m_normalColor = sf::Color(255, 255, 255);
}

void GhostView::update(float deltaTime) {
    m_animationTimer += deltaTime;
    updateSprite();
}

void GhostView::onModelChanged() {
    updateSprite();
}


void GhostView::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

void GhostView::updateSprite() {
    auto& spriteSheet = rendering::SpriteSheet::getInstance();

    std::string spriteId;

    if (m_ghostmodel->isScared()) {
        float scaredTimer = m_ghostmodel->getScaredTimer();

        // Blink between blue and white when timer is below 3 seconds
        if (scaredTimer <= 3.0f) {
            float timeRemaining = scaredTimer;
            float blinkSpeed = 0.1f + (timeRemaining / 3.0f) * 0.4f;
            float blinkTime = 3.0f - timeRemaining;
            int blinkPhase = static_cast<int>(blinkTime / blinkSpeed) % 2;

            // Animate between frames based on timer
            int frameIndex = static_cast<int>(m_animationTimer / 0.2f) % 2;

            std::string ghost_scared = frameIndex == 0 ? "ghost_scared_1" : "ghost_scared_2";
            std::string ghost_blink_scared = frameIndex == 0 ? "ghost_blink_scared_1" : "ghost_blink_scared_2";

            spriteId = blinkPhase == 0 ? ghost_scared : ghost_blink_scared;
        } else {
            // Normal scared animation (not blinking yet)
            int frameIndex = static_cast<int>(m_animationTimer / 0.2f) % 2;
            spriteId = frameIndex == 0 ? "ghost_scared_1" : "ghost_scared_2";
        }
    } else {
        // Normal ghost - select sprite based on direction
        int direction = m_ghostmodel->getDirection();
        int frameIndex = static_cast<int>(m_animationTimer / 0.2f) % 2;

        std::string directionStr;
        switch (direction) {
            case 0: directionStr = "left"; break;
            case 1: directionStr = "down"; break;
            case 2: directionStr = "right"; break;
            case 3: directionStr = "up"; break;
            default: directionStr = "right"; break;
        }

        std::string ghostColor = getGhostColor();
        spriteId = "ghost_" + ghostColor + "_" + directionStr + "_" + std::to_string(frameIndex + 1);
    }

    m_sprite.setTextureRect(spriteSheet.getSpriteRect(spriteId));

    // Position and scale
    Vector2f logicPos = m_ghostmodel->getPosition();
    Vector2f pixelPos = m_camera.worldToPixel(logicPos);

    Vector2f logicSize = m_ghostmodel->getSize();
    Vector2f pixelSize = m_camera.worldToPixelSize(logicSize);

    sf::IntRect textureRect = m_sprite.getTextureRect();
    float scaleX = pixelSize.x / textureRect.width;
    float scaleY = pixelSize.y / textureRect.height;
    m_sprite.setScale(scaleX, scaleY);

    m_sprite.setOrigin(textureRect.width / 2.0f, textureRect.height / 2.0f);
    m_sprite.setPosition(pixelPos.x, pixelPos.y);
}

std::string GhostView::getGhostColor() const {
    return "red"; // Default
}

// RedGhostView implementation
RedGhostView::RedGhostView(std::shared_ptr<GhostModel> ghostmodel, Camera& camera)
    : GhostView(std::move(ghostmodel), camera) {
}

void RedGhostView::setupSprite() {
    m_normalColor = sf::Color(233, 3, 8);
}

std::string RedGhostView::getGhostColor() const {
    return "red";
}

void RedGhostView::update(float deltaTime) {
    GhostView::update(deltaTime);
}

void RedGhostView::draw(sf::RenderWindow& window) {
    GhostView::draw(window);
}

// BlueGhostView implementation
BlueGhostView::BlueGhostView(std::shared_ptr<GhostModel> ghostmodel, Camera& camera)
    : GhostView(std::move(ghostmodel), camera) {
}

void BlueGhostView::setupSprite() {
    m_normalColor = sf::Color(6, 176, 232);
}

std::string BlueGhostView::getGhostColor() const {
    return "blue";
}

void BlueGhostView::update(float deltaTime) {
    GhostView::update(deltaTime);
}

void BlueGhostView::draw(sf::RenderWindow& window) {
    GhostView::draw(window);
}

// OrangeGhostView implementation
OrangeGhostView::OrangeGhostView(std::shared_ptr<GhostModel> ghostmodel, Camera& camera)
    : GhostView(std::move(ghostmodel), camera) {
}

void OrangeGhostView::setupSprite() {
    m_normalColor = sf::Color(234, 133, 12);
}

std::string OrangeGhostView::getGhostColor() const {
    return "orange";
}

void OrangeGhostView::update(float deltaTime) {
    GhostView::update(deltaTime);
}

void OrangeGhostView::draw(sf::RenderWindow& window) {
    GhostView::draw(window);
}

// PinkGhostView implementation
PinkGhostView::PinkGhostView(std::shared_ptr<GhostModel> ghostmodel, Camera& camera)
    : GhostView(std::move(ghostmodel), camera) {
}

void PinkGhostView::setupSprite() {
    m_normalColor = sf::Color(240, 157, 178);
}

std::string PinkGhostView::getGhostColor() const {
    return "pink";
}

void PinkGhostView::update(float deltaTime) {
    GhostView::update(deltaTime);
}

void PinkGhostView::draw(sf::RenderWindow& window) {
    GhostView::draw(window);
}
void RedGhostView::onModelChanged() {
    GhostView::onModelChanged();
}

void BlueGhostView::onModelChanged() {
    GhostView::onModelChanged();
}

void OrangeGhostView::onModelChanged() {
    GhostView::onModelChanged();
}

void PinkGhostView::onModelChanged() {
    GhostView::onModelChanged();
}
} // namespace pacman::representation::views
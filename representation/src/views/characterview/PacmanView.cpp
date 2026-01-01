#include "views/characterview/PacmanView.h"
#include "Game.h"
#include "entities/PacmanModel.h"
#include "rendering/SpriteSheet.h"
#include "core/Stopwatch.h"

namespace pacman::representation::views {

using logic::entities::PacmanModel;
using logic::Vector2f;

PacmanView::PacmanView(std::shared_ptr<PacmanModel> pacmanModel, Camera& camera)
    : m_pacmanmodel(std::move(pacmanModel)), m_camera(camera), m_animationTimer(0.0f) {

    // Setup sprite met texture van sprite sheet
    auto& spriteSheet = rendering::SpriteSheet::getInstance();
    m_sprite.setTexture(spriteSheet.getTexture());
    updateShape();
}

void PacmanView::update(float deltaTime) {
    // ✨ AANGEPAST - Alleen animatie timers hier
    m_animationTimer += deltaTime;

    if (m_pacmanmodel->isDying()) {
        m_deathAnimationTimer += deltaTime;
    } else {
        m_deathAnimationTimer = 0.0f;
    }

    // Update shape elke frame voor smooth animation
    updateShape();
}

void PacmanView::onModelChanged() {
    // React op model changes (positie, direction, death)
    // Update shape immediately when model changes
    updateShape();
}

void PacmanView::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

void PacmanView::updateShape() {
    auto& spriteSheet = rendering::SpriteSheet::getInstance();
    std::string spriteId;

    if (m_pacmanmodel->isDying()) {
        // Death animation takes priority
        spriteId = getDeathAnimationSprite();
    } else {
        // Normal movement animation
        int frameIndex = static_cast<int>(m_animationTimer / 0.1f) % 3;
        int direction = m_pacmanmodel->getDirection();

        switch (direction) {
            case 0: // Links
                spriteId = frameIndex == 0 ? "pacman_left_closed" :
                          frameIndex == 1 ? "pacman_left_half" : "pacman_left_open";
                break;
            case 1: // Beneden
                spriteId = frameIndex == 0 ? "pacman_down_closed" :
                          frameIndex == 1 ? "pacman_down_half" : "pacman_down_open";
                break;
            case 2: // Rechts
                spriteId = frameIndex == 0 ? "pacman_right_closed" :
                          frameIndex == 1 ? "pacman_right_half" : "pacman_right_open";
                break;
            case 3: // Boven
                spriteId = frameIndex == 0 ? "pacman_up_closed" :
                          frameIndex == 1 ? "pacman_up_half" : "pacman_up_open";
                break;
        }
    }

    // Set texture rectangle
    m_sprite.setTextureRect(spriteSheet.getSpriteRect(spriteId));

    // Convert normalized coordinates to pixel coordinates
    Vector2f logicPos = m_pacmanmodel->getPosition();
    Vector2f pixelPos = m_camera.worldToPixel(logicPos);

    Vector2f logicSize = m_pacmanmodel->getSize();
    Vector2f pixelSize = m_camera.worldToPixelSize(logicSize);

    // Set sprite scale
    sf::IntRect textureRect = m_sprite.getTextureRect();
    float scaleX = pixelSize.x / textureRect.width;
    float scaleY = pixelSize.y / textureRect.height;
    m_sprite.setScale(scaleX, scaleY);

    // Set origin to center
    m_sprite.setOrigin(textureRect.width / 2.0f, textureRect.height / 2.0f);

    // Set position
    m_sprite.setPosition(pixelPos.x, pixelPos.y);
}

std::string PacmanView::getDeathAnimationSprite() const {
    // Map death animation time to sprite frames
    // Total death animation duration is 2 seconds, we have 11 frames
    float deathProgress = m_deathAnimationTimer / 2.0f; // 0 to 1
    int frameIndex = static_cast<int>(deathProgress * 10); // 0 to 10

    // Clamp to valid range
    frameIndex = std::min(frameIndex, 10);
    frameIndex = std::max(frameIndex, 0);

    return "pacman_death_" + std::to_string(frameIndex);
}

} // namespace pacman::representation::views
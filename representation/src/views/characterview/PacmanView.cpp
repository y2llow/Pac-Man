#include "views/characterview/PacmanView.h"
#include "Game.h"
#include "entities/PacmanModel.h"
#include "rendering/SpriteSheet.h"
#include "core/Stopwatch.h"  // NIEUW

PacmanView::PacmanView(std::shared_ptr<PacmanModel> pacmanModel, Camera& camera)
    : m_pacmanmodel(std::move(pacmanModel)), m_camera(camera), m_animationTimer(0.0f) {

    // Setup sprite met texture van sprite sheet
    auto& spriteSheet = SpriteSheet::getInstance();
    m_sprite.setTexture(spriteSheet.getTexture());

    updateShape();
}

void PacmanView::update(float deltaTime) {
    m_animationTimer += deltaTime;
    updateShape();
}

void PacmanView::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

void PacmanView::updateShape() {
    auto& spriteSheet = SpriteSheet::getInstance();

    // Bepaal welke animatie frame te gebruiken (0.1 seconden per frame)
    int frameIndex = static_cast<int>(m_animationTimer / 0.1f) % 3;

    // Kies sprite op basis van richting en animatie frame
    std::string spriteId;
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

    // Set texture rectangle
    m_sprite.setTextureRect(spriteSheet.getSpriteRect(spriteId));

    // Convert normalized coordinates to pixel coordinates
    Vector2f logicPos = m_pacmanmodel->getPosition();
    Vector2f pixelPos = m_camera.worldToPixel(logicPos);

    Vector2f logicSize = m_pacmanmodel->getSize();
    Vector2f pixelSize = m_camera.worldToPixelSize(logicSize);

    // Set sprite scale om de juiste grootte te krijgen
    sf::IntRect textureRect = m_sprite.getTextureRect();
    float scaleX = pixelSize.x / textureRect.width;
    float scaleY = pixelSize.y / textureRect.height;
    m_sprite.setScale(scaleX, scaleY);

    // Set origin to center
    m_sprite.setOrigin(textureRect.width / 2.0f, textureRect.height / 2.0f);

    // Set position
    m_sprite.setPosition(pixelPos.x, pixelPos.y);
}
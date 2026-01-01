#include "views/CollectibleView/FruitView.h"
#include "Game.h"
#include "entities/FruitModel.h"
#include "rendering/SpriteSheet.h"

namespace pacman::representation::views {

using logic::entities::FruitModel;
using logic::Vector2f;

FruitView::FruitView(std::shared_ptr<FruitModel> fruitmodel, Camera& camera)
    : m_fruitmodel(std::move(fruitmodel)), m_camera(camera) {

    // Setup sprite met texture van sprite sheet
    auto& spriteSheet = rendering::SpriteSheet::getInstance();
    m_sprite.setTexture(spriteSheet.getTexture());

    updateShape();
    updateSprite();
}

void FruitView::update(float deltaTime) {
    // Animaties kunnen hier
}

void FruitView::onModelChanged() {
    updateSprite();
}

void FruitView::updateSprite() {
    // Sync visual representation with model state
    updateShape();
}

void FruitView::draw(sf::RenderWindow& window) {
    if (shouldRender()) {
        window.draw(m_sprite);
    }
}

bool FruitView::shouldRender() const {
    return m_fruitmodel && !m_fruitmodel->isCollected();
}

void FruitView::updateShape() {
    if (!m_fruitmodel) return;

    if (m_fruitmodel->isCollected()) {
        return;
    }

    // Set the fruit sprite
    auto& spriteSheet = rendering::SpriteSheet::getInstance();

    std::string spriteId = "burger"; // default

    m_sprite.setTextureRect(spriteSheet.getSpriteRect(spriteId));

    // Convert normalized coordinates to pixel coordinates using camera
    Vector2f logicPos = m_fruitmodel->getPosition();
    Vector2f pixelPos = m_camera.worldToPixel(logicPos);

    // Convert normalized size to pixel size
    Vector2f logicSize = m_fruitmodel->getSize();
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

} // namespace pacman::representation::views
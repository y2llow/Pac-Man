#include "views/CollectibleView/FruitView.h"
#include "Game.h"
#include "entities/FruitModel.h"
#include "rendering/SpriteSheet.h"

FruitView::FruitView(std::shared_ptr<FruitModel> fruitmodel, Camera& camera)
    : m_fruitmodel(std::move(fruitmodel)), m_camera(camera) {

    // Setup sprite met texture van sprite sheet
    auto& spriteSheet = SpriteSheet::getInstance();
    m_sprite.setTexture(spriteSheet.getTexture());

    updateShape();
    updateSprite();
}

void FruitView::update(float deltaTime) {
    // Fruits don't animate, but we still need the signature
    updateSprite();
}

void FruitView::updateSprite() {
    // Sync visual representation with model state
    updateShape();
}

void FruitView::draw(sf::RenderWindow& window) {
    if (shouldRender()) {
        window.draw(m_sprite);  // CORRECTIE: gebruik m_sprite ipv m_circle
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
    auto& spriteSheet = SpriteSheet::getInstance();

    // Kies de juiste fruit sprite op basis van type (als je verschillende fruit types hebt)
    std::string spriteId = "burger"; // default

    // Als je verschillende fruit types ondersteunt:
    // switch (m_fruitmodel->getType()) {
    //     case FruitModel::Type::CHERRY: spriteId = "fruit_cherry"; break;
    //     case FruitModel::Type::STRAWBERRY: spriteId = "fruit_strawberry"; break;
    //     case FruitModel::Type::ORANGE: spriteId = "fruit_orange"; break;
    //     case FruitModel::Type::APPLE: spriteId = "fruit_apple"; break;
    //     case FruitModel::Type::MELON: spriteId = "fruit_melon"; break;
    //     default: spriteId = "fruit"; break;
    // }

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
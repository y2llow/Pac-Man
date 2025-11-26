#include "views/CollectibleView/CoinView.h"
#include "Game.h"
#include "entities/CoinModel.h"
#include "rendering/SpriteSheet.h"  // NIEUW: voor sprite support

CoinView::CoinView(std::shared_ptr<CoinModel> coinModel, Camera& camera)
    : m_coinModel(std::move(coinModel)), m_camera(camera) {

    // Setup sprite met texture van sprite sheet
    auto& spriteSheet = SpriteSheet::getInstance();
    m_sprite.setTexture(spriteSheet.getTexture());

    updateShape();
    updateSprite();
}

void CoinView::update(float deltaTime) {
    updateSprite();
}

void CoinView::updateSprite() {
    // Sync visual representation with model state
    updateShape();
}

void CoinView::draw(sf::RenderWindow& window) {
    if (shouldRender()) {
        window.draw(m_sprite);
    }
}

bool CoinView::shouldRender() const {
    return m_coinModel && !m_coinModel->isCollected();
}

void CoinView::updateShape() {
    if (!m_coinModel) return;

    if (m_coinModel->isCollected()) {
        return;
    }

    // Set the coin sprite
    auto& spriteSheet = SpriteSheet::getInstance();
    m_sprite.setTextureRect(spriteSheet.getSpriteRect("coin"));

    // Convert normalized coordinates to pixel coordinates using camera
    Vector2f logicPos = m_coinModel->getPosition();
    Vector2f pixelPos = m_camera.worldToPixel(logicPos);

    // Convert normalized size to pixel size
    Vector2f logicSize = m_coinModel->getSize();
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
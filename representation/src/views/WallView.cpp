#include "views/WallView.h"
#include "entities/WallModel.h"
#include "Camera.h"

namespace pacman::representation::views {

using logic::entities::WallModel;
using logic::Vector2f;

WallView::WallView(std::shared_ptr<WallModel> model, Camera& camera)
    : m_model(std::move(model)), m_camera(camera) {
    setupRectangle();
    updateShape();
}

void WallView::setupRectangle() {
    m_shape.setFillColor(sf::Color(33, 33, 255));
}

void WallView::update(float deltaTime) {
    // Walls don't animate - nothing to do here anymore
}

void WallView::onModelChanged() {
    // Als de wall's positie/size zou veranderen, update de shape
    updateShape();
}

void WallView::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
}

void WallView::updateShape() {
    if (!m_model) return;

    // Convert normalized coordinates to pixel coordinates
    Vector2f logicPos = m_model->getPosition();
    Vector2f pixelPos = m_camera.worldToPixel(logicPos);

    // Convert normalized size to pixel size
    Vector2f logicSize = m_model->getSize();
    Vector2f pixelSize = m_camera.worldToPixelSize(logicSize);

    pixelSize.x = pixelSize.x * 0.9f;
    pixelSize.y = pixelSize.y * 0.9f;

    m_shape.setSize({pixelSize.x, pixelSize.y});
    m_shape.setOrigin(pixelSize.x / 2.0f, pixelSize.y / 2.0f);
    m_shape.setPosition(pixelPos.x, pixelPos.y);
}

} // namespace pacman::representation::views
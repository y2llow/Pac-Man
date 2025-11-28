#include "views/DoorView.h"
#include "entities/DoorModel.h"  // Zorg dat dit pad correct is!
#include "Camera.h"

DoorView::DoorView(std::shared_ptr<DoorModel> model, Camera& camera)
    : m_model(std::move(model)), m_camera(camera) {
    setupRectangle();
    updateShape();
}

void DoorView::setupRectangle() {
    m_shape.setFillColor(sf::Color(120, 120, 180));
}

void DoorView::update(float deltaTime) {
    // Doors don't animate, but we must implement this pure virtual function
    updateShape();
}

void DoorView::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
}

void DoorView::updateShape() {
    if (!m_model) return;

    // Convert normalized coordinates to pixel coordinates
    Vector2f logicPos = m_model->getPosition();
    Vector2f pixelPos = m_camera.worldToPixel(logicPos);

    // Convert normalized size to pixel size
    Vector2f logicSize = m_model->getSize();
    Vector2f pixelSize = m_camera.worldToPixelSize(logicSize);

    pixelSize.x = pixelSize.x *0.9;
    pixelSize.y = pixelSize.y *0.9;

    m_shape.setSize({pixelSize.x , pixelSize.y});
    m_shape.setOrigin(pixelSize.x / 2.0f, pixelSize.y / 2.0f);
    m_shape.setPosition(pixelPos.x, pixelPos.y);
}
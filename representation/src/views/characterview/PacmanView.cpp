#include "views/characterview/PacmanView.h"

#include "Game.h"
#include "entities/PacmanModel.h"

PacmanView::PacmanView(PacmanModel& coinModel,  Camera& camera)
     : m_pacmanmodel(coinModel),  m_camera(camera) {
    m_circle.setFillColor(sf::Color(252, 252, 2));
    updateShape();
     }

void PacmanView::update(){
    // Update sprite when moving left or right
    updateShape();

    // Update sprite when dying

}

void PacmanView::draw(sf::RenderWindow& window) {
    window.draw(m_circle);
}

void PacmanView::updateShape() {
    // Convert normalized coordinates to pixel coordinates using camera
    Vector2f logicPos = m_pacmanmodel.getPosition();
    Vector2f pixelPos = m_camera.worldToPixel(logicPos);

    // Convert normalized size to pixel size
    Vector2f logicSize = m_pacmanmodel.getSize();
    Vector2f pixelSize = m_camera.worldToPixelSize(logicSize);

    // Fixed base radius
    float newRadius = std::min(pixelSize.x, pixelSize.y);
    m_circle.setRadius(newRadius);
    m_circle.setOrigin(newRadius, newRadius);
    m_circle.setPosition(pixelPos.x , pixelPos.y); // Use world coordinates directly

    // Scale transforms world coordinates to screen coordinates
    // This will stretch the circle into an oval
    float scaleX = pixelSize.x / (newRadius * 2.0f);
    float scaleY = pixelSize.y / (newRadius * 2.0f);
    m_circle.setScale(scaleX, scaleY);
}


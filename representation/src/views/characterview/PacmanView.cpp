#include "views/characterview/PacmanView.h"

#include "Game.h"
#include "entities/PacmanModel.h"

PacmanView::PacmanView(PacmanModel& coinModel, sf::RenderWindow& window, Camera& camera)
     : m_pacmanmodel(coinModel), m_window(window), m_camera(camera) {
    m_circle.setFillColor(sf::Color(252, 252, 2));
    m_circle.setRadius(PACMAN_SIZE);
    m_circle.setOrigin(PACMAN_SIZE, PACMAN_SIZE);

    updateShape();
     }

void PacmanView::update(){
    // Update sprite when moving left or right
    updateShape();

    // Update sprite when dying

}

void PacmanView::draw(sf::RenderWindow& window) {

    m_window.draw(m_circle);
}

void PacmanView::updateShape() {
    // Convert normalized coordinates to pixel coordinates using camera
    sf::Vector2f logicPos = m_pacmanmodel.getPosition();
    sf::Vector2f pixelPos = m_camera.worldToPixel(logicPos);

    // Convert normalized size to pixel size
    sf::Vector2f logicSize = m_pacmanmodel.getSize();
    sf::Vector2f pixelSize = m_camera.worldToPixelSize(logicSize);

    // Set position
    m_circle.setPosition(pixelPos);

    // Scale based on converted size
    float baseRadius = 10.0f;  // Base radius in pixels
    float scaleX = pixelSize.x / baseRadius;
    float scaleY = pixelSize.y / baseRadius;
    m_circle.setScale(scaleX, scaleY);
}



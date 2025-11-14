#include "views/characterview/PacmanView.h"

#include "Game.h"
#include "entities/PacmanModel.h"

PacmanView::PacmanView(PacmanModel& coinModel, sf::RenderWindow& window)
     : m_pacmanmodel(coinModel), m_window(window){
    m_circle.setFillColor(sf::Color(255,255,0));
    m_circle.setRadius(10);
    m_circle.setOrigin(10.0f, 10.0f);

    updateShape();
     }

void PacmanView::update(){
    // Update sprite when moving left or right

    // Update sprite when dying

}

void PacmanView::draw(sf::RenderWindow& window) {
     m_circle.setOrigin(m_pacmanmodel.getPosition());
    m_window.draw(m_circle);
}

void PacmanView::updateShape() {
    // Convert normalized coordinates [-1, 1] to pixel coordinates
    sf::Vector2f logicPos = m_pacmanmodel.getPosition();

    const float windowWidth = pacman::representation::Game::WINDOW_WIDTH;
    const float windowHeight = pacman::representation::Game::WINDOW_HEIGHT;

    // Convert from normalized [-1,1] to pixel coordinates [0,800]
    float pixelX = (logicPos.x + 1.0f) * (windowWidth / 2.0f);
    float pixelY = (logicPos.y + 1.0f) * (windowHeight / 2.0f);

    // Set position - circle is already centered due to setOrigin
    m_circle.setPosition(pixelX, pixelY);

    // Optional: Scale based on coin size if needed
    sf::Vector2f logicSize = m_pacmanmodel.getSize();
    float scaleX = logicSize.x * 15.0f;  // Adjust scaling factor as needed
    float scaleY = logicSize.y * 15.0f;
    m_circle.setScale(scaleX, scaleY);
}



#include "views/CollectibleView/FruitView.h"

#include "Game.h"
FruitView::FruitView(FruitModel& fruitmodel, sf::RenderWindow& window): m_fruitmodel(fruitmodel), m_window(window) {
    //set shape
    m_circle.setFillColor(sf::Color(0,255,0));
    m_circle.setRadius(5);
    m_circle.setOrigin(5.0f, 5.0f);

    updateShape();
}


void FruitView::update(){
    // Update sprite when moving left or right

    // Update sprite when dying

}

void FruitView::draw(sf::RenderWindow& window) {
    m_window.draw(m_circle);
}

void FruitView::updateShape() {
    // Convert normalized coordinates [-1, 1] to pixel coordinates
    sf::Vector2f logicPos = m_fruitmodel.getPosition();

    const float windowWidth = pacman::representation::Game::WINDOW_WIDTH;
    const float windowHeight = pacman::representation::Game::WINDOW_HEIGHT;

    // Convert from normalized [-1,1] to pixel coordinates [0,800]
    float pixelX = (logicPos.x + 1.0f) * (windowWidth / 2.0f);
    float pixelY = (logicPos.y + 1.0f) * (windowHeight / 2.0f);

    // Set position - circle is already centered due to setOrigin
    m_circle.setPosition(pixelX, pixelY);

    // Optional: Scale based on coin size if needed
    sf::Vector2f logicSize = m_fruitmodel.getSize();
    float scaleX = logicSize.x * 15.0f;  // Adjust scaling factor as needed
    float scaleY = logicSize.y * 15.0f;
    m_circle.setScale(scaleX, scaleY);
}







#include "states/LevelState.h"

#include "StateManger.h"
#include "states/PausedState.h"

#include <iostream>
#include <memory>

LevelState::LevelState(StateManager& stateManager, sf::RenderWindow& window)
    : State(stateManager), m_window(window), m_factory(std::make_unique<SFMLFactory>(window)), m_camera(window.getSize()) {
}


/**
 * Set window, load in walls, coins, fruits, pac-man and ghosts from map by using factory
 */
void LevelState::initialize() {
    // Optional: Add a centered background panel like MenuState
    m_backgroundPanel.setSize(sf::Vector2f(500, 350));
    m_backgroundPanel.setFillColor(sf::Color(200, 33, 0, 220)); // Same blue as MenuState
    m_backgroundPanel.setOutlineColor(sf::Color(255, 255, 0)); // Yellow border
    m_backgroundPanel.setOutlineThickness(3);
    m_backgroundPanel.setOrigin(100, 125); // Center the panel
    m_backgroundPanel.setPosition(600 / 2, 600 / 2);
}

void LevelState::update(float deltaTime) {
    // Simple test - replace with your World update
}

void LevelState::render() {
    m_window.clear(sf::Color(5, 5, 20));
    m_window.draw(m_backgroundPanel);
}


/**
 * stateManager -> PausedState when esc is pressed
 * @param event current SFML event
 */
void LevelState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Escape:
            m_stateManager.pushState(std::make_unique<PausedState>(m_stateManager, m_window));
            break;default: ;
        }
    }
}

void LevelState::loadMapFromFile(const std::string& filename){
}
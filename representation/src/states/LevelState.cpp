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
    // read characters from maps
    // make
}

void LevelState::update(float deltaTime) {
    // Simple test - replace with your World update
}

void LevelState::render() {
    m_window.clear(sf::Color::Blue);  // Maze-like background
    // m_window.draw(m_testShape);       // Simple Pac-Man placeholder
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
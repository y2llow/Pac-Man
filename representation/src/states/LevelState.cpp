#include "states/LevelState.h"

#include "StateManger.h"
#include "states/PausedState.h"

#include <fstream>
#include <iostream>
#include <memory>

LevelState::LevelState(StateManager& stateManager, sf::RenderWindow& window, Camera& camera)
    : State(stateManager), m_window(window),
      m_factory(std::make_unique<SFMLFactory>(window, camera)),
      m_camera(camera) {
}

/**
 * Set window, load in walls, coins, fruits, pac-man and ghosts from map by using factory
 */
void LevelState::initialize() {
    // Reset the view to match current window size
    sf::Vector2u windowSize = m_window.getSize();
    sf::FloatRect visibleArea(0, 0, windowSize.x, windowSize.y);
    m_window.setView(sf::View(visibleArea));

    //initialise world
    m_world = std::make_unique<World>(m_window.getSize(), *m_factory);
    m_world->initialize();
}

void LevelState::update(float deltaTime) {
    if (m_world) {
        m_world->update(deltaTime);
    }
}

void LevelState::render() {
    m_window.clear(sf::Color(5, 5, 20));

    for (const auto& view : m_factory->getViews()) {
        if (view) {
            view->draw(m_window);
        }
    }

    m_window.display();
}

/**
 * stateManager -> PausedState when esc is pressed
 * @param event current SFML event
 */
void LevelState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Escape:
            m_stateManager.pushState(std::make_unique<PausedState>(m_stateManager, m_window, m_camera));
            break;default: ;
        }
    }
}
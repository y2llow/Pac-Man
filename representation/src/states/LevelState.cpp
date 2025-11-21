#include "states/LevelState.h"
#include "StateManger.h"
#include "states/PausedState.h"
#include <fstream>
#include <iostream>
#include <memory>


LevelState::LevelState(StateManager& stateManager, sf::RenderWindow& window, Camera& camera)
    : State(stateManager), m_window(window),
      m_factory(std::make_unique<SFMLFactory>(window, camera)), // Pass reference
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

    // Update camera with current window size
    m_camera.updateWindowSize();

    // Initialize world without window size
    m_world = std::make_unique<World>(*m_factory);
    m_world->initialize();

    updateLayout();
}

/**
 * Handle window resizing - update all positions based on current window size
 * Follows the same pattern as MenuState::updateLayout()
 */
void LevelState::updateLayout() {
    Vector2f windowSize;
    windowSize.x = m_window.getSize().x ;
    windowSize.y = m_window.getSize().y ;

    // Update camera with new window size
    m_camera.updateWindowSize(Vector2f(windowSize)); // Add this method to Camera if needed

    // Reset the view
    sf::FloatRect visibleArea(0, 0, windowSize.x, windowSize.y);
    m_window.setView(sf::View(visibleArea));

    // // Update world and factory
    // if (m_world) {
    //     m_world->handleResize(windowSize);
    // }

    if (m_factory) {
        m_factory->handleResize(windowSize); // Remove camera parameter
    }
}

void LevelState::update(float deltaTime) {
    if (m_world) {
        m_world->update(deltaTime);
    }

    // Add this line - clean up collected views after world update
    if (m_factory) {
        m_factory->cleanupCollectedViews();
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
    // Always handle resize first
    if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        m_window.setView(sf::View(visibleArea));
        updateLayout();
        return; // Important: return after handling resize
    }

    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Escape:
            m_stateManager.pushState(std::make_unique<PausedState>(m_stateManager, m_window, m_camera));
            break;
        default:
            break;
        }
    }
}


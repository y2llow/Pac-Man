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

    // Update camera with current window size
    m_camera.updateWindowSize();

    // Initialize world
    m_world = std::make_unique<World>(m_window.getSize(), *m_factory);
    m_world->initialize();

    // Update layout for proper positioning
    updateLayout();
}

/**
 * Handle window resizing - update all positions based on current window size
 * Follows the same pattern as MenuState::updateLayout()
 */
void LevelState::updateLayout() {
    sf::Vector2u windowSize = m_window.getSize();
    const float windowWidth = static_cast<float>(windowSize.x);
    const float windowHeight = static_cast<float>(windowSize.y);

    // Reset the view to match new window size
    sf::FloatRect visibleArea(0, 0, windowWidth, windowHeight);
    m_window.setView(sf::View(visibleArea));

    // Update camera with new window size
    m_camera.updateWindowSize();

    // If you add any UI elements to LevelState later (score display, lives, etc.),
    // position them here using the same percentage-based approach as MenuState

    // Example for future score display:
    // if (m_scoreText) {
    //     sf::FloatRect scoreBounds = m_scoreText.getLocalBounds();
    //     m_scoreText.setOrigin(scoreBounds.width / 2, scoreBounds.height / 2);
    //     m_scoreText.setPosition(windowWidth / 2, windowHeight * 0.05f);
    // }

    // Example for future lives display:
    // if (m_livesText) {
    //     sf::FloatRect livesBounds = m_livesText.getLocalBounds();
    //     m_livesText.setOrigin(livesBounds.width / 2, livesBounds.height / 2);
    //     m_livesText.setPosition(windowWidth * 0.1f, windowHeight * 0.05f);
    // }

    // Notify world about window resize if needed
    if (m_world) {
        // You might want to add a handleResize method to World class
        // m_world->handleWindowResize(windowSize);
    }

    // Notify factory about layout changes
    if (m_factory) {
        // You might want to add an updateLayout method to SFMLFactory
        // m_factory->updateLayout(windowSize);
    }
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
    // Handle window resize - exactly like MenuState
    if (event.type == sf::Event::Resized) {
        // Update the view to match new window size
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        m_window.setView(sf::View(visibleArea));

        // Recalculate all positions
        updateLayout();
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


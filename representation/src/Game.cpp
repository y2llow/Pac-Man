#include "Game.h"

namespace pacman::representation {

Game::Game()
    : m_window(std::make_unique<sf::RenderWindow>(
          sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
          "Pac-Man"
      ))
    , m_camera(Camera(*m_window)), m_stateManager(*m_window) {

    m_window->setFramerateLimit(FPS_LIMIT);
}

/**
 * Main game loop. Starts with Pushing the MenuState, Loops thru (processes events, updates (logic), renders update (representation)).
 */
void Game::run() {
    // Push MenuState so Menu can be shown on screen
    m_stateManager.pushState(std::make_unique<MenuState>(m_stateManager, *m_window, m_camera));

    while (m_window->isOpen()) {
        processEvents();
        update(1.0f / 60.0f); // Fixed delta time for simplicity
        render();
    }
}

/**
 * First Checks if window is closed then handles event in StateManager puhsing or popping states from stack
 */
void Game::processEvents() {
    sf::Event event{};
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window->close();
        }
        m_stateManager.handleEvent(event);
    }
}

void Game::update(float deltaTime) {
    m_stateManager.update(deltaTime);
}


void Game::render() {
    m_window->clear();
    m_stateManager.render();
    m_window->display();
}

} // namespace pacman::representation
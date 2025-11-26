#include "Game.h"
#include "rendering/SpriteSheet.h"
#include "core/Stopwatch.h"

namespace pacman::representation {

Game::Game()
    : m_window(std::make_unique<sf::RenderWindow>(
          sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
          "Pac-Man"
      ))
    , m_camera(Camera(*m_window)), m_stateManager(*m_window) {

    m_window->setFramerateLimit(FPS_LIMIT);

    auto& spriteSheet = SpriteSheet::getInstance();
    if (!spriteSheet.loadSpriteSheet("assets/textures/pacman_sprites.png")) {
        throw std::runtime_error("Failed to load sprite sheet!");
    }
}

/**
 * Main game loop. Starts with Pushing the MenuState, Loops thru (processes events, updates (logic), renders update (representation)).
 */
void Game::run() {
    // Get the singleton instance and start it
    Stopwatch& stopwatch = Stopwatch::getInstance();
    stopwatch.start();

    // Push MenuState so Menu can be shown on screen
    m_stateManager.pushState(std::make_unique<MenuState>(m_stateManager, *m_window, m_camera));

    while (m_window->isOpen()) {
        float deltaTime = stopwatch.tick();

        processEvents();
        update(deltaTime); // Now using actual delta time
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
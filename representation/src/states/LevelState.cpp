#include "states/LevelState.h"
#include "StateManger.h"
#include "states/GameOverState.h"
#include "states/PausedState.h"
#include "states/VictoryState.h"

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

    // Initialize world without window size
    m_world = std::make_unique<World>(*m_factory);
    m_world->initialize();

    if (m_font.loadFromFile("assets/fonts/arial.ttf")) {
        // Initialize text objects with the font
        m_scoreText.setFont(m_font);
        m_livesText.setFont(m_font);

        // Set colors and styles (these don't change with resize)
        m_scoreText.setFillColor(sf::Color::Yellow);
        m_scoreText.setStyle(sf::Text::Bold);

        m_livesText.setFillColor(sf::Color::Yellow);
        m_livesText.setStyle(sf::Text::Bold);
    }

    updateLayout();
}

/**
 * Handle window resizing - update all positions based on current window size
 * Follows the same pattern as MenuState::updateLayout()
 */
void LevelState::updateLayout() {
    Vector2f windowSize;
    windowSize.x = m_window.getSize().x;
    windowSize.y = m_window.getSize().y;

    // Update camera with new window size
    m_camera.updateWindowSize(Vector2f(windowSize));

    // Reset the view
    sf::FloatRect visibleArea(0, 0, windowSize.x, windowSize.y);
    m_window.setView(sf::View(visibleArea));

    if (m_factory) {
        m_factory->handleResize(windowSize);
    }

    // Scale text based on window size
    // Character size scales with window height (e.g., 7% of window height)
    unsigned int scaledCharSize = static_cast<unsigned int>(windowSize.y * 0.07f);
    m_scoreText.setCharacterSize(scaledCharSize);
    m_livesText.setCharacterSize(scaledCharSize);

    // Update text content to get proper bounds
    int currentScore = m_world ? m_world->Getscore()->getCurrentScore() : 0;
    int currentLives = m_world ? m_world->getPacman()->getLives() : 3;

    m_scoreText.setString("SCORE: " + std::to_string(currentScore));
    m_livesText.setString("Lives: " + std::to_string(currentLives));

    // Position score text at top-left with padding
    float padding = windowSize.x * 0.005f; // 2% padding
    m_scoreText.setPosition(padding, padding);

    // Position lives text at top-right with padding
    sf::FloatRect livesBounds = m_livesText.getLocalBounds();
    m_livesText.setPosition(windowSize.x - livesBounds.width - padding, 0);
}

void LevelState::update(float deltaTime) {
    handleInput();

    if (m_world) {
        m_world->update(deltaTime);
    }

    if (m_factory) {
        for (const auto& view : m_factory->getViews()) {
            if (view) {
                view->update(deltaTime);
            }
        }
        m_factory->cleanupCollectedViews();
    }

    // Update text content (the actual values change during gameplay)
    if (m_world) {
        int scoreValue = m_world->Getscore()->getCurrentScore();
        int livesValue = m_world->getPacman()->getLives();

        m_scoreText.setString("SCORE: " + std::to_string(scoreValue));
        m_livesText.setString("Lives: " + std::to_string(livesValue));

        // Reposition lives text since width might change
        sf::FloatRect livesBounds = m_livesText.getLocalBounds();
        float padding = m_window.getSize().x * 0.005f;
        m_livesText.setPosition(m_window.getSize().x - livesBounds.width - padding, padding);
    }
}

void LevelState::render() {
    m_window.clear(sf::Color(5, 5, 20));

    for (const auto& view : m_factory->getViews()) {
        if (view) {
            view->draw(m_window);
        }
    }

    // Draw text elements
    m_window.draw(m_scoreText);
    m_window.draw(m_livesText);
}

void LevelState::handleInput() {
    if (!m_world) return;

    auto pacman = m_world->getPacman();
    if (!pacman) return;

    // Check keyboard input and update Pacman's buffer
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        pacman->bufferDirection(0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        pacman->bufferDirection(1);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        pacman->bufferDirection(2);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        pacman->bufferDirection(3);
    }
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
        return;
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
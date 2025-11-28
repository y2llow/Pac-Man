#include "states/LevelState.h"
#include "StateManger.h"
#include "states/GameOverState.h"
#include "states/MenuState.h"
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

        // Game Over text
        m_gameOverText.setFont(m_font);
        m_gameOverText.setString("GAME OVER");
        m_gameOverText.setFillColor(sf::Color::Red);
        m_gameOverText.setStyle(sf::Text::Bold);

        // Setup game over overlay
        m_gameOverOverlay.setFillColor(sf::Color(0, 0, 0, 180));

        // NIEUW: Level Complete text
        m_levelCompleteText.setFont(m_font);
        m_levelCompleteText.setFillColor(sf::Color::Yellow);
        m_levelCompleteText.setStyle(sf::Text::Bold);

        // Setup level complete overlay
        m_levelCompleteOverlay.setFillColor(sf::Color(255, 255, 0, 120)); // Geel, semi-transparant
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
    unsigned int scaledCharSize = static_cast<unsigned int>(windowSize.y * 0.07f);
    m_scoreText.setCharacterSize(scaledCharSize);
    m_livesText.setCharacterSize(scaledCharSize);

    // Update text content to get proper bounds
    int currentScore = m_world ? m_world->Getscore()->getCurrentScore() : 0;
    int currentLives = m_world ? m_world->getPacman()->getLives() : 3;

    m_scoreText.setString("SCORE: " + std::to_string(currentScore));
    m_livesText.setString("Lives: " + std::to_string(currentLives));

    // Position score text at top-left with padding
    float padding = windowSize.x * 0.005f;
    m_scoreText.setPosition(padding, padding);

    // Position lives text at top-right with padding
    sf::FloatRect livesBounds = m_livesText.getLocalBounds();
    m_livesText.setPosition(windowSize.x - livesBounds.width - padding, 0);

    // Game Over text - SCALABLE based on window size
    // Start with height-based size
    unsigned int gameOverCharSize = static_cast<unsigned int>(windowSize.y * 0.12f);
    m_gameOverText.setCharacterSize(gameOverCharSize);

    // Check if text is too wide for the window
    sf::FloatRect gameOverBounds = m_gameOverText.getLocalBounds();
    float maxWidthGameOver = windowSize.x * 0.9f; // Use 90% of window width

    // If text is too wide, scale it down to fit
    if (gameOverBounds.width > maxWidthGameOver) {
        float scaleFactor = maxWidthGameOver / gameOverBounds.width;
        gameOverCharSize = static_cast<unsigned int>(gameOverCharSize * scaleFactor);
        m_gameOverText.setCharacterSize(gameOverCharSize);

        // Recalculate bounds after resize
        gameOverBounds = m_gameOverText.getLocalBounds();
    }

    // Center the text
    m_gameOverText.setOrigin(gameOverBounds.width / 2, gameOverBounds.height / 2);
    m_gameOverText.setPosition(windowSize.x / 2, windowSize.y / 2);

    m_gameOverOverlay.setSize(sf::Vector2f(windowSize.x, windowSize.y));

    // Level Complete text - SCALABLE based on window size
    // Start with height-based size
    unsigned int levelCompleteCharSize = static_cast<unsigned int>(windowSize.y * 0.12f);
    m_levelCompleteText.setCharacterSize(levelCompleteCharSize);

    // Update the string to ensure bounds are correct
    if (m_isLevelComplete) {
        m_levelCompleteText.setString("LEVEL " + std::to_string(m_completedLevel) + " COMPLETE!");
    }

    // Check if text is too wide for the window
    sf::FloatRect levelCompleteBounds = m_levelCompleteText.getLocalBounds();
    float maxWidth = windowSize.x * 0.9f; // Use 90% of window width

    // If text is too wide, scale it down to fit
    if (levelCompleteBounds.width > maxWidth) {
        float scaleFactor = maxWidth / levelCompleteBounds.width;
        levelCompleteCharSize = static_cast<unsigned int>(levelCompleteCharSize * scaleFactor);
        m_levelCompleteText.setCharacterSize(levelCompleteCharSize);

        // Recalculate bounds after resize
        levelCompleteBounds = m_levelCompleteText.getLocalBounds();
    }

    // Center the text
    m_levelCompleteText.setOrigin(levelCompleteBounds.width / 2, levelCompleteBounds.height / 2);
    m_levelCompleteText.setPosition(windowSize.x / 2, windowSize.y / 2);

    m_levelCompleteOverlay.setSize(sf::Vector2f(windowSize.x, windowSize.y));
}

void LevelState::update(float deltaTime) {
    // Check for game over first
    if (m_world && m_world->getPacman()->getLives() <= 0 && !m_isGameOver) {
        // Trigger game over
        m_isGameOver = true;
        m_gameOverTimer = 0.0f;
        m_world->Getscore()->saveHighScores();
    }

    // Handle game over timer
    if (m_isGameOver) {
        m_gameOverTimer += deltaTime;

        // KEEP UPDATING PACMAN AND HIS VIEW DURING GAME OVER
        if (m_world && m_world->getPacman()) {
            m_world->getPacman()->update(deltaTime);

            // Update PacmanView - find it in factory views
            for (const auto& view : m_factory->getViews()) {
                if (view) {
                    view->update(deltaTime);
                }
            }
        }

        if (m_gameOverTimer >= GAME_OVER_DISPLAY_TIME) {
            // Time's up - go back to menu
            m_stateManager.switchToState(std::make_unique<MenuState>(m_stateManager, m_window, m_camera));
            return;
        }

        // Don't update anything else during game over
        return;
    }

    // NIEUW: Handle level complete timer
    if (m_isLevelComplete) {
        m_levelCompleteTimer += deltaTime;

        if (m_levelCompleteTimer >= LEVEL_COMPLETE_DISPLAY_TIME) {
            // Time's up - advance to next level
            m_isLevelComplete = false;
            m_levelCompleteTimer = 0.0f;

            if (m_world) {
                m_world->advanceToNextLevel();
                m_completedLevel = m_world->getCurrentLevel();
            }
        }

        // Don't update game logic during level complete screen
        return;
    }

    // Normal game updates (only when not game over or level complete)
    handleInput();

    if (m_world) {
        m_world->update(deltaTime);

        // Check if level was just completed
        if (m_world->areAllCoinsCollected() && !m_isLevelComplete) {
            m_isLevelComplete = true;
            m_levelCompleteTimer = 0.0f;
            m_completedLevel = m_world->getCurrentLevel();

            // Update text with current level
            m_levelCompleteText.setString("LEVEL " + std::to_string(m_completedLevel) + " COMPLETE!");

            // Force a complete layout update to recalculate everything
            updateLayout();
        }
    }

    if (m_factory) {
        for (const auto& view : m_factory->getViews()) {
            if (view) {
                view->update(deltaTime);
            }
        }
        m_factory->cleanupCollectedViews();
    }

    // Update text content
    if (m_world) {
        int scoreValue = m_world->Getscore()->getCurrentScore();
        int livesValue = m_world->getPacman()->getLives();

        m_scoreText.setString("SCORE: " + std::to_string(scoreValue));
        m_livesText.setString("Lives: " + std::to_string(livesValue));

        sf::FloatRect livesBounds = m_livesText.getLocalBounds();
        float padding = m_window.getSize().x * 0.005f;
        m_livesText.setPosition(m_window.getSize().x - livesBounds.width - padding, padding);
    }
}


void LevelState::render() {
    m_window.clear(sf::Color(5, 5, 20));

    // Draw game entities
    for (const auto& view : m_factory->getViews()) {
        if (view) {
            view->draw(m_window);
        }
    }

    // Draw UI text
    m_window.draw(m_scoreText);
    m_window.draw(m_livesText);

    // Draw Level Complete overlay if needed
    if (m_isLevelComplete) {
        m_window.draw(m_levelCompleteOverlay);
        m_window.draw(m_levelCompleteText);
    }

    // Draw Game Over overlay if needed
    if (m_isGameOver) {
        m_window.draw(m_gameOverOverlay);
        m_window.draw(m_gameOverText);
    }
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
            // Don't allow pause during level complete or game over
            if (!m_isLevelComplete && !m_isGameOver) {
                m_stateManager.pushState(std::make_unique<PausedState>(m_stateManager, m_window, m_camera));
            }
            break;
        default:
            break;
        }
    }
}
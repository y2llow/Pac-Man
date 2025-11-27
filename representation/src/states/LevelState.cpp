#include "states/LevelState.h"
#include "StateManger.h"
#include "states/GameOverState.h"
#include "states/PausedState.h"
#include "states/VictoryState.h"

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

    if (m_font.loadFromFile("assets/fonts/arial.ttf")) {
        // Use camera to get current window size
        const float windowWidth = windowSize.x; const float windowHeight = windowSize.y;

        // Create the overlay
        m_overlay.setSize(sf::Vector2f(windowWidth, windowHeight));
        m_overlay.setFillColor(sf::Color(0, 0, 0, 180));

        // Initialize text objects with the font
        m_scoreText.setFont(m_font);
        m_livesText.setFont(m_font);
        m_menuText.setFont(m_font);

        // int ScoreString = m_world->Getscore()->getCurrentScore();
        //
        // // Convert the integer to a string
        // std::string scoreText = "SCORE: " + std::to_string(ScoreString);
        //
        // // Set the string for the SFML text object
        // m_scoreText.setString(scoreText);
        m_scoreText.setCharacterSize(60);
        m_scoreText.setFillColor(sf::Color::Yellow);
        m_scoreText.setStyle(sf::Text::Bold);

        // int LivesString = m_world->getPacman()->getLives();
        //
        // std::string livesText = "Lives: " + std::to_string(LivesString);
        //
        // m_livesText.setString(livesText);
        // m_livesText.setPosition(windowWidth - 500,0);
        m_livesText.setCharacterSize(60);
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
    windowSize.x = m_window.getSize().x ; windowSize.y = m_window.getSize().y ;

    // Update camera with new window size
    m_camera.updateWindowSize(Vector2f(windowSize)); // Add this method to Camera if needed

    // Reset the view
    sf::FloatRect visibleArea(0, 0, windowSize.x, windowSize.y);
    m_window.setView(sf::View(visibleArea));

    if (m_factory) {
        m_factory->handleResize(windowSize); // Remove camera parameter
    }
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
}

void LevelState::render() {
    m_window.clear(sf::Color(5, 5, 20));

    for (const auto& view : m_factory->getViews()) {
        if (view) {
            view->draw(m_window);
        }
    }

    //dynamische score
    int ScoreString = m_world->Getscore()->getCurrentScore();
    std::string scoreText = "SCORE: " + std::to_string(ScoreString);
    m_scoreText.setString(scoreText);

    //dynamische lives
    int LivesString = m_world->getPacman()->getLives();
    std::string livesText = "Lives: " + std::to_string(LivesString);
    m_livesText.setString(livesText);
    m_livesText.setPosition(m_window.getSize().x - 220,0);

            m_window.draw(m_scoreText);
            m_window.draw(m_livesText);
}

void LevelState::handleInput() {
    if (!m_world) return;

    // Get Pacman from World (je moet hiervoor een method toevoegen aan World)
    auto pacman = m_world->getPacman(); // Je moet deze method implementeren

    if (!pacman) return;

    // Check keyboard input en update Pacman's buffer
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


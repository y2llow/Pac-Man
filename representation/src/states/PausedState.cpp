#include "states/PausedState.h"

#include "Game.h"
#include "StateManger.h"
#include "states/MenuState.h"

PausedState::PausedState(StateManager& stateManager, sf::RenderWindow& window, Camera& camera)
    : State(stateManager), m_window(window), m_camera(camera) {
}

void PausedState::initialize() {
    if (m_font.loadFromFile("assets/fonts/arial.ttf")) {
        const float windowWidth = pacman::representation::Game::WINDOW_WIDTH;
        const float windowHeight = pacman::representation::Game::WINDOW_HEIGHT;

        // Create the overlay first (darker for contrast)
        m_overlay.setSize(sf::Vector2f(windowWidth, windowHeight));
        m_overlay.setFillColor(sf::Color(0, 0, 0, 180)); // Darker overlay for better readability

        // Create the background panel
        m_backgroundPanel.setSize(sf::Vector2f(400, 150));
        m_backgroundPanel.setFillColor(sf::Color(30, 30, 60, 220)); // Same blue as MenuState
        m_backgroundPanel.setOutlineColor(sf::Color(255, 255, 0)); // Yellow border
        m_backgroundPanel.setOutlineThickness(3);
        m_backgroundPanel.setOrigin(200, 125); // Center the panel
        m_backgroundPanel.setPosition(windowWidth / 2, windowHeight / 2);

        // Create and position texts (PAUSED, Continue, Menu)
        auto createText = [&](sf::Text& text, const std::string& content, unsigned int charSize, const sf::Color& color, sf::Text::Style style,
                              float xOffset, float yOffset) {
            text.setFont(m_font);
            text.setString(content);
            text.setCharacterSize(charSize);
            text.setFillColor(color);
            text.setStyle(style);

            // Center the text based on window width/height and offsets
            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.width / 2, textBounds.height / 2);
            text.setPosition(windowWidth * xOffset, windowHeight * yOffset);
        };

        // PAUSED title text (same style as MenuState title)
        createText(m_pauseText, "PAUSED", 64, sf::Color(255, 255, 0), sf::Text::Bold, 0.5f, 0.25f);

        // Continue instructions
        createText(m_continueText, "PRESS ESC TO CONTINUE", 28, sf::Color::White, sf::Text::Bold, 0.5f, 0.4f);

        // Menu instructions
        createText(m_menuText, "PRESS M FOR MAIN MENU", 28, sf::Color::White, sf::Text::Bold, 0.5f, 0.45f);
    }
}


void PausedState::update(float deltaTime) {
    // Optional: Add blinking effect for instructions (like MenuState)
    static float blinkTimer = 0;
    blinkTimer += deltaTime;

    if (blinkTimer >= 0.8f) {
        // Toggle between white and gray for both instruction texts
        sf::Color newColor = (m_continueText.getFillColor() == sf::Color::White) ?
                            sf::Color(150, 150, 150) : sf::Color::White;

        m_continueText.setFillColor(newColor);
        m_menuText.setFillColor(newColor);
        blinkTimer = 0;
    }
}

void PausedState::render() {
    // Note: LevelState is still in the stack below this one, so it gets rendered first
    m_window.clear(sf::Color(10, 10, 40));

    // // Draw semi-transparent overlay (dims the game behind)
    // m_window.draw(m_overlay);

    // Draw background panel (optional - makes text more readable)
    m_window.draw(m_backgroundPanel);

    // Draw all text elements
    m_window.draw(m_pauseText);
    m_window.draw(m_continueText);
    m_window.draw(m_menuText);
}

void StateManager::switchToState(std::unique_ptr<State> state) {
    // Clear all existing states
    clearStates();

    // Push the new state
    pushState(std::move(state));
}

/**
 * stateManager -> LevelState if esc is pressed
 * stateManager -> MenuState if M is pressed
 * @param event current SFML event
 */
void PausedState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Escape:
            m_stateManager.popState();
            break;
        case sf::Keyboard::M:
            m_stateManager.switchToState(std::make_unique<MenuState>(m_stateManager, m_window, m_camera));
            break;
        }
    }
}

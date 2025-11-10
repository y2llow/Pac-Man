#include "states/PausedState.h"
#include "StateManger.h"
#include "states/MenuState.h"

PausedState::PausedState(StateManager& stateManager, sf::RenderWindow& window)
    : State(stateManager), m_window(window) {
}

void PausedState::initialize() {
    if (m_font.loadFromFile("assets/fonts/arial.ttf")) {
        const float windowWidth = 800;
        const float windowHeight = 600;

        // Paused title (same style as MenuState title)
        m_pauseText.setFont(m_font);
        m_pauseText.setString("PAUSED");
        m_pauseText.setCharacterSize(64);
        m_pauseText.setFillColor(sf::Color(255, 255, 0)); // Bright yellow like Pac-Man
        m_pauseText.setStyle(sf::Text::Bold);

        // Center the pause text
        sf::FloatRect pauseBounds = m_pauseText.getLocalBounds();
        m_pauseText.setOrigin(pauseBounds.width / 2, pauseBounds.height / 2);
        m_pauseText.setPosition(windowWidth / 2, 215);

        // Continue instructions
        m_continueText.setFont(m_font);
        m_continueText.setString("PRESS ESC TO CONTINUE");
        m_continueText.setCharacterSize(28);
        m_continueText.setFillColor(sf::Color::White);
        m_continueText.setStyle(sf::Text::Bold);

        // Center the continue text
        sf::FloatRect continueBounds = m_continueText.getLocalBounds();
        m_continueText.setOrigin(continueBounds.width / 2, continueBounds.height / 2);
        m_continueText.setPosition(windowWidth / 2, 300);

        // Menu instructions
        m_menuText.setFont(m_font);
        m_menuText.setString("PRESS M FOR MAIN MENU");
        m_menuText.setCharacterSize(28);
        m_menuText.setFillColor(sf::Color::White);
        m_menuText.setStyle(sf::Text::Bold);

        // Center the menu text
        sf::FloatRect menuBounds = m_menuText.getLocalBounds();
        m_menuText.setOrigin(menuBounds.width / 2, menuBounds.height / 2);
        m_menuText.setPosition(windowWidth / 2, 361);

        // Create a semi-transparent overlay (darker than MenuState for better contrast)
        m_overlay.setSize(sf::Vector2f(windowWidth, windowHeight));
        m_overlay.setFillColor(sf::Color(0, 0, 0, 180)); // Darker overlay for better readability

        // Optional: Add a centered background panel like MenuState
        m_backgroundPanel.setSize(sf::Vector2f(400, 250));
        m_backgroundPanel.setFillColor(sf::Color(30, 30, 60, 220)); // Same blue as MenuState
        m_backgroundPanel.setOutlineColor(sf::Color(255, 255, 0)); // Yellow border
        m_backgroundPanel.setOutlineThickness(3);
        m_backgroundPanel.setOrigin(200, 125); // Center the panel
        m_backgroundPanel.setPosition(windowWidth / 2, windowHeight / 2);
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
            m_stateManager.switchToState(std::make_unique<MenuState>(m_stateManager, m_window));
            break;
        }
    }
}

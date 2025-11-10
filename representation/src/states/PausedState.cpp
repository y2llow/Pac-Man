#include "states/PausedState.h"

#include "StateManger.h"
#include "states/MenuState.h"

PausedState::PausedState(StateManager& stateManager, sf::RenderWindow& window)
    : State(stateManager), m_window(window) {
}

void PausedState::initialize() {
    if (m_font.loadFromFile("assets/fonts/arial.ttf")) {
        m_pauseText.setFont(m_font);
        m_pauseText.setString("PAUSED");
        m_pauseText.setCharacterSize(48);
        m_pauseText.setPosition(300, 200);

        m_continueText.setFont(m_font);
        m_continueText.setString("Press ESC to Continue\nPress M for Menu");
        m_continueText.setCharacterSize(24);
        m_continueText.setPosition(250, 300);
    }
}


void StateManager::switchToState(std::unique_ptr<State> state) {
    // Clear all existing states
    clearStates();

    // Push the new state
    pushState(std::move(state));
}




void PausedState::update(float deltaTime) {
    // Paused state doesn't update game logic
}

void PausedState::render() {
    // Note: LevelState is still in the stack below this one, so it gets rendered first
    // We just overlay the pause screen
    sf::RectangleShape overlay(sf::Vector2f(800, 600));
    overlay.setFillColor(sf::Color(0, 0, 0, 128));  // Semi-transparent black

    m_window.draw(overlay);
    m_window.draw(m_pauseText);
    m_window.draw(m_continueText);
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

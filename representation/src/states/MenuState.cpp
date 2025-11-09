#include "states/MenuState.h"

#include "StateManger.h"
#include "states/LevelState.h"
#include <memory>


class LevelState;MenuState::MenuState(StateManager& stateManager, sf::RenderWindow& window)
    : State(stateManager), m_window(window) {
}

void MenuState::initialize() {
    // Simple menu setup
    if (m_font.loadFromFile("assets/fonts/arial.ttf")) {
        m_titleText.setFont(m_font);
        m_titleText.setString("PAC-MAN");
        m_titleText.setCharacterSize(48);
        m_titleText.setPosition(250, 200);

        m_playText.setFont(m_font);
        m_playText.setString("Press SPACE to Play");
        m_playText.setCharacterSize(24);
        m_playText.setPosition(280, 300);
    }
}

void MenuState::update(float deltaTime) {
    // Game.getScore();
    // setscore into Highscore table
    // Highscore updates
}

void MenuState::render() {
    m_window.clear(sf::Color::Black);
    m_window.draw(m_titleText);
    m_window.draw(m_playText);
}

/**
 * MenuState -> LevelState when spacebar is pressed
 * @param event = current SFML event
 */
void MenuState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            m_stateManager.pushState(std::make_unique<LevelState>(m_stateManager, m_window));
        }
    }
}

#include "StateManger.h"
#include "states/State.h"

StateManager::StateManager(sf::RenderWindow& window)
    : m_window(window) {
}

void StateManager::pushState(std::unique_ptr<State> state) {
    if (state) {
        m_states.push_back(std::move(state));
        m_states.back()->initialize();
    }
}

void StateManager::popState() {
    if (!m_states.empty()) {
        m_states.pop_back();
    }
}
void StateManager::switchToState(std::unique_ptr<State> state) {
    // Clear all existing states
    clearStates();

    // Push the new state
    pushState(std::move(state));
}

void StateManager::clearStates() {
    m_states.clear();
}

void StateManager::update(float deltaTime) {
    if (!m_states.empty()) {
        m_states.back()->update(deltaTime);
    }
}

void StateManager::render() {
    if (!m_states.empty()) {
        m_states.back()->render();
    }
}

/**
 * Forwards SFML events to the current active state (top of stack)
 * handleEvent depends on *Param event* checked in State class
 * @param event = SFML event to handle
 */
void StateManager::handleEvent(const sf::Event& event) {
    if (!m_states.empty()) {
        m_states.back()->handleEvent(event);
    }
}
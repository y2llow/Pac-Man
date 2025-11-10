#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

class State;

class StateManager {
public:
    explicit StateManager(sf::RenderWindow& window);

    // State stack management
    void pushState(std::unique_ptr<State> state);
    void popState();
    void switchToState(std::unique_ptr<State>state);
    void clearStates();

    // Check if stack is empty (for quitting)
    bool isEmpty() const { return m_states.empty(); }

    // Main loop methods
    void update(float deltaTime);
    void render();
    void handleEvent(const sf::Event& event);

private:
    std::vector<std::unique_ptr<State>> m_states;
    sf::RenderWindow& m_window;
};

#endif

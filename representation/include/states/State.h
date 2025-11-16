#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

class StateManager;  // Forward declaration

class State {
public:
    explicit State(StateManager& stateManager) : m_stateManager(stateManager) {}
    virtual ~State() = default;

    // Pure virtual methods that all states must implement
    virtual void initialize() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void onEnter() {}  // Called when state becomes active (optional override)


protected:
    StateManager& m_stateManager;
};

#endif
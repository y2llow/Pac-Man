#ifndef LEVEL_STATE_H
#define LEVEL_STATE_H

#include "State.h"
#include <SFML/Graphics.hpp>

class LevelState : public State {
public:
    LevelState(StateManager& stateManager, sf::RenderWindow& window);

    void initialize() override;
    void update(float deltaTime) override;
    void render() override;
    void handleEvent(const sf::Event& event) override;

private:
    sf::RenderWindow& m_window;

    // Simple test - replace with your World later
    sf::RectangleShape m_testShape;
};

#endif
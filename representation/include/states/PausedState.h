#ifndef PAUSED_STATE_H
#define PAUSED_STATE_H

#include "State.h"
#include <SFML/Graphics.hpp>

class PausedState : public State {
public:
    PausedState(StateManager& stateManager, sf::RenderWindow& window);

    void initialize() override;
    void update(float deltaTime) override;
    void render() override;
    void handleEvent(const sf::Event& event) override;

private:
    sf::RenderWindow& m_window;
    sf::Font m_font;
    sf::Text m_pauseText;
    sf::Text m_continueText;
};

#endif

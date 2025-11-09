#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "State.h"
#include <SFML/Graphics.hpp>

class MenuState : public State {
public:
    MenuState(StateManager& stateManager, sf::RenderWindow& window);
    
    void initialize() override;
    void update(float deltaTime) override;
    void render() override;
    void handleEvent(const sf::Event& event) override;

private:
    sf::RenderWindow& m_window;
    sf::Font m_font;
    sf::Text m_titleText;
    sf::Text m_playText;
};

#endif
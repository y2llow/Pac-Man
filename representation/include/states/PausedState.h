#ifndef PAUSED_STATE_H
#define PAUSED_STATE_H

#include "Camera.h"
#include "State.h"

#include <memory>
#include <SFML/Graphics.hpp>

class PausedState : public State {
public:
    PausedState(StateManager& stateManager, sf::RenderWindow& window, Camera& camera);

    void initialize() override;
    void update(float deltaTime) override;
    void render() override;
    void handleEvent(const sf::Event& event) override;
    void updateLayout();


private:
    sf::RenderWindow& m_window;
    Camera& m_camera;
    sf::Font m_font;
    sf::Text m_pauseText;
    sf::Text m_continueText;
    sf::Text m_menuText;
    sf::RectangleShape m_overlay;
    sf::RectangleShape m_backgroundPanel;
};

#endif

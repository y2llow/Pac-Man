#pragma once
#include "Camera.h"
#include "State.h"
#include <SFML/Graphics.hpp>

class VictoryState : public State {
public:
    VictoryState(StateManager& stateManager, sf::RenderWindow& window, Camera& camera);
    void initialize() override;
    void update(float deltaTime) override;
    void render() override;
    void handleEvent(const sf::Event& event) override;

private:
    void updateLayout();

    sf::RenderWindow& m_window;
    Camera& m_camera;

    sf::Font m_font;
    sf::RectangleShape m_overlay;
    sf::RectangleShape m_backgroundPanel;
    sf::Text m_victoryText;
    sf::Text m_continueText;
    sf::Text m_menuText;

    float m_blinkTimer = 0.0f;
};
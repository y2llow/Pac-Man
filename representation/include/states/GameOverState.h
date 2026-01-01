#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include "Camera.h"
#include "State.h"
#include <SFML/Graphics.hpp>

namespace pacman::representation::states {

class GameOverState : public State {
public:
    GameOverState(StateManager& stateManager, sf::RenderWindow& window, Camera& camera);

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
    sf::Text m_gameOverText;
    sf::Text m_continueText;
    sf::Text m_menuText;

    float m_blinkTimer = 0.0f;
};

} // namespace pacman::representation::states

#endif
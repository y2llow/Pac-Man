#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "Camera.h"
#include "State.h"
#include <SFML/Graphics.hpp>

class MenuState : public State {
public:
    MenuState(StateManager& stateManager, sf::RenderWindow& window, Camera& camera);
    
    void initialize() override;
    void update(float deltaTime) override;
    void render() override;
    void handleEvent(const sf::Event& event) override;

private:
    sf::RenderWindow& m_window;
    Camera& m_camera;
    sf::Font m_font;
    sf::Text m_titleText;
    sf::Text m_playButtonText;
    sf::RectangleShape m_playButton;
    sf::Text m_highScoreTitle;
    std::vector<sf::Text> m_highScoreTexts;
    std::vector<int> m_highScores;
    sf::RectangleShape m_highScoreBackground;

    bool m_isButtonHovered;

    void loadHighScores();
    void updateHighScoreDisplay();
    void updateLayout();  // Updates positions when window resizes
    bool isMouseOverButton(const sf::Vector2i& mousePos) const;
    void startGame();

};

#endif
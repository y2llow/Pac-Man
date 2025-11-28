#ifndef LEVEL_STATE_H
#define LEVEL_STATE_H

#include "Camera.h"
#include "State.h"
#include "factory/ConcreteFactory.h"
#include "world/World.h"

#include <SFML/Graphics.hpp>

class LevelState : public State {
public:
    LevelState(StateManager& stateManager, sf::RenderWindow& window, Camera& camera);

    void initialize() override;
    void update(float deltaTime) override;
    void render() override;

    void handleEvent(const sf::Event& event) override;
    void handleInput();
    void updateLayout();

private:
    sf::RenderWindow& m_window;
    std::unique_ptr<SFMLFactory> m_factory;
    std::unique_ptr<World> m_world;
    Camera& m_camera;
    std::vector<std::unique_ptr<Observer>> m_entityViews;
    MapModel m_mapModel;

    // UI text elements
    sf::Font m_font;
    sf::Text m_scoreText;
    sf::Text m_livesText;

    // Game Over overlay
    bool m_isGameOver = false;
    float m_gameOverTimer = 0.0f;
    static constexpr float GAME_OVER_DISPLAY_TIME = 3.0f;
    sf::Text m_gameOverText;
    sf::RectangleShape m_gameOverOverlay;

    // Level Complete overlay
    bool m_isLevelComplete = false;
    float m_levelCompleteTimer = 0.0f;
    static constexpr float LEVEL_COMPLETE_DISPLAY_TIME = 2.0f;
    sf::Text m_levelCompleteText;
    sf::RectangleShape m_levelCompleteOverlay;
    int m_completedLevel = 1;
};

#endif
#ifndef LEVEL_STATE_H
#define LEVEL_STATE_H

#include "Camera.h"
#include "State.h"
#include "factory/ConcreteFactory.h"
#include "world/World.h"

#include <SFML/Window/Keyboard.hpp>
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
    std::unique_ptr<SFMLFactory> m_factory;  // Factory for creating entities
    std::unique_ptr<World> m_world;          // World to manage entities
    Camera& m_camera;                         // For coordinate conversion
    std::vector<std::unique_ptr<Observer>> m_entityViews;
    MapModel m_mapModel;

    // text elements
    sf::Font m_font;
    sf::Text m_scoreText;
    sf::Text m_livesText;
    sf::Text m_menuText;
    sf::RectangleShape m_overlay;
    sf::RectangleShape m_backgroundPanel;

};

#endif
#ifndef LEVEL_STATE_H
#define LEVEL_STATE_H

#include "Camera.h"
#include "State.h"
#include "factory/ConcreteFactory.h"
#include "world/World.h"

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
    std::unique_ptr<SFMLFactory> m_factory;  // Factory for creating entities
    std::unique_ptr<World> m_world;          // World to manage entities
    Camera m_camera;                         // For coordinate conversion

    void loadMapFromFile(const std::string& filename);
    void createEntityFromGrid(char cellType, int x, int y);
};

#endif
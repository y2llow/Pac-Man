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
    void updateLayout();


private:
    sf::RenderWindow& m_window;
    std::unique_ptr<SFMLFactory> m_factory;  // Factory for creating entities
    std::unique_ptr<World> m_world;          // World to manage entities
    Camera& m_camera;                         // For coordinate conversion
    std::vector<std::unique_ptr<Observer>> m_entityViews;
    MapModel m_mapModel;


    bool loadFromFile(const std::string& filename);
    void createWallsFromGrid(std::vector<std::string> m_grid, sf::Vector2u m_gridSize);
    void addEntityWithView(std::unique_ptr<EntityModel> entity, std::unique_ptr<Observer> view) ;
};

#endif
#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "StateManger.h"
#include "states/MenuState.h"

namespace pacman::representation {

class Game {
public:
    Game();
    ~Game() = default;

    void run();

    // Configuration - exactly like your image
    static constexpr unsigned int WINDOW_WIDTH = 800;
    static constexpr unsigned int WINDOW_HEIGHT = 800;
    static constexpr unsigned int FPS_LIMIT = 60;

private:
    std::unique_ptr<sf::RenderWindow> m_window;
    StateManager m_stateManager;

    void processEvents();
    void update(float deltaTime);
    void render();


};

} // namespace pacman::representation
#include "Game.h"
#include <iostream>

Game::Game(): m_window(std::make_unique<Window>("Pac-Man", sf::Vector2u(800,600))),
              m_world(sf::Vector2u(800,600)),
              m_initialized(false) {
}

Game::~Game(){}

void Game::Update(){
    m_window->Update(); // Update window events.

    if (!m_initialized) {
        // Initialize logic first
        if (m_world.initialize()) {
            // Then initialize representation with logic data
            m_mapView.initialize(m_world.getMapModel(), m_window->GetRenderWindow());
            m_initialized = true;
        } else {
            std::cerr << "Failed to initialize world!" << std::endl;
        }
    }

    // Update game logic (we'll add delta time later)
    // m_world.update(deltaTime);
}

void Game::Render(){
    m_window->BeginDraw(); // Clear.

    if (m_initialized) {
        m_mapView.draw(m_window->GetRenderWindow());
        // Later we'll add other entities here
    }

    m_window->EndDraw(); // Display.
}


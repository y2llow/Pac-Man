#include "Game.h"


Game::Game(): m_window("Map", sf::Vector2u(800,600)){
}

Game::~Game(){};

void Game::Update(){
    m_window.Update(); // Update window events.
}

void Game::Render(){
    m_window.BeginDraw(); // Clear.
    // m_window.Draw();
    m_window.EndDraw(); // Display.
}

[[nodiscard]] Window *Game::GetWindow() {
    return &m_window;
}

// void Game::RestartClock(){
//     m_elapsed += m_clock.restart();
// }

#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "world/World.h"
#include "views/MapView.h" // This is OK here - Game is in representation layer

class Game {
public:
    Game();
    ~Game();
    void Update();
    void Render();
    Window* GetWindow();

private:
    Window m_window;
    World m_world;          // Logic
    MapView m_mapView;      // Representation
    bool m_initialized;
};

#endif
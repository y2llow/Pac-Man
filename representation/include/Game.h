#ifndef GAME_H
#define GAME_H
#include "Window.h"
#include "world/World.h"


class Game{
public:
    Game();
    ~Game();
    // void HandleInput();
    void Update();
    void Render();
    Window* GetWindow();

    // void RestartClock();



private:
    Window m_window;
    World m_world;
    // float m_elapsed;


   };
#endif //GAME_H

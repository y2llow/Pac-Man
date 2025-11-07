#ifndef GAME_H
#define GAME_H
#include "Window.h"
#include <SFML/Graphics.hpp>


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
    // float m_elapsed;


   };
#endif //GAME_H

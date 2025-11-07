#ifndef GAME_H
#define GAME_H
#include "Window.h"
#include <SFML/Graphics.hpp>


class Game{
public:
    Game();
    ~Game();
    void HandleInput();
    void Update();
    void Render();
    Window* GetWindow();



private:
    void MoveMushroom();
    Window m_window;

   };
#endif //GAME_H

#include "Game.h"

int main(int argc, char* argv[])
{
    using Game::GameWindow;

    // Initialization
    GameWindow pong;
    pong.Init();
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        pong.Update();
        
        // Draw
        pong.Draw();
    }
    // De-Initialization
    CloseWindow();      
    return 0;
}
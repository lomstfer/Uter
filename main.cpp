#include <raylib.h>
#include <iostream>
#include "SpriteSheet.hpp"
#include "Player.hpp"

#define Log(x) std::cout << x << std::endl;

int main(void)
{
    const int winW = 800;
    const int winH = 450;

    InitWindow(winW, winH, "Uter");
    SetTargetFPS(60);

    Player player(Vector2{10, 10}, "assets/oldman_walk.png", 4);
    
    SetExitKey(KEY_NULL);
    bool running = true;
    while (running) 
    {
        if (WindowShouldClose()) {
            running = false;
        }

        player.update();

        // Draw ------
        BeginDrawing();
        ClearBackground(Color{0, 0, 0, 255});

        player.spriteSheet.animateDraw(6, GetFrameTime(), player.position);

        EndDrawing();
    }

    
    CloseWindow();
    

    return 0;
}
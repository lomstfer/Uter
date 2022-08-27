#include <raylib.h>
#include <iostream>
#include "SpriteSheet.hpp"
#include "Player.hpp"
#include "Textures.hpp"

#define Log(x) std::cout << x << std::endl;

int main()
{
    const int winW = 800;
    const int winH = 700;

    InitWindow(winW, winH, "Uter");
    loadTextures();
    SetTargetFPS(60);
    Image icon = LoadImageFromTexture(peoSS);
    SetWindowIcon(icon);

    Player player = Player(Vector2{10, 10}, peoSS, 4, 5);
    
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

        player.spriteSheet.animateDraw(10, GetFrameTime(), player.position);

        EndDrawing();
    }

    
    CloseWindow();
    

    return 0;
}
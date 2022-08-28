#include <raylib.h>
#include <iostream>
#include "SpriteSheet.hpp"
#include "Player.hpp"
#include "Textures.hpp"

#define Log(x) std::cout << x << std::endl;

int main()
{
    const int winW = 1000;
    const int winH = 750;

    InitWindow(winW, winH, "Uter");
    textures->loadTextures();
    SetTargetFPS(144);
    Image icon = LoadImageFromTexture(textures->peoStill);
    SetWindowIcon(icon);

    Player player = Player(Vector2{10, 10}, textures->peoSS, 4, 5);
    
    //SetExitKey(KEY_NULL);
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

        player.draw();

        EndDrawing();
    }

    
    CloseWindow();
    

    return 0;
}
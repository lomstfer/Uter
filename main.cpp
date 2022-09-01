#include <raylib.h>
#include <iostream>
#include "SpriteSheet.hpp"
#include "Player.hpp"
#include "Globals.hpp"

#define Log(x) std::cout << x << std::endl;

int main()
{
    InitWindow(winW, winH, "Uter");
    loadTextures();
    SetTargetFPS(60);
    Image icon = LoadImageFromTexture(peoStill);
    SetWindowIcon(icon);

    Player player = Player(Vector2{10, 10}, peoSS, 4, 5);
    
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

//#include <iostream>
//#define Log(x) std::cout << x << std::endl;

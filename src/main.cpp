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
    SetTargetFPS(144);
    Image icon = LoadImageFromTexture(peoStill);
    SetWindowIcon(icon);

    Player player = Player(Vector2{winW / 2.0f, 10}, peoSS, 4, 5);
    
    //SetExitKey(KEY_NULL);
    bool running = true;
    while (running) 
    {
        if (WindowShouldClose()) {
            running = false;
        }

        

        // Draw ------
        BeginDrawing();
        ClearBackground(Color{0, 0, 0, 255});
        player.update();

        EndDrawing();
    }

    
    CloseWindow();
    

    return 0;
}

//#include <iostream>
//#define Log(x) std::cout << x << std::endl;

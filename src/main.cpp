#include <raylib.h>
#include <iostream>
#include "SpriteSheet.hpp"
#include "Player.hpp"
#include "Globals.hpp"
#include <stdio.h>

#define Log(x) std::cout << x << std::endl;

int main()
{
    InitWindow(winW, winH, "Uter");
    loadTextures();
    SetTargetFPS(144);
    Image icon = LoadImageFromTexture(peoStill);
    SetWindowIcon(icon);

    Player player = Player(Vector2{winW / 2.0f, 10}, peoSS, 4, 5);

    Image img = GenImageColor(winW, winH, BLANK);

    int scale = 1;

    for (int i = 0; i <= winW / scale; i++) {
        for (int j = 0; j <= winH / scale; j++) {
            ImageDrawPixel(&img, i, j, Color{(unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255), 80});
        }
    }

    Texture2D tt = LoadTextureFromImage(img);
    
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

        DrawTextureEx(tt, Vector2{0, 0}, 0, scale, Color{255, 255, 255, 255});

        player.update();
        

        EndDrawing();
    }

    
    CloseWindow();
    

    return 0;
}

//#include <iostream>
//#define Log(x) std::cout << x << std::endl;

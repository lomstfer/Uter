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

    Player player = Player(Vector2{winW/2.0f, 10}, peoSS, 4, 5);

    Image backgroundImg = GenImageColor(winW, winH, BLANK);

    for (int i = 0; i <= winW; i++) {
        for (int j = 0; j <= winH; j++) {
            ImageDrawPixel(&backgroundImg, i, j, Color{(unsigned char)(GetRandomValue(200, 255)), (unsigned char)(GetRandomValue(200, 255)), (unsigned char)(GetRandomValue(200, 255)), 30});
        }
    }

    Texture2D backgroundTexture = LoadTextureFromImage(backgroundImg);

    int bs = 4;
    Rectangle brec = Rectangle{winW/2 - brec.width*bs/2, winH/2 - brec.height*bs/2, 32, 32};
    Image testImg = GenImageColor(brec.width, brec.height, BLANK);

    /*for (int i = 0; i <= brec.width; i++) {
        for (int j = 0; j <= brec.height; j++) {
            ImageDrawPixel(&testImg, i, j, Color{0, (unsigned char)(GetRandomValue(150, 151)), 0, 255});
        }
    }*/

    // head
    for (int x = 0; x <= brec.width; x++) {
        for (int y = 0; y <= brec.height; y++) {
            if (sqrt(pow(x - brec.width/2, 2) + pow(y - brec.height/2, 2)) <= (brec.width + brec.height)/4) {
                ImageDrawPixel(&testImg, x, y, Color{255, 255, 255, (unsigned char)(abs(x - brec.width/2))});
            }
                
        }
    }

    // eyes
    for (int i = 0; i <= 20; i++) {
        ImageDrawPixel(&testImg, 10 + GetRandomValue(-1.5, 1.5), 10+ GetRandomValue(-1.5, 1.5), Color{0, 0, 0, 255});

        ImageDrawPixel(&testImg, brec.width - 10 + GetRandomValue(-1.5, 1.5), 10 + GetRandomValue(-1.5, 1.5), Color{0, 0, 0, 255});
    }

    // mouth
    int mouthEle = 0;
    for (int i = 0; i <= brec.width - 10; i++) {
        if (i % 2 == 0)
            mouthEle += GetRandomValue(-1, 1);
        ImageDrawPixel(&testImg, 5 + i, 20 + mouthEle, Color{0, 0, 0, 255});
    }

    Texture2D testTexture = LoadTextureFromImage(testImg);

    
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

        DrawTextureEx(backgroundTexture, Vector2{0, 0}, 0, 1, Color{255, 255, 255, 255});
        DrawTextureEx(testTexture, Vector2{brec.x, brec.y}, 0, bs, Color{255, 255, 255, 255});

        player.update();
        

        EndDrawing();
    }

    
    CloseWindow();
    

    return 0;
}

//#include <iostream>
//#define Log(x) std::cout << x << std::endl;

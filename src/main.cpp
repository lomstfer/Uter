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

    float logTime = 0;

    Player player = Player(Vector2{winW/2.0f, 10}, peoSS, 4, 5);

    Image backgroundImg = GenImageColor(winW, winH, BLANK);

    for (int i = 0; i <= winW; i++) {
        for (int j = 0; j <= winH; j++) {
            ImageDrawPixel(&backgroundImg, i, j, Color{(unsigned char)(GetRandomValue(0, 50)), (unsigned char)(GetRandomValue(0, 50)), (unsigned char)(GetRandomValue(0, 50)), 255});
        }
    }

    Texture2D backgroundTexture = LoadTextureFromImage(backgroundImg);

    int bs = 1;
    Rectangle brec = Rectangle{winW/2 - brec.width*bs/2, 100, 128, 128};
    int brecx;
    int brecy;
    Image testImg = GenImageColor(brec.width, brec.height, BLANK);

    /*for (int i = 0; i <= brec.width; i++) {
        for (int j = 0; j <= brec.height; j++) {
            ImageDrawPixel(&testImg, i, j, Color{0, (unsigned char)(GetRandomValue(150, 151)), 0, 255});
        }
    }*/

    Vector2 light = Vector2{400, 100};

    for (int x = 0; x <= brec.width; x++) {
        for (int y = 0; y <= brec.height; y++) {
            if (sqrt(pow(x + 0.5 - brec.width/2, 2) + pow(y + 0.5 - brec.height/2, 2)) <= brec.width/brec.height * brec.width/2) {
                float d = sqrt(pow(brec.x + x - light.x, 2) + pow(brec.y + y - light.y, 2)) * 18;
                float c = 1 - d;
                ImageDrawPixel(&testImg, x, y, ConvertToRGBA(c, c, c, 1));
            }
        }
    }

    /* // eyes
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
    } */

    Texture2D testTexture = LoadTextureFromImage(testImg);

    float dt;
    //SetExitKey(KEY_NULL);
    bool running = true;
    while (running) 
    {
        dt = GetFrameTime();
        if (WindowShouldClose()) {
            running = false;
        }

        logTime += GetFrameTime();
        if (logTime >= 0.1) {
            logTime = 0;
            Log(std::to_string(GetFrameTime() * 1000) + " ms");
        }

        brec.y += sin(GetTime()) * 60 * dt;
        brecx = brec.x + brec.width/2;
        brecy = brec.y + brec.height/2;

        for (int x = 0; x <= brec.width; x++) {
            for (int y = 0; y <= brec.height; y++) {
                if (sqrt(pow(x + 0.5 - brec.width/2, 2) + pow(y + 0.5 - brec.height/2, 2)) <= brec.width/brec.height * brec.width/2) {
                    float d = sqrt(pow(brec.x + x - light.x, 2) + pow(brec.y + y - light.y, 2)) * 7;
                    float c = 1 - d/2500;
                    ImageDrawPixel(&testImg, x, y, ConvertToRGBA(c, c, c, 1));
                }
            }
        }
        UnloadTexture(testTexture);
        testTexture = LoadTextureFromImage(testImg);

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

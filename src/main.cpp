#include <raylib.h>
#include <iostream>
#include "Globals.hpp"
#include "SpriteSheet.hpp"
#include "Player.hpp"
#include "Boss.hpp"

int main()
{
    InitWindow(SCREENW, SCREENH, "Uter");
    loadTextures();
    SetTargetFPS(60);
    Image icon = LoadImageFromTexture(PEOSTILL);
    SetWindowIcon(icon);
    SetWindowState(FLAG_FULLSCREEN_MODE);
    float logTime = 0;

    int difficulty = 1; // load difficulty

    float inBetweenTime = 0;
    float inBetweenMax = 5;
    
    RenderTexture2D renderTarget = LoadRenderTexture(WINW, WINH);

    Player player = Player(Vector2{WINW/2.0f - PEOSTILL.width/2, WINH}, PEOSS, 4, SPRITESCALE);

    Boss boss = Boss(difficulty);

    Image backgroundImg = GenImageColor(WINW/SPRITESCALE, WINH/SPRITESCALE, BLANK);

    for (int i = 0; i <= WINW; i++) {
        for (int j = 0; j <= WINH; j++) {
            ImageDrawPixel(&backgroundImg, i, j, Color{(unsigned char)(GetRandomValue(0, 50)), (unsigned char)(GetRandomValue(0, 50)), (unsigned char)(GetRandomValue(0, 50)), 255});
        }
    }

    Texture2D backgroundTexture = LoadTextureFromImage(backgroundImg);

    enum gameStates {
        MENU,
        PLAYING
    };
    int gameState = MENU;

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
        if (logTime >= 1) {
            logTime = 0;
            Log(std::to_string(GetFrameTime() * 1000) + " ms");
        }

        if (IsKeyPressed(KEY_H)) {
            changeWindowSize(rand() % 1920, rand() % 1080);
        }
        
        switch (gameState) 
        {
            case MENU:
                if (IsKeyPressed(KEY_ENTER)) {
                    gameState = PLAYING;
                    difficulty = 1;
                }
                BeginDrawing();
                    ClearBackground(Color{100, 0, 0, 255});
                EndDrawing();
            break;

            case PLAYING:
                if (boss.killedPlayer) {
                    player.dead = true;
                    gameState = MENU;
                    player.~Player();
                    Player player = Player(Vector2{WINW/2.0f - PEOSTILL.width/2, WINH}, PEOSS, 4, SPRITESCALE);
                    boss = Boss(difficulty);
                }
                if (boss.killed) {
                    inBetweenTime += dt;
                    boss.die();
                    boss.update(player);
                    if (inBetweenTime >= inBetweenMax) {
                        inBetweenTime = 0;
                        boss = Boss(difficulty + 1);
                    }
                }
                boss.update(player);
                    
                // Draw ------
                BeginDrawing();

                BeginTextureMode(renderTarget);
                    ClearBackground(Color{0, 0, 0, 255});
                
                    DrawTextureEx(backgroundTexture, Vector2{0, 0}, 0, SPRITESCALE, Color{255, 255, 255, 255});

                    player.update();
                    boss.draw();
                EndTextureMode();
                DrawTexturePro(renderTarget.texture, Rectangle{0,0,float(renderTarget.texture.width),float(-renderTarget.texture.height)}, Rectangle{0,0,float(SCREENW),float(SCREENH)}, Vector2{0,0}, 0, WHITE);
                
                EndDrawing();
            break;
        }
        

        
    }

    CloseWindow();
    
    return 0;
}

//#include <iostream>
//#define Log(x) std::cout << x << std::endl;

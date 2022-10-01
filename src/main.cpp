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
    SetTargetFPS(144);
    Image icon = LoadImageFromTexture(PEO_STILL);
    SetWindowIcon(icon);
    //SetWindowState(FLAG_FULLSCREEN_MODE);

    Font font = LoadFont("assets/Silkscreen-Regular.ttf");

    float logTime = 0;

    int difficulty = 1; // load difficulty

    float inBetweenTime = 0;
    float inBetweenMax = 5;
    
    RenderTexture2D renderTarget = LoadRenderTexture(WINW, WINH);
    RenderTexture2D renderTargetPaused = LoadRenderTexture(WINW, WINH);

    Player player = Player(Vector2{WINW/2.0f - PEO_STILL.width/2, WINH}, PEO_SS, 4, SPRITESCALE);

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
        PLAYING,
        PAUSED
    };
    int gameState = MENU;

    float dt;
    SetExitKey(KEY_NULL);
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
                if (IsKeyPressed(KEY_ESCAPE)) {
                    gameState = PAUSED;
                }
                if (boss.killedPlayer) {
                    player.dead = true;
                    gameState = MENU;
                    player.~Player();
                    Player player = Player(Vector2{WINW/2.0f - PEO_STILL.width/2, WINH}, PEO_SS, 4, SPRITESCALE);
                    boss = Boss(difficulty);
                }
                if (boss.killed) {
                    inBetweenTime += dt;
                    boss.die();
                    boss.update(player);
                    if (inBetweenTime >= inBetweenMax) {
                        inBetweenTime = 0;
                        difficulty += 1;
                        boss = Boss(difficulty);
                    }
                }
                boss.update(player);
                    
                // Draw ------
                BeginDrawing();

                BeginTextureMode(renderTarget);
                    ClearBackground(Color{0, 0, 0, 255});
                
                    DrawTextureEx(backgroundTexture, {0, 0}, 0, SPRITESCALE, {255,255,255,255});

                    player.update();
                    player.updateAttacks(boss.position, !boss.killed);
                    if (player.attackHit) {
                        player.attackHit = false;
                        boss.looseHealth(player.damage);
                    }

                    DrawTextureEx(GROUND, {0, WINH-GROUND.height*SPRITESCALE}, 0, SPRITESCALE, {255,255,255,255});

                    boss.draw();

                    DrawTextEx(font, std::to_string(difficulty).c_str(), {10, WINH - 60}, 50, 0, BLACK);

                EndTextureMode();
                DrawTexturePro(renderTarget.texture, Rectangle{0,0,float(renderTarget.texture.width),float(-renderTarget.texture.height)}, Rectangle{0,0,float(SCREENW),float(SCREENH)}, Vector2{0,0}, 0, WHITE);
                
                EndDrawing();
            break;

            case PAUSED:
                if (IsKeyPressed(KEY_ESCAPE)) {
                    gameState = PLAYING;
                }
                if (IsKeyPressed(KEY_O)) {
                    running = false;
                }
                BeginDrawing();
                BeginTextureMode(renderTargetPaused);
                    ClearBackground({0,0,0,0});
                    DrawTextEx(font, "paused", {WINW/2 - 500,WINH/2 - 300}, 100, 0, WHITE);
                EndTextureMode();
                DrawTexturePro(renderTarget.texture, Rectangle{0,0,float(renderTarget.texture.width),float(-renderTarget.texture.height)}, Rectangle{0,0,float(SCREENW),float(SCREENH)}, Vector2{0,0}, 0, {100,100,100,255});
                DrawTexturePro(renderTargetPaused.texture, Rectangle{0,0,float(renderTargetPaused.texture.width),float(-renderTargetPaused.texture.height)}, Rectangle{0,0,float(SCREENW),float(SCREENH)}, Vector2{0,0}, 0, {255,255,255,255});
                EndDrawing();
            break;
        }
    
    }

    CloseWindow();
    UnloadFont(font);
    return 0;
}

//#include <iostream>
//#define Log(x) std::cout << x << std::endl;

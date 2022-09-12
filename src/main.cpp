#include <raylib.h>
#include <iostream>
#include "Globals.hpp"
#include "SpriteSheet.hpp"
#include "Player.hpp"
#include "Boss.hpp"


#define Log(x) std::cout << x << std::endl;

int main()
{
    InitWindow(SCREENW, SCREENH, "Uter");
    loadTextures();
    SetTargetFPS(144);
    Image icon = LoadImageFromTexture(PEOSTILL);
    SetWindowIcon(icon);
    SetWindowState(FLAG_FULLSCREEN_MODE);

    RenderTexture2D renderTarget = LoadRenderTexture(WINW, WINH);
    RenderTexture2D rE = LoadRenderTexture(32, 32);

    float logTime = 0;

    Player player = Player(Vector2{WINW/2.0f - PEOSTILL.width/2, 10}, PEOSS, 4, SPRITESCALE);

    Boss boss = Boss(Vector2{WINW/2.f, 100});

    Image backgroundImg = GenImageColor(WINW/SPRITESCALE, WINH/SPRITESCALE, BLANK);

    for (int i = 0; i <= WINW; i++) {
        for (int j = 0; j <= WINH; j++) {
            ImageDrawPixel(&backgroundImg, i, j, Color{(unsigned char)(GetRandomValue(0, 20)), (unsigned char)(GetRandomValue(0, 20)), (unsigned char)(GetRandomValue(0, 20)), 255});
        }
    }

    Texture2D backgroundTexture = LoadTextureFromImage(backgroundImg);

    int bs = 4;
    Rectangle brec = Rectangle{WINW/2 - brec.width*bs/2, 100, 64, 64};
    Image testImg = GenImageColor(brec.width, brec.height, BLANK);

    Vector2 light = Vector2{0, 0};

    Texture2D testTexture = LoadTextureFromImage(testImg);

    float dt;
    //SetExitKey(KEY_NULL);

    float rot = 0;


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

        light = GetMousePosition();

        BeginTextureMode(rE);
        DrawLine(16,0,32,32,WHITE);
        DrawLine(1,31,31,31,WHITE);
        DrawLine(0,32,16,0,WHITE);
        EndTextureMode();
        rot += dt * 100;
        // Draw ------
        BeginDrawing();
        BeginTextureMode(renderTarget);
            ClearBackground(Color{0, 0, 0, 255});
        
            DrawTextureEx(backgroundTexture, Vector2{0, 0}, 0, SPRITESCALE, Color{255, 255, 255, 255});
            DrawTextureEx(testTexture, Vector2{brec.x, brec.y}, 0, bs, Color{255, 255, 255, 255});

            player.update();
            //boss.update(player.position);
            
            DrawTexturePro(rE.texture, {0,0,rE.texture.width,-rE.texture.height}, {WINW/2,100,rE.texture.width*10,rE.texture.height*10}, Vector2{rE.texture.width/2*10,rE.texture.height/2*10}, rot, Color{255,255,255,255});
            
        EndTextureMode();
        DrawTexturePro(renderTarget.texture, Rectangle{0,0,float(renderTarget.texture.width),float(-renderTarget.texture.height)}, Rectangle{0,0,float(SCREENW),float(SCREENH)}, Vector2{0,0}, 0, WHITE);
        
        EndDrawing();
    }

    
    CloseWindow();
    

    return 0;
}

//#include <iostream>
//#define Log(x) std::cout << x << std::endl;

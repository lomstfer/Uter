#include <raylib.h>
#include <iostream>
#include <math.h>

#define Log(x) std::cout << x << std::endl;

Vector2 rotp(float cx, float cy, float angle, Vector2 p)
{
  float s = sin(angle);
  float c = cos(angle);

  // translate point back to origin:
  p.x -= cx;
  p.y -= cy;

  // rotate point
  float xnew = p.x * c - p.y * s;
  float ynew = p.x * s + p.y * c;

  // translate point back:
  p.x = xnew + cx;
  p.y = ynew + cy;
  return p;
}

int main()
{
    InitWindow(1280, 720, "Uter");
    SetTargetFPS(144);

    RenderTexture2D testTarget = LoadRenderTexture(64, 65);

    float dt;

    float rot = 0.01;

    Vector2 p1s = {testTarget.texture.width/2,0};
    Vector2 p1e = {testTarget.texture.width,testTarget.texture.height};

    Vector2 p2s = {0,testTarget.texture.height};
    Vector2 p2e = {testTarget.texture.width,testTarget.texture.height};

    Vector2 p3s = {0,testTarget.texture.width};
    Vector2 p3e = {testTarget.texture.width/2,0};

    //SetExitKey(KEY_NULL);
    bool running = true;
    while (running) 
    {
        dt = GetFrameTime();
        if (WindowShouldClose()) {
            running = false;
        }

        p1s = rotp(32, 32, rot, p1s);
        p1e = rotp(32, 32, rot, p1e);

        p2s = rotp(32, 32, rot, p2s);
        p2e = rotp(32, 32, rot, p2e);

        p3s = rotp(32, 32, rot, p3s);
        p3e = rotp(32, 32, rot, p3e);

        BeginTextureMode(testTarget);
        ClearBackground(Color{0, 0, 0, 255});
        DrawLine(p1s.x,p1s.y,p1e.x,p1e.y,WHITE);
        DrawLine(p2s.x,p2s.y,p2e.x,p2e.y,WHITE);
        DrawLine(p3s.x,p3s.y,p3e.x,p3e.y,WHITE);
        EndTextureMode();


        // Draw ------
        BeginDrawing();
            ClearBackground(Color{0, 0, 0, 255});
                    
            DrawTexturePro(testTarget.texture, {0,0,testTarget.texture.width,-testTarget.texture.height}, {1280/2,720/2,testTarget.texture.width*5,testTarget.texture.height*5}, Vector2{testTarget.texture.width/2*5,testTarget.texture.height/2*5}, 0, Color{255,255,255,255});
            
        
        EndDrawing();
    }

    
    CloseWindow();
    

    return 0;
}

//#include <iostream>
//#define Log(x) std::cout << x << std::endl;

#include "Globals.hpp"

int WINW = 1920;
int WINH = 1080;

int SCREENW = 1920;
int SCREENH = 1080;

float SPRITESCALE = 8;//

int ftint(float x) {
    if (x > 0)
        return int(x + 0.5);
    else 
        return int(x - 0.5);
}

void changeWindowSize(int newWidth, int newHeight) {
    SetWindowPosition(GetWindowPosition().x - (newWidth - SCREENW) / 2, GetWindowPosition().y - (newHeight - SCREENH) / 2);
    SetWindowSize(newWidth, newHeight);
    SCREENW = newWidth;
    SCREENH = newHeight;
}

Color ConvertToRGBA(float r, float g, float b, float a) {
    r = r <= 0 ? 0 : r >= 1 ? 1 : r;
    g = g <= 0 ? 0 : g >= 1 ? 1 : g;
    b = b <= 0 ? 0 : b >= 1 ? 1 : b;
    a = a <= 0 ? 0 : a >= 1 ? 1 : a;
    return Color{(unsigned char)(int(r*255 + 0.5)), (unsigned char)(int(g*255 + 0.5)), (unsigned char)(int(b*255 + 0.5)), (unsigned char)(int(a*255 + 0.5))};
}

Texture2D PEOSS;
Texture2D PEOSTILL;
Texture2D BOSS1;
Texture2D BOSSBIG;

void loadTextures() {
    PEOSS = LoadTexture("assets/peo_run.png");
    PEOSTILL = LoadTexture("assets/peo.png");
    BOSS1 = LoadTexture("assets/boss/rectangle.png");
    BOSSBIG = LoadTexture("assets/boss/boss_long.png");
}
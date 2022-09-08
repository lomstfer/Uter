#include "Globals.hpp"

int winW = 1280;
int winH = 720;

int ftint(float x) {
    if (x > 0)
        return int(x + 0.5);
    else 
        return int(x - 0.5);
}

void changeWindowSize(int newWidth, int newHeight) {
    SetWindowPosition(GetWindowPosition().x - (newWidth - winW) / 2, GetWindowPosition().y - (newHeight - winH) / 2);
    SetWindowSize(newWidth, newHeight);
    winW = newWidth;
    winH = newHeight;
}

Color ConvertToRGBA(float r, float g, float b, float a) {
    r = r <= 0 ? 0 : r >= 1 ? 1 : r;
    g = g <= 0 ? 0 : g >= 1 ? 1 : g;
    b = b <= 0 ? 0 : b >= 1 ? 1 : b;
    a = a <= 0 ? 0 : a >= 1 ? 1 : a;
    return Color{(unsigned char)(ftint(r*255)), (unsigned char)(ftint(g*255)), (unsigned char)(ftint(b*255)), (unsigned char)(ftint(a*255))};
}

Texture2D peoSS;
Texture2D peoStill;

void loadTextures() {
    peoSS = LoadTexture("assets/peo_run.png");
    peoStill = LoadTexture("assets/peo.png");
}
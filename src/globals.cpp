#include "Globals.hpp"

int WINW = 1920;
int WINH = 1080;

int SCREENW = 1920;
int SCREENH = 1080;

float SPRITESCALE = 6;

int ftint(float x) {
    if (x > 0)
        return int(x + 0.5);
    else 
        return int(x - 0.5);
}

void minmax(float& num, float smallest, float biggest) {
    if (num < smallest) {
        num = smallest;
    }
    if (num > biggest) {
        num = biggest;
    }
}

int randInt(int lower, int higher)
{
    return rand()%(higher - lower + 1) + lower;
}

void changeWindowSize(int newWidth, int newHeight) {
    SetWindowPosition(GetWindowPosition().x - (newWidth - SCREENW)/2, GetWindowPosition().y - (newHeight - SCREENH)/2);
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

Texture2D PEO_SS;
Texture2D PEO_STILL;

Texture2D CREE_SS;
Texture2D CREE_STILL;

Texture2D SMALL_CIRCLE;
Texture2D GROUND;
int GROUND_HEIGHT = 42;

void loadTextures() {
    PEO_SS = LoadTexture("assets/peo_run.png");
    PEO_STILL = LoadTexture("assets/peo.png");
    CREE_SS = LoadTexture("assets/cree_walk.png");

    SMALL_CIRCLE = LoadTexture("assets/boss/small_circle.png");
    GROUND = LoadTexture("assets/ground.png");
}
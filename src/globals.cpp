#include "Globals.hpp"

int winW = 1280;
int winH = 720;

void changeWindowSize(int newWidth, int newHeight) {
    SetWindowPosition(GetWindowPosition().x - (newWidth - winW) / 2, GetWindowPosition().y - (newHeight - winH) / 2);
    SetWindowSize(newWidth, newHeight);
    winW = newWidth;
    winH = newHeight;
}

Texture2D peoSS;
Texture2D peoStill;

void loadTextures() {
    peoSS = LoadTexture("assets/peo_run.png");
    peoStill = LoadTexture("assets/peo.png");
}
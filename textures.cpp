#include "Textures.hpp"

Texture2D peoSS;
Texture2D peoStill;

void loadTextures() {
    peoSS = LoadTexture("assets/peo_run.png");
    peoStill = LoadTexture("assets/peo.png");
}
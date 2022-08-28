#ifndef TEXTURES_HPP
#define TEXTURES_HPP

// ss = sprite sheet

struct Textures {
    Texture2D peoSS;
    Texture2D peoStill;

    void loadTextures() {
        peoSS = LoadTexture("assets/peo_run.png");
        peoStill = LoadTexture("assets/peo.png");
    }
};

Textures* textures;

#endif
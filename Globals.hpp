#ifndef TEXTURES_HPP
#define TEXTURES_HPP
#include <raylib.h>

extern int winW;
extern int winH;

void changeWindowSize(int newWidth, int newHeight);

// ss = sprite sheet
extern Texture2D peoSS;
extern Texture2D peoStill;

void loadTextures();

#endif
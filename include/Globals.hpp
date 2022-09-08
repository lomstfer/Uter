#ifndef TEXTURES_HPP
#define TEXTURES_HPP
#include <raylib.h>
#include <iostream>

#define Log(x) std::cout << x << std::endl;

extern int winW;
extern int winH;

void changeWindowSize(int newWidth, int newHeight);

Color ConvertToRGBA(float r, float g, float b, float a);

// ss = sprite sheet
extern Texture2D peoSS;
extern Texture2D peoStill;

void loadTextures();

#endif
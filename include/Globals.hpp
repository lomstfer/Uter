#ifndef TEXTURES_HPP
#define TEXTURES_HPP
#include <raylib.h>
#include <iostream>

#define Log(x) std::cout << x << std::endl;

extern int WINW;
extern int WINH;
extern int SCREENW;
extern int SCREENH;

extern float SPRITESCALE;

void changeWindowSize(int newWidth, int newHeight);

int ftint(float x);

Color ConvertToRGBA(float r, float g, float b, float a);

// ss = sprite sheet
extern Texture2D PEOSS;
extern Texture2D PEOSTILL;
extern Texture2D BOSS1;
extern Texture2D BOSSBIG;

void loadTextures();

#endif
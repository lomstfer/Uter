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
void minmax(float& num, float smallest, float biggest);
int randInt(int lower, int higher);

Color ConvertToRGBA(float r, float g, float b, float a);

// ss = sprite sheet
extern Texture2D PEO_SS;
extern Texture2D PEO_STILL;

extern Texture2D CREE_SS;
extern Texture2D CREE_STILL;

extern Texture2D SMALL_CIRCLE;
extern Texture2D GROUND;
extern int GROUND_HEIGHT;

void loadTextures();

#endif
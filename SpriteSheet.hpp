#ifndef SPRITE_SHEET_HPP
#define SPRITE_SHEET_HPP
#include <raylib.h>

// Sprite sheet with only one row that is

class SpriteSheet {
public:
    SpriteSheet(Texture2D texture, const int numberOfFrames, int scale);
    void animateDraw(float fps, float deltaTime, Vector2 drawPosition);

private:
    Texture2D texture;
    const int numberOfFrames;
    int scale;
    int currentFrame;
    int frameWidth;
    float timer;
};
#endif
#ifndef SPRITE_SHEET_HPP
#define SPRITE_SHEET_HPP

#include <raylib.h>

// Sprite sheet with only one row

class SpriteSheet {
public:
    SpriteSheet(const char* filePath, const int numberOfFrames);
    void animateDraw(float fps, float deltaTime, Vector2 drawPosition);

private:
    const char* filePath;
    const int numberOfFrames;
    Texture2D texture;
    int currentFrame;
    int frameWidth;
    float timer;
};
#endif
#ifndef SPRITE_SHEET_HPP
#define SPRITE_SHEET_HPP
#include <raylib.h>

// Sprite sheet with only one row that is

class SpriteSheet {
public:
    SpriteSheet(Texture2D texture, const int numberOfFrames, float scale);
    void animate(float fps, float deltaTime);
    void draw(Vector2 drawPosition);

    Texture2D texture;
    const int numberOfFrames;
    float scale;
    int currentFrame;
    int fWidth;;
    int fHeight;
    float timer;
    Rectangle srcRect;
    Rectangle dstRect;
    int facing;
};
#endif
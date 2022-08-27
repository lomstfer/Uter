#include "SpriteSheet.hpp"
#include <iostream>
#include <raylib.h>

SpriteSheet::SpriteSheet(Texture2D texture, const int numberOfFrames, int scale)
: texture(texture), numberOfFrames(numberOfFrames), scale(scale) {
    frameWidth = texture.width / numberOfFrames;
    currentFrame = 0;
}

void SpriteSheet::animateDraw(float fps, float deltaTime, Vector2 drawPosition) {
    timer += deltaTime;
    if (timer > 1.0f / fps) {
        timer = 0.0f;
        currentFrame += 1;
    }
    currentFrame = currentFrame % numberOfFrames;
    Rectangle srcRect = {float(frameWidth * currentFrame), 0.0f, (float)frameWidth, (float)texture.height};
    Rectangle dstRect = {drawPosition.x, drawPosition.y, (float)frameWidth * scale, (float)texture.height * scale};
    DrawTexturePro(texture, srcRect, dstRect, Vector2{0, 0}, 0, Color{255, 255, 255, 255});
}
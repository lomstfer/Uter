#include "SpriteSheet.hpp"
#include <iostream>

SpriteSheet::SpriteSheet(Texture2D texture, const int numberOfFrames, float scale)
: texture(texture), numberOfFrames(numberOfFrames), scale(scale) {
    fWidth = texture.width / numberOfFrames;
    fHeight = texture.height;
    currentFrame = 0;
    facing = 1;
    srcRect = {float(fWidth * currentFrame), 0.0f, (float)fWidth * facing, (float)texture.height};
    dstRect = {0, 0, (float)fWidth * scale, (float)texture.height * scale};
}

void SpriteSheet::animate(float fps, float deltaTime) {
    timer += deltaTime;
    if (timer > 1.0f / fps) {
        timer = 0.0f;
        currentFrame += 1;
    }
    currentFrame = currentFrame % numberOfFrames;
    srcRect = {float(fWidth * currentFrame), 0.0f, (float)fWidth * facing, (float)texture.height};
}

void SpriteSheet::draw(Vector2 drawPosition) {
    dstRect = {drawPosition.x, drawPosition.y, (float)fWidth * scale, (float)texture.height * scale};
    DrawTexturePro(texture, srcRect, dstRect, Vector2{fWidth/2 * scale, fHeight/2 * scale}, 0, Color{255, 255, 255, 255});
}

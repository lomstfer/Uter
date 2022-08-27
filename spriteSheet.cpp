#include "SpriteSheet.hpp"
#include <iostream>

SpriteSheet::SpriteSheet(const char* filePath, const int numberOfFrames) 
: filePath(filePath), numberOfFrames(numberOfFrames) {
    texture = LoadTexture(filePath);
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
    Rectangle rect = {float(frameWidth * currentFrame), 0.0f, (float)frameWidth, (float)texture.height};
    DrawTextureRec(texture, rect, drawPosition, Color{255, 255, 255, 255});
}
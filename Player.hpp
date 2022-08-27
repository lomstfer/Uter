#include "SpriteSheet.hpp"

class Player {
public:
    Player(Vector2 position, const char* filePath, const int numberOfFrames);
    void update();
    Vector2 position;
    SpriteSheet spriteSheet;
};
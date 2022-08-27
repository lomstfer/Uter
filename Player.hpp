#include "SpriteSheet.hpp"

class Player {
public:
    Player(Vector2 position, Texture2D texture, const int numberOfFrames, int scale);
    void update();
    Vector2 position;
    SpriteSheet spriteSheet;
};
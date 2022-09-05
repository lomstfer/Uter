#include "Globals.hpp"
#include <math.h>
#include <iostream>
#include "SpriteSheet.hpp"

class Boss {
public:
    Boss(Vector2 position, Texture2D texture, const int numberOfFrames, int scale);
    void update();

private:
    void attack();

    SpriteSheet sS;
    Vector2 position;
    Rectangle collisionRect;
    Vector2 velocity;

    int movementSystem;
};

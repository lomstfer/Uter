#include "SpriteSheet.hpp"
#include <math.h>
#include <iostream>
#include "Textures.hpp"

class Player {
public:
    Player(Vector2 position, Texture2D texture, const int numberOfFrames, int scale);
    void update();
    void draw();
    
    
    Vector2 position;
    Vector2 collisionPosition;
    SpriteSheet spriteSheet;

    Vector2 velocity;
    float runSpeed;
    float jumpForce;
    float gravity = 10000;
    float damp;
    
};
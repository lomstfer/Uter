#include "SpriteSheet.hpp"
#include <math.h>
#include <iostream>
#include "Globals.hpp"

class Player {
public:
    Player(Vector2 position, Texture2D texture, const int numberOfFrames, int scale);
    void update();
    void draw();

    void dashMaking();
    
    Vector2 position;
    Vector2 collisionPosition;
    SpriteSheet spriteSheet;

    Vector2 velocity;
    float runSpeed;
    float jumpForce;
    float gravity;
    float damp;
    int jumps;

    bool dashing;
    bool justPressedLeft;
    float pressAgainTime;
    float pressAgainMaxTime;
    float dashForce;
    float dashCooldown;
    
};
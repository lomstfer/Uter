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
    SpriteSheet sS;
    Rectangle collisionRect;

    Vector2 velocity;
    float runSpeed;
    float jumpForce;
    float gravity;
    float damp;
    float airDamp;
    float jumps;
    float maxJumps;
    bool grounded;

    // dash
    bool dashing;
    bool justPressedLeft;
    bool justPressedRight;
    float pressAgainTimeLeft;
    float pressAgainTimeRight;
    float pressAgainTimeCD;
    float dashForce;
    float dashTime;
    float dashTimeCD;
    float dashCooldownTime;
    float dashCooldownCD;
    bool just_dashed;
};
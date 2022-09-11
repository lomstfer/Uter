#include "Globals.hpp"
#include <math.h>
#include <iostream>
#include "SpriteSheet.hpp"

class Player {
public:
    Player(Vector2 position, Texture2D texture, const int numberOfFrames, float scale);
    void update();
    
    Vector2 position;
private:
    void dashMaking();
    
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
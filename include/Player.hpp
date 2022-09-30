#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Globals.hpp"
#include <math.h>
#include <iostream>
#include <vector>
#include "SpriteSheet.hpp"

class Player {
public:
    Player(Vector2 position, Texture2D texture, const int numberOfFrames, float scale);
    void update(Vector2 boss_position);
    
    bool dead = false;
    
    Vector2 position;
    Rectangle collisionRect;
private:
    void dashMaking();
    
    SpriteSheet sS;
    
    Vector2 velocity;

    float runSpeed;
    float jumpForce;
    float gravity;
    float damp;
    float airDamp;
    float jumps;
    float maxJumps;
    bool grounded;

    // Attack
    class Attack {
    public:
        Attack(Vector2 position, Vector2 velocity);
        Vector2 position;
        Vector2 velocity;
    };
    std::vector<Attack> attacks;
    float attackTime = 0;
    float attackNow = 2;

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
#endif
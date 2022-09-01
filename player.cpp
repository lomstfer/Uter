#include "Player.hpp"

#define Log(x) std::cout << x << std::endl;

Player::Player(Vector2 position, Texture2D texture, const int numberOfFrames, int scale)
: position(position), collisionPosition(position), spriteSheet(texture, numberOfFrames, scale) {
    velocity = Vector2{0, 0};
    runSpeed = 400;
    jumpForce = 2000;
    gravity = 10000;
    damp = 0.000001;
    jumps = 1;

    dashing = false;
    justPressedLeft = false;
    pressAgainTime = 0;
    pressAgainMaxTime = 0.5;
    dashForce = 3000;
    dashCooldown = 2;
}

void Player::update() {
    float dt = GetFrameTime();

    velocity.y += gravity * dt;
    velocity.x *= pow(damp, dt);

    if (abs(velocity.x) < 5) {
        velocity.x = 0;
        spriteSheet.texture = peoStill;
    } else {
        spriteSheet.texture = peoSS;
    }

    if (abs(velocity.x) > 0) {
        if (velocity.x > 0) 
            spriteSheet.facing = 1;
        else if (velocity.x < 0)
            spriteSheet.facing = -1;
        spriteSheet.animate(10, dt);
    }
    
    if (!dashing) {
        if (IsKeyDown(KEY_A)) {
            velocity.x = -runSpeed;
        }

        if (IsKeyDown(KEY_D)) {
            velocity.x = runSpeed;
        }
    }
    
    if (IsKeyDown(KEY_SPACE) && jumps > 0) {
        velocity.y = -jumpForce;
        jumps -= 1;
    }

    dashMaking();

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    if (position.y > winH - spriteSheet.texture.height * spriteSheet.scale) {
        position.y = winH - spriteSheet.texture.height * spriteSheet.scale;
        jumps = 1;
    }
    if (position.x > winW - spriteSheet.frameWidth * spriteSheet.scale) {
        position.x = winW - spriteSheet.frameWidth * spriteSheet.scale;
    }
    if (position.x < 0) {
        position.x = 0;
    }
}

void Player::draw() {
    spriteSheet.draw(position);
}

void Player::dashMaking() {
    float dt = GetFrameTime();

    dashing = false;
    
    if (justPressedLeft) {
        pressAgainTime += dt;
        if (IsKeyPressed(KEY_A) && pressAgainTime < pressAgainMaxTime) {
            velocity.x = -dashForce;
            pressAgainTime = 0;
            dashing = true;
            justPressedLeft = false;
        }
    }

    if (IsKeyPressed(KEY_A) && dashing == false) {
        justPressedLeft = true;
    }
}
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

    // dash
    dashCooldownCD = 2;
    pressAgainTimeCD = 0.5;
    dashForce = 3000;
    dashTimeCD = 0.2;

    dashing = false;
    justPressedLeft = false;
    justPressedRight = false;
    pressAgainTimeLeft = 0;
    pressAgainTimeRight = 0;
    dashTime = 0;
    dashCooldownTime = 0;
    just_dashed = false;
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

    if (dashing) {
        just_dashed = true;
        dashTime += dt;
        Log("d:" + std::to_string(dashTime));
        if (dashTime >= dashTimeCD) {
            dashTime = 0;
            dashing = false;
        }
    }

    if (just_dashed) {
        dashCooldownTime += dt;
        if (dashCooldownTime >= dashCooldownCD) {
            dashCooldownTime = 0;
            just_dashed = false;
        }
    }
    
    if (justPressedLeft) {
        pressAgainTimeLeft += dt;
        if (IsKeyPressed(KEY_A) && pressAgainTimeLeft < pressAgainTimeCD) {
            velocity.x = -dashForce;
            pressAgainTimeLeft = 0;
            dashing = true;
            justPressedLeft = false;
        }
        if (pressAgainTimeLeft >= pressAgainTimeCD) {
            pressAgainTimeLeft = 0;
            justPressedLeft = false;
        }
    }

    if (IsKeyPressed(KEY_A) && dashing == false && just_dashed == false) {
        justPressedLeft = true;
        justPressedRight = false;
    }

    if (justPressedRight) {
        pressAgainTimeRight += dt;
        if (IsKeyPressed(KEY_D) && pressAgainTimeRight < pressAgainTimeCD) {
            velocity.x = dashForce;
            pressAgainTimeRight = 0;
            dashing = true;
            justPressedRight = false;
        }
        if (pressAgainTimeRight >= pressAgainTimeCD) {
            pressAgainTimeRight = 0;
            justPressedRight = false;
        }
    }

    if (IsKeyPressed(KEY_D) && dashing == false && just_dashed == false) {
        justPressedRight = true;
        justPressedLeft = false;
    }
}
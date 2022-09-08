#include "Player.hpp"

Player::Player(Vector2 position, Texture2D texture, const int numberOfFrames, int scale)
: sS(texture, numberOfFrames, scale), position(position) {
    velocity = Vector2{0, 0};
    collisionRect = Rectangle{position.x + 2 * sS.scale, 
                              position.y + 1 * sS.scale, 
                              (sS.fWidth - 2) * sS.scale, 
                              sS.fHeight - sS.scale
                              };
    runSpeed = 900;
    jumpForce = 2300;
    gravity = 10000;
    damp = 0.000001;
    airDamp = 0.01;
    jumps = 1;
    maxJumps = jumps;
    grounded = true;

    // dash
    dashCooldownCD = 0.5;
    pressAgainTimeCD = 0.5;
    dashForce = 3300;
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
    if (grounded) {
        velocity.x *= pow(damp, dt);
    }
    else {
        velocity.x *= pow(airDamp, dt);
    }
        

    if (abs(velocity.x) < 5) {
        velocity.x = 0;
        sS.texture = peoStill;
    } 
    else {
        sS.texture = peoSS;
    }

    if (abs(velocity.x) > 0) {
        if (velocity.x > 0) 
            sS.facing = 1;
        else if (velocity.x < 0)
            sS.facing = -1;
        sS.animate(10, dt);
        sS.draw(position);
    } 
    else {
        sS.draw(position);
    }
    
    if (!dashing) {
        if (IsKeyDown(KEY_A)) {
            velocity.x = -runSpeed;
        }

        if (IsKeyDown(KEY_D)) {
            velocity.x = runSpeed;
        }
    }
    
    if (IsKeyDown(KEY_UP) && jumps > 0) {
        velocity.y = -jumpForce;
        jumps -= 1;
    }
    if (IsKeyReleased(KEY_UP)) {
        jumps = 0;
    }

    dashMaking();

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    collisionRect.x = position.x;
    collisionRect.y = position.y;
    if (position.y > winH - sS.fHeight * sS.scale) {
        position.y = winH - sS.fHeight * sS.scale;
        jumps = maxJumps;
        grounded = true;

        if (velocity.y > gravity * 0.01) {
            // duns
        }

        velocity.y = 0;
    }
    else {
        grounded = false;
    }

    if (position.x + (sS.fWidth - 2) * sS.scale > winW) {
        position.x = winW - (sS.fWidth - 2) * sS.scale;
    }
    if (position.x + 2 * sS.scale < 0) {
        position.x = -2 * sS.scale;
    }
}

void Player::dashMaking() {
    float dt = GetFrameTime();

    if (dashing) {
        just_dashed = true;
        dashTime += dt;
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
            velocity.y = -dashForce / 7;
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
            velocity.y = -dashForce / 7;
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
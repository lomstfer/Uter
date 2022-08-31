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
    

    if (IsKeyDown(KEY_A)) {
        velocity.x = -runSpeed;
    }
    if (IsKeyDown(KEY_D)) {
        velocity.x = runSpeed;
    }
    if (IsKeyDown(KEY_SPACE) && jumps > 0) {
        velocity.y = -jumpForce;
        jumps -= 1;
    }

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    if (position.y > winH - spriteSheet.texture.height * spriteSheet.scale) {
        position.y = winH - spriteSheet.texture.height * spriteSheet.scale;
        jumps = 1;
    }
}



void Player::draw() {
    spriteSheet.draw(position);
}
#include "Player.hpp"

#define Log(x) std::cout << x << std::endl;

Player::Player(Vector2 position, Texture2D texture, const int numberOfFrames, int scale)
: position(position), collisionPosition(position), spriteSheet(texture, numberOfFrames, scale) {
    velocity = Vector2{0, 0};
    runSpeed = 400;
    jumpForce = 1000;
    damp = 0.0001;
}

void Player::update() {
    float dt = GetFrameTime();

    velocity.y += gravity * dt;
    velocity.x *= pow(damp, dt);

    if (abs(velocity.x) < 5) {
        velocity.x = 0;
        spriteSheet.texture = textures->peoStill;
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
    if (IsKeyDown(KEY_SPACE)) {
        velocity.y = -jumpForce;
    }

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;


    if (position.y > 750 - spriteSheet.texture.height * spriteSheet.scale) {
        position.y = 750 - spriteSheet.texture.height * spriteSheet.scale;
    }
}

void Player::draw() {
    spriteSheet.draw(position);
}
#include "PlayerCree.hpp"

Player::Player(Vector2 position, Texture2D texture, const int numberOfFrames, float scale)
: position(position), sS(texture, numberOfFrames, scale)  {
    velocity = Vector2{0, 0};
    collisionRect = Rectangle{position.x - (sS.fWidth/2 - (2)) * SPRITESCALE, 
                              position.y - (sS.fHeight/2 - (1)) * SPRITESCALE, 
                              (4) * SPRITESCALE, 
                              (7) * SPRITESCALE
                              };
    runSpeed = 4000;
    jumpForce = 1000;
    gravity = 10000;
    damp = 0.000001;
    airDamp = 0.001;
    jumps = 1;
    maxJumps = jumps;
    grounded = true;
}

Player::Attack::Attack(Vector2 position, Vector2 velocity)
: velocity(velocity), position(position) {}

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
        sS.texture = PEO_STILL;
    } 
    else {
        sS.texture = CREE_SS;
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
    
    if (IsKeyDown(KEY_A)) {
        velocity.x += -runSpeed * dt;
    }

    if (IsKeyDown(KEY_D)) {
        velocity.x += runSpeed * dt;
    }
    
    if (IsKeyDown(KEY_SPACE) && jumps > 0) {
        velocity.y = -jumpForce;
        jumps -= 1;
    }
    if (IsKeyReleased(KEY_SPACE)) {
        jumps = 0;
    }

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    if (position.y + sS.fHeight/2 * sS.scale > WINH-GROUND_HEIGHT*SPRITESCALE) {
        position.y = WINH-GROUND_HEIGHT*SPRITESCALE - sS.fHeight/2 * sS.scale;
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

    if (position.x + (sS.fWidth/2 - 2) * SPRITESCALE > WINW) {
        position.x = WINW - (sS.fWidth/2 - 2) * SPRITESCALE;
    }
    if (position.x - (sS.fWidth/2 - 2) * SPRITESCALE < 0) {
        position.x = (sS.fWidth/2 - 2) * SPRITESCALE;
    }

    collisionRect = {position.x - (sS.fWidth/2 - (2)) * SPRITESCALE, 
                    position.y - (sS.fHeight/2 - (1)) * SPRITESCALE, 
                    (4) * SPRITESCALE, 
                    (7) * SPRITESCALE};
}

void Player::updateAttacks(Vector2 boss_position, bool boss_alive) {
    float dt = GetFrameTime();
    if (boss_alive)
        attackTime += dt;
    if (attackTime >= attackNow) {
        attackTime = 0;
        float d = sqrt(pow(boss_position.x - position.x,2) + pow(boss_position.y - position.y,2));
        attacks.emplace_back(position, Vector2{(boss_position.x - position.x)/d * 600.f, (boss_position.y - position.y)/d * 600.f});
    }

    for (int i = 0; i < attacks.size();) {
        attacks[i].velocity.y += 300.f * dt;
        attacks[i].position.x += attacks[i].velocity.x * dt;
        attacks[i].position.y += attacks[i].velocity.y * dt;
        DrawRectangle(attacks[i].position.x, attacks[i].position.y, SPRITESCALE, SPRITESCALE, {252,231,43,255});

        if (attacks[i].position.x > boss_position.x - 10*SPRITESCALE &&
            attacks[i].position.x < boss_position.x + 10*SPRITESCALE &&
            attacks[i].position.y > boss_position.y - 10*SPRITESCALE &&
            attacks[i].position.y < boss_position.y + 10*SPRITESCALE) {
                attacks.erase(attacks.begin() + i);
                attackHit = true;
            }
        else if (attacks[i].position.y > WINH)
            attacks.erase(attacks.begin() + i);
        else
            i++;
    }
}
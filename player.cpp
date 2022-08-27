#include "Player.hpp"

Player::Player(Vector2 position, const char* filePath, const int numberOfFrames)
: position(position), spriteSheet(filePath, numberOfFrames) {

}

void Player::update() {
    position.x += 1;
}
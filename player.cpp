#include "Player.hpp"

Player::Player(Vector2 position, Texture2D texture, const int numberOfFrames, int scale)
: position(position), spriteSheet(texture, numberOfFrames, scale) {

}

void Player::update() {
    position.x += 1;
}
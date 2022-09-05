#include "Boss.hpp"

Boss::Boss(Vector2 position, Texture2D texture, const int numberOfFrames, int scale)
: sS(texture, numberOfFrames, scale), position(position) {
    
}
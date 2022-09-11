#include "Globals.hpp"
#include <math.h>
#include <iostream>
#include "SpriteSheet.hpp"

class Boss {
public:
    Boss(Vector2 position);
    void update(Vector2 playerPosition);

private:
    void attack();
    void mov1();

    Texture2D tT;
    SpriteSheet SS;
    float rotation;
    float rotationSpeed;
    float rotationSpeedMax;
    int shape;
    int scale;
    Vector2 position;
    Rectangle collisionRect;
    Vector2 velocity;

    int movementSystem;

    int difficulty;

    Vector2 playerPos;

    Vector2 p1;
    Vector2 p2;
    Vector2 p3;
    Vector2 p4;
    Vector2 p5;
};

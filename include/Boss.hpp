#include <math.h>
#include <vector>
#include "Globals.hpp"
#include <iostream>
#include "SpriteSheet.hpp"

class Boss {
public:
    Boss(Vector2 position);
    void update(Vector2 playerPosition);
    void draw();

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

    Vector2 p1s;
    Vector2 p1e;
    Vector2 p2s;
    Vector2 p2e;
    Vector2 p3s;
    Vector2 p3e;
    Vector2 p4s;
    Vector2 p4e;
    Vector2 p5s;
    Vector2 p5e;

    RenderTexture2D shapeT;

    class Attack {
    public:
        Attack(Vector2 position);
        Vector2 position;
    };
    std::vector<Attack> attackList;
    float attackTime;
};

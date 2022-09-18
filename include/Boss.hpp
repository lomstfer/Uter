#include <math.h>
#include <vector>
#include "Globals.hpp"
#include <iostream>
#include "SpriteSheet.hpp"
#include "Player.hpp"

class Boss {
public:
    Boss(int difficulty);
    void update(const Player& player);
    void draw();

    void looseHealth(float amount);
    bool killed;

    void die();
private:
    void attack();
    void updateAttacks(const Player& player);
    void mov1();

    int difficulty;
    float time;

    float health;
    float maxHealth;
    Rectangle healthRect;
    float healthWStore;

    float rotation;
    float rotationSpeed;
    float rotationSpeedMax;
    int shape;
    int scale;
    Vector2 position;
    Rectangle collisionRect;
    Vector2 velocity;
    float movSysTime;

    int movementSystem;

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

    float alphaOnStuff = 255;

    class Attack {
    public:
        Attack(Vector2 position, Vector2 velocity);
        Vector2 position;
        Vector2 velocity;
    };
    std::vector<Attack> attackList;
    float attackTime;
};

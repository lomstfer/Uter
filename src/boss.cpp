#include "Boss.hpp"

Vector2 rotate_point(float cx, float cy, float angle, Vector2 p)
{
  float s = sin(angle);
  float c = cos(angle);

  // translate point back to origin:
  p.x -= cx;
  p.y -= cy;

  // rotate point
  float xnew = p.x * c - p.y * s;
  float ynew = p.x * s + p.y * c;

  // translate point back:
  p.x = xnew + cx;
  p.y = ynew + cy;
  return p;
}

Boss::Boss(Vector2 position)
: position(position), SS(BOSSBIG, 15, ftint(SPRITESCALE * (rand()%2 + 1))) {
    movementSystem = 1;
    scale = SPRITESCALE;
    difficulty = 1;
    
    rotation = 0;
    rotationSpeed = 0;
    rotationSpeedMax = 10;
    shape = 2;
    switch (shape)
    {
    case 1:
        // rectangle
        tT = RECTANGLE;
    break;

    case 2:
        // triangle
        tT = TRIANGLE;
    
    default: break;
    }
    
}

void Boss::update(Vector2 playerPosition) {
    playerPos = playerPosition;
    switch (movementSystem)
    {
    case 1:
        mov1();
        break;
    
    default:
        break;
    }

    rotationSpeed = GetFrameTime() * (velocity.x) * 10;
    if (rotationSpeed > rotationSpeedMax)
        rotationSpeed = rotationSpeedMax;
    rotation += rotationSpeed * GetFrameTime();

    DrawTexturePro(tT, {0,0,tT.width,tT.height}, {position.x,position.y,tT.width*scale,tT.height*scale}, Vector2{tT.width/2*scale,tT.height/2*scale}, rotation, Color{255,255,255,255});
}

void Boss::mov1() {
    float dt = GetFrameTime();

    position.y += sin(GetTime()) * difficulty * 100 * dt;

    if (playerPos.x > position.x + 100) {
        velocity.x += difficulty * 50 * dt;
    }
    if (playerPos.x < position.x - 100) {
        velocity.x -= difficulty * 50 * dt;
    }

    if (position.x < 0) {
        if (velocity.x < 0) {
            velocity.x += -velocity.x * dt * 5;
        } 
    }
    if (position.x > WINW) {
        if (velocity.x > 0) {
            velocity.x += -velocity.x * dt * 5;
        } 
    }

    position.x += velocity.x * dt;
}
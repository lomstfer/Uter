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
    shape = 1;
    switch (shape)
    {
    case 1: 
        p1.x = position.x + 100;
        p1.y = position.y - 100;
        p2.x = position.x + 100;
        p2.y = position.y + 100;
        p3.x = position.x - 100;
        p3.y = position.y + 100;
        p4.x = position.x - 100;
        p4.y = position.y - 100;
    break;
    
    default: break;
    }
    tT = BOSS1;
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

    rotationSpeed = GetFrameTime() * (velocity.x);
    if (rotationSpeed > rotationSpeedMax)
        rotationSpeed = rotationSpeedMax;
    rotation += rotationSpeed * GetFrameTime();

    p1 = rotate_point(position.x, position.y, rotation, p1);
    p2 = rotate_point(position.x, position.y, rotation, p2);
    p3 = rotate_point(position.x, position.y, rotation, p3);
    p4 = rotate_point(position.x, position.y, rotation, p4);

    DrawLine(p1.x, p1.y, p2.x, p2.y, WHITE);
    DrawLine(p2.x, p2.y, p3.x, p3.y, WHITE);
    DrawLine(p3.x, p3.y, p4.x, p4.y, WHITE);
    DrawLine(p4.x, p4.y, p1.x, p1.y, WHITE);
    DrawLine(position.x, position.y, p2.x, p2.y, WHITE);
    DrawLine(position.x, position.y, p3.x, p3.y, WHITE);
    DrawLine(position.x, position.y, p1.x, p1.y, WHITE);
    DrawLine(position.x, position.y, p4.x, p4.y, WHITE);

    switch (shape)
    {
    case 1:
        DrawTexturePro(tT, {0,0,tT.width,tT.height}, {position.x,position.y,tT.width*scale,tT.height*scale}, Vector2{tT.width/2*scale,tT.height/2*scale}, rotation, Color{255,255,255,255});
        break;
    case 2:
        DrawTexturePro(tT, {0,0,tT.width,tT.height}, {position.x,position.y,tT.width*scale,tT.height*scale}, Vector2{tT.width/2*scale,tT.height/2*scale}, rotation, WHITE);
        break;
    default:
        break;
    }
}

void Boss::mov1() {
    float dt = GetFrameTime();

    position.y += sin(GetTime()) * difficulty * 100 * dt;
    p1.y += sin(GetTime()) * difficulty * 100 * dt;
    p2.y += sin(GetTime()) * difficulty * 100 * dt;
    p3.y += sin(GetTime()) * difficulty * 100 * dt;
    p4.y += sin(GetTime()) * difficulty * 100 * dt;

    if (playerPos.x > position.x + 100) {
        velocity.x += difficulty * 50 * dt;
        velocity.x += difficulty * rotationSpeed * 10 * dt;
    }
    if (playerPos.x < position.x - 100) {
        velocity.x -= difficulty * 50 * dt;
        velocity.x += difficulty * rotationSpeed * 10 * dt;
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
    p1.x += velocity.x * dt;
    p2.x += velocity.x * dt;
    p3.x += velocity.x * dt;
    p4.x += velocity.x * dt;
}
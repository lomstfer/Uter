#include "Boss.hpp"

Vector2 rotatePoint(float cx, float cy, float angle, Vector2 p)
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

    velocity = {0,0};
    
    rotation = 0;
    rotationSpeed = 0;
    rotationSpeedMax = 10;
    shape = 2;
    switch (shape)
    {
    case 1:
        shapeTarget = LoadRenderTexture(32, 32);

        // rectangle
        tT = RECTANGLE;
    break;

    case 2:
        shapeTarget = LoadRenderTexture(128, 128);
        // triangle
        tT = TRIANGLE;
        
        // right leg
        p1s = {shapeTarget.texture.width/2,30};
        p1e = {shapeTarget.texture.width-32,shapeTarget.texture.height-44};

        // left leg
        p2s = {p1s.x,p1s.y};
        p2e = {32,shapeTarget.texture.height-44};

        // bottom
        p3s = {p2e.x, p2e.y};
        p3e = {p1e.x, p1e.y};
    
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
    
    rotationSpeed = velocity.x;
    if (rotationSpeed > rotationSpeedMax)
        rotationSpeed = rotationSpeedMax;
    if (rotationSpeed < -rotationSpeedMax)
        rotationSpeed = -rotationSpeedMax;
    rotation += rotationSpeed * GetFrameTime();

    p1s = rotatePoint(64, 64, rotationSpeed * 0.1 * GetFrameTime(), p1s);
    p1e = rotatePoint(64, 64, rotationSpeed * 0.1 * GetFrameTime(), p1e);

    p2s = rotatePoint(64, 64, rotationSpeed * 0.1 * GetFrameTime(), p2s);
    p2e = rotatePoint(64, 64, rotationSpeed * 0.1 * GetFrameTime(), p2e);

    p3s = rotatePoint(64, 64, rotationSpeed * 0.1 * GetFrameTime(), p3s);
    p3e = rotatePoint(64, 64, rotationSpeed * 0.1 * GetFrameTime(), p3e);

    BeginTextureMode(shapeTarget);
        ClearBackground(Color{0, 0, 0, 0});
        DrawLine(p1s.x,p1s.y,p1e.x,p1e.y,WHITE);
        DrawLine(p2s.x,p2s.y,p2e.x,p2e.y,BLUE);
        DrawLine(p3s.x,p3s.y,p3e.x,p3e.y,GREEN);
    EndTextureMode();
}

void Boss::draw() {
    DrawTexturePro(shapeTarget.texture, {0,0,shapeTarget.texture.width,-shapeTarget.texture.height}, {position.x,position.y,shapeTarget.texture.width*scale,shapeTarget.texture.height*scale}, Vector2{shapeTarget.texture.width/2*scale,shapeTarget.texture.height/2*scale}, 0, Color{255,255,255,255});
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
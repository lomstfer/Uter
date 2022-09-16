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
    attackTime = 0;
    
    rotation = 0;
    rotationSpeed = 0;
    rotationSpeedMax = 20;
    shape = rand()%2+1;

    switch (shape)
    {
    case 1:
        // rectangle
        shapeT = LoadRenderTexture(64, 64);
        tT = RECTANGLE;
        // up
        p1s = {shapeT.texture.width/4,shapeT.texture.height/4};
        p1e = {shapeT.texture.width/4 + 32,shapeT.texture.height/4};
        // down
        p2s = {shapeT.texture.width/4,shapeT.texture.height/4 + 32};
        p2e = {shapeT.texture.width/4 + 32,shapeT.texture.height/4 + 32};
        // left
        p3s = {p1s.x, p1s.y};
        p3e = {p2s.x, p2s.y};
        // right
        p4s = {p1e.x, p1e.y};
        p4e = {p2e.x, p2e.y};
    break;

    case 2:
        // triangle
        shapeT = LoadRenderTexture(80, 80);
        tT = TRIANGLE;
        
        // right leg
        p1s = {shapeT.texture.width/2,0.23*shapeT.texture.height};
        p1e = {shapeT.texture.width - 0.25*shapeT.texture.width,shapeT.texture.height - 0.34*shapeT.texture.height};

        // left leg
        p2s = {p1s.x,p1s.y};
        p2e = {0.25*shapeT.texture.width,shapeT.texture.height-0.34*shapeT.texture.height};

        // bottom
        p3s = {p2e.x, p2e.y};
        p3e = {p1e.x, p1e.y};
    
    default: break;
    }
    
    
}

void Boss::update(const Player& player) {
    playerPos = player.position;

    attackTime += GetFrameTime();

    if (attackTime >= 1) {
        attackTime = 0;
        attack();
    }
    
    switch (movementSystem)
    {
    case 1: mov1(); break;
    
    default: break;
    }
    
    switch (shape)
    {
    case 1:
        // rectangle
        p1s = rotatePoint(shapeT.texture.width/2, shapeT.texture.height/2, rotationSpeed * 0.05 * GetFrameTime(), p1s);
        p1e = rotatePoint(shapeT.texture.width/2, shapeT.texture.height/2, rotationSpeed * 0.05 * GetFrameTime(), p1e);

        p2s = rotatePoint(shapeT.texture.width/2, shapeT.texture.height/2, rotationSpeed * 0.05 * GetFrameTime(), p2s);
        p2e = rotatePoint(shapeT.texture.width/2, shapeT.texture.height/2, rotationSpeed * 0.05 * GetFrameTime(), p2e);

        p3s = rotatePoint(shapeT.texture.width/2, shapeT.texture.height/2, rotationSpeed * 0.05 * GetFrameTime(), p3s);
        p3e = rotatePoint(shapeT.texture.width/2, shapeT.texture.height/2, rotationSpeed * 0.05 * GetFrameTime(), p3e);

        p4s = rotatePoint(shapeT.texture.width/2, shapeT.texture.height/2, rotationSpeed * 0.05 * GetFrameTime(), p4s);
        p4e = rotatePoint(shapeT.texture.width/2, shapeT.texture.height/2, rotationSpeed * 0.05 * GetFrameTime(), p4e);

        BeginTextureMode(shapeT);
            ClearBackground(Color{0, 0, 0, 0});
            DrawLine(p1s.x,p1s.y,p1e.x,p1e.y,WHITE);
            DrawLine(p2s.x,p2s.y,p2e.x,p2e.y,WHITE);
            DrawLine(p3s.x,p3s.y,p3e.x,p3e.y,WHITE);
            DrawLine(p4s.x,p4s.y,p4e.x,p4e.y,WHITE);
        EndTextureMode();
    break;

    case 2:
        // triangle
        p1s = rotatePoint(shapeT.texture.width/2, shapeT.texture.height/2, rotationSpeed * 0.05 * GetFrameTime(), p1s);
        p1e = rotatePoint(shapeT.texture.width/2, shapeT.texture.height/2, rotationSpeed * 0.05 * GetFrameTime(), p1e);

        p2s = rotatePoint(shapeT.texture.width/2, shapeT.texture.height/2, rotationSpeed * 0.05 * GetFrameTime(), p2s);
        p2e = rotatePoint(shapeT.texture.width/2, shapeT.texture.height/2, rotationSpeed * 0.05 * GetFrameTime(), p2e);

        p3s = rotatePoint(shapeT.texture.width/2, shapeT.texture.height/2, rotationSpeed * 0.05 * GetFrameTime(), p3s);
        p3e = rotatePoint(shapeT.texture.width/2, shapeT.texture.height/2, rotationSpeed * 0.05 * GetFrameTime(), p3e);

        BeginTextureMode(shapeT);
            ClearBackground(Color{0, 0, 0, 0});
            
            DrawLine(p1s.x,p1s.y,p1e.x,p1e.y,WHITE);
            DrawLine(p2s.x,p2s.y,p2e.x,p2e.y,WHITE);
            DrawLine(p3s.x,p3s.y,p3e.x,p3e.y,WHITE);
            
        EndTextureMode();
    
    default: break;
    }

    updateAttacks(player);
}

Boss::Attack::Attack(Vector2 position)
: position(position) {}

void Boss::updateAttacks(const Player& player) {
    for (int i = 0; i < attackList.size();) {
        attackList[i].position.y += 100 * GetFrameTime();

        if (CheckCollisionRecs(player.collisionRect, {attackList[i].position.x-SMALL_CIRCLE.width/2*SPRITESCALE,attackList[i].position.y-SMALL_CIRCLE.height/2*SPRITESCALE,SMALL_CIRCLE.width*SPRITESCALE,SMALL_CIRCLE.height*SPRITESCALE})
            /* attackList[i].position.y + SMALL_CIRCLE.height/2 * SPRITESCALE >= playerPos.y - PEOSTILL.height/2 * SPRITESCALE &&
            attackList[i].position.x + SMALL_CIRCLE.width/2 * SPRITESCALE >= playerPos.x - PEOSTILL.width/2 * SPRITESCALE &&
            attackList[i].position.x - SMALL_CIRCLE.height/2 * SPRITESCALE <= playerPos.x + PEOSTILL.width/2 * SPRITESCALE */) {
                Log("HIT");
                attackList.erase(attackList.begin() + i);
            }

        else if (attackList[i].position.y > WINH) {
            attackList.erase(attackList.begin() + i);
        }
        else {
            i++;
        }
    }
}

void Boss::draw() {
    DrawTexturePro(shapeT.texture, {0,0,shapeT.texture.width,-shapeT.texture.height}, {position.x,position.y,shapeT.texture.width*scale,shapeT.texture.height*scale}, Vector2{shapeT.texture.width/2*scale,shapeT.texture.height/2*scale}, 0, Color{255,255,255,255});
    for (int i = 0; i < attackList.size(); i++) {
        DrawTextureEx(SMALL_CIRCLE, {attackList[i].position.x - SMALL_CIRCLE.width*SPRITESCALE/2,attackList[i].position.y - SMALL_CIRCLE.height*SPRITESCALE/2}, 0, SPRITESCALE, WHITE);
    }
}

void Boss::attack() {
    Attack at = Attack(position);
    attackList.push_back(at);
}

void Boss::mov1() {
    float dt = GetFrameTime();

    rotationSpeed = velocity.x;
    if (rotationSpeed > rotationSpeedMax)
        rotationSpeed = rotationSpeedMax;
    if (rotationSpeed < -rotationSpeedMax)
        rotationSpeed = -rotationSpeedMax;
    rotation += rotationSpeed * GetFrameTime();

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
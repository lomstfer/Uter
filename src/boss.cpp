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

Boss::Boss(int difficulty)
: difficulty(difficulty) {
    movementSystem = 0;

    scale = SPRITESCALE;

    health = 100;
    maxHealth = health;
    healthRect = {0, 0, health/maxHealth * WINW, 1.66f * SPRITESCALE};
    healthWStore = healthRect.width;
    killed = false;

    position = {WINW/2, -WINH/5};
    velocity = {0,0};
    attackTime = 0;
    movSysTime = 0;
    
    rotation = 0;
    rotationSpeed = 0;
    rotationSpeedMax = 20;
    shape = rand()%2+1;

    switch (shape)
    {
    case 1:
        // rectangle
        shapeT = LoadRenderTexture(64, 64);
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
    time += GetFrameTime();
    playerPos = player.position;

    if (movementSystem > 0)
        attackTime += GetFrameTime();

    if (IsKeyPressed(KEY_L)) {
        looseHealth(20);
    }

    if (healthRect.height > 1.66f * SPRITESCALE) {
        healthRect.height -= healthRect.height * 5.f * GetFrameTime();
        if (healthRect.height < 1.66f * SPRITESCALE)
            healthRect.height = 1.66f * SPRITESCALE;
    }
    if (healthRect.width > healthWStore) {
        healthRect.width -= (healthRect.width - healthWStore) * 10.f * GetFrameTime();
        if (healthRect.width < healthWStore)
            healthRect.width = healthWStore;
    }

    if (attackTime >= 1 / (float)difficulty * 4) {
        attackTime = 0;
        attack();
    }

    switch (movementSystem)
    {
    case 0: 
        position.y += 80/time * GetFrameTime();
        if (position.y > WINH/5) {
            movementSystem = rand()%1 + 1;
        }
    break;

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
            DrawLine(p1s.x,p1s.y,p1e.x,p1e.y,{255,255,255,alphaOnBoss});
            DrawLine(p2s.x,p2s.y,p2e.x,p2e.y,{255,255,255,alphaOnBoss});
            DrawLine(p3s.x,p3s.y,p3e.x,p3e.y,{255,255,255,alphaOnBoss});
            DrawLine(p4s.x,p4s.y,p4e.x,p4e.y,{255,255,255,alphaOnBoss});
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
            
            DrawLine(p1s.x,p1s.y,p1e.x,p1e.y,{255,255,255,alphaOnBoss});
            DrawLine(p2s.x,p2s.y,p2e.x,p2e.y,{255,255,255,alphaOnBoss});
            DrawLine(p3s.x,p3s.y,p3e.x,p3e.y,{255,255,255,alphaOnBoss});
        EndTextureMode();
    
    default: break;
    }

    updateAttacks(player);
}

void Boss::draw() {
    DrawTexturePro(shapeT.texture, {0,0,shapeT.texture.width,-shapeT.texture.height}, {position.x,position.y,shapeT.texture.width*scale,shapeT.texture.height*scale}, Vector2{shapeT.texture.width/2*scale,shapeT.texture.height/2*scale}, 0, Color{255,255,255,255});
    for (int i = 0; i < attackList.size(); i++) {
        DrawTextureEx(SMALL_CIRCLE, {attackList[i].position.x - SMALL_CIRCLE.width*SPRITESCALE/2,attackList[i].position.y - SMALL_CIRCLE.height*SPRITESCALE/2}, 0, SPRITESCALE, {255,255,255,alphaOnAttacks});
    }

    DrawRectangle(healthRect.x, healthRect.y, healthRect.width, healthRect.height, RED);
}

void Boss::attack() {
    Attack at = Attack(position, velocity);
    attackList.push_back(at);
}

Boss::Attack::Attack(Vector2 position, Vector2 velocity)
: position(position), velocity({0,0}) {}

void Boss::updateAttacks(const Player& player) {
    for (int i = 0; i < attackList.size();) {
        attackList[i].velocity.y = 100;
        if (abs(attackList[i].position.x - player.position.x) > 50)
        {
            if (attackList[i].position.x - player.position.x < 0) {
                attackList[i].velocity.x -= 10.f/(attackList[i].position.x - player.position.x) * 100.f;
            }
            if (attackList[i].position.x - player.position.x > 0) {
                attackList[i].velocity.x -= 10.f/(attackList[i].position.x - player.position.x) * 100.f;
            }
        }
        if (killed) {
            velocity.x = 0;
            Log("i1");
            velocity.y += 100.f * GetFrameTime();
        }
        
        attackList[i].position.y += attackList[i].velocity.y * GetFrameTime();
        attackList[i].position.x += attackList[i].velocity.x * GetFrameTime();

        if (CheckCollisionRecs(player.collisionRect, {attackList[i].position.x-SMALL_CIRCLE.width/2*SPRITESCALE,attackList[i].position.y-SMALL_CIRCLE.height/2*SPRITESCALE,SMALL_CIRCLE.width*SPRITESCALE,SMALL_CIRCLE.height*SPRITESCALE})) {                
            attackList.erase(attackList.begin() + i);
            killedPlayer = true;
        }
        else if (attackList[i].position.y > WINH + 100) {
            attackList.erase(attackList.begin() + i);
        }
        else {
            i++;
        }
    }
}

void Boss::looseHealth(float amount) {
    health -= amount;
    healthRect.height *= 1.5f + amount/6.f;
    if (health <= 0) {
        killed = true;
    }
    healthWStore = health/maxHealth * WINW;
}

void Boss::die() {
    alphaOnBoss -= 100.f * GetFrameTime();
    if (alphaOnBoss < 0) {
        alphaOnBoss = 0;
    }
    velocity.x *= pow(0.00001,GetFrameTime());
    velocity.y *= pow(0.00001,GetFrameTime());
    rotationSpeed = 0;
}

void Boss::mov1() {
    float dt = GetFrameTime();
    movSysTime += dt;

    rotationSpeed = velocity.x;
    if (rotationSpeed > rotationSpeedMax)
        rotationSpeed = rotationSpeedMax;
    if (rotationSpeed < -rotationSpeedMax)
        rotationSpeed = -rotationSpeedMax;
    rotation += rotationSpeed * GetFrameTime();

    position.y += sin(movSysTime) * 100 * dt;

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
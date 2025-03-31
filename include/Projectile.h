#ifndef PROJECTILE_H
#define PROJECTILE_H
#pragma once
#include <SDL2/SDL.h>
#include "Ultilities.h"

class Projectile {
public:
    Projectile(int startX, int startY, Direction dir, float speed, Color color, int width, int height);
    Projectile();
    virtual ~Projectile() = default;

    virtual void update();
    virtual void render(SDL_Renderer* renderer);
    virtual bool hasHitPlayer();
    virtual bool hasHitShield();
    bool isOffScreen();

    GameObject gameObject;
    Direction direction;
    float speed;
    bool isAlive = true;
};

class EnemyProjectile : public Projectile {
public:
    EnemyProjectile(int startX, int startY, Direction dir, float speed);
    bool hasHitPlayer() override;
    bool hasHitShield() override;
};

class BuffProjectile : public Projectile {
public:
    BuffProjectile(int startX, int startY, Direction dir, float speed);
    bool hasHitPlayer() override;
};

#endif

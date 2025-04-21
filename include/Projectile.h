#ifndef PROJECTILE_H
#define PROJECTILE_H
#pragma once
#include <SDL2/SDL.h>
#include <bits/stdc++.h>
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

class PlayerProjectile : public Projectile{
public:
    PlayerProjectile(int startX, int startY, float speed);
    bool hasHitBoss();
    void update() override;
    bool hasHitPlayer() override;
    bool hasHitShield() override;
    void render(SDL_Renderer* renderer) override;
private:
    Uint32 destroyedTime;
};

class HealthProjectile : public Projectile {
public:
    HealthProjectile(int startX, int startY, Direction dir, float speed);
    bool hasHitPlayer() override;
    void update() override;
    void render(SDL_Renderer* renderer) override;
private:
    float animTime = 0.0f;
    float scale = 1.0f;
};

class TrickyProjectile : public Projectile {
public:
    TrickyProjectile(int startX, int startY, Direction dir, float speed);

    bool hasHitPlayer() override;
    bool hasHitShield() override;
    void update() override;
    void render(SDL_Renderer* renderer) override;

private:
    bool switchedLane = false;
    float switchAnimProgress = 0.0f; // 0.0 to 1.0
    Vector animStartPos;
    Vector animEndPos;
    Direction originalDir;
    Direction newDir;
    void startLaneSwitch();
    bool isNearPlayer();
};

#endif

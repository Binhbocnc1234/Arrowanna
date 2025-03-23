#ifndef PROJECTILE_H
#define PROJECTILE_H
#pragma once
#include <SDL2/SDL.h>
#include "Ultilities.h"
class Projectile {
public:
    Projectile() : speed(0), gameObject(0, 0) {};
    Projectile(int startX, int startY, Direction dir, float speed);
    void update();
    void render(SDL_Renderer* renderer);
    bool hasHitPlayer();
    bool hasHitShield();
    bool isOffScreen();
    
    GameObject gameObject;
    Direction direction;
    float speed;
    bool isAlive = true;
};

#endif

#ifndef WAVE_H
#define WAVE_H
#pragma once
#include <vector>
#include "Projectile.h"

class Wave {
public:
    Wave(int screenWidth, int screenHeight);
    void spawnProjectile();
    void update();
    void updateProjectiles();
    void renderProjectiles();
    void checkCollisions(int playerX, int playerY, SDL_Point shieldPoint, Direction shieldDir);

private:
    std::vector<Projectile> projectiles;
    int screenWidth, screenHeight;
    int frameCount = 0;
};

#endif

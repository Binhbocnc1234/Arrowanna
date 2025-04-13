#ifndef WAVE_H
#define WAVE_H
#pragma once
#include <vector>
#include "Projectile.h"

class Wave {
public:
    Wave();
    Wave(int width, int height);
    void spawnProjectile();
    void update();
    void updateProjectiles();
    void renderBoundaries();
    void renderProjectiles();
    void clearProjectiles();

private:
    std::vector<Projectile*> projectiles;
    int width, height;
    int frameCount = 0;
};

#endif

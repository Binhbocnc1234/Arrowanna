#ifndef WAVE_H
#define WAVE_H
#pragma once
#include <vector>
#include "Projectile.h"

enum class WaveMode {
    NORMAL,
    HYPED,
    SLOWMOTION,
    TRICKY_ONLY // New mode for only TrickyProjectile
};

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

    void setMode(WaveMode mode);
    WaveMode getMode() const;

private:
    std::vector<Projectile*> projectiles;
    int width, height;
    int frameCount = 0;
    WaveMode mode = WaveMode::NORMAL;
    int spawnDelay = 60; // Default for normal mode
    float projectileSpeed = 3.0f; // Default for normal mode

    // Add mode timer and duration
    int modeTimer = 0;
    int modeDuration = 800; // e.g., 600 frames (10 seconds at 60fps)
    void updateModeSettings();
    void nextMode(); // Helper to cycle to the next mode
};

#endif

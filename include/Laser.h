#pragma once
#include <SDL2/SDL.h>
#include "Ultilities.h"

enum class LaserState {
    Charging,
    Firing,
    Collapsing,
    Inactive
};

class Laser {
public:
    Laser(Direction lane, Uint32 chargeTime = 1200, Uint32 fireTime = 600, Uint32 collapseTime = 400);
    void update();
    void render(SDL_Renderer* renderer);
    bool isActive() const;
    bool checkBlock();
    bool checkHit();
    bool shouldDealDamage();

    void activate(Direction lane);
    void deactivate();

    LaserState getState() const { return state; }
    Direction getLane() const { return lane; }
    void setColor(SDL_Color c) { color = c; }
    void setMaxWidth(float w) { maxWidth = w; }

private:
    Direction lane;
    LaserState state = LaserState::Inactive;
    Uint32 startTime = 0;
    Uint32 chargeTime, fireTime, collapseTime;
    float width = 0.0f;
    float maxWidth = 80.0f;
    SDL_Color color = {255, 240, 240, 220}; // White with a bit red

    SDL_Texture* laserTexture = nullptr;
    bool damageDealt = false;
    void renderLaser(SDL_Renderer* renderer, float width, Uint8 alpha);
};

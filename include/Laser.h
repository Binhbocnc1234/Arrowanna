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
    Laser(Direction lane);
    void update();
    void render(SDL_Renderer* renderer);
    bool isActive() const;
    void activate(Direction lane);
    void deactivate();

    LaserState getState() const { return state; }
    Direction getLane() const { return lane; }

    // Gây sát thương, trả về true nếu đến thời điểm gây damage
    bool shouldDealDamage();

private:
    Direction lane;
    LaserState state = LaserState::Inactive;
    Uint32 startTime = 0;
    float width = 0.0f;
    float maxWidth = 50.0f; // Bằng shield
    SDL_Color color = {255, 240, 240, 90}; // Trạng thái Charge
    SDL_Texture* laserTexture = nullptr;

    // Thời gian các trạng thái (ms)
    Uint32 chargeTime = 2000;
    Uint32 fireTime = 750;
    Uint32 collapseTime = 400;

    // Firing damage logic
    Uint32 lastDamageTime = 0;
    Uint32 damageInterval = 250; // ms
    bool damageFrame = false;
};

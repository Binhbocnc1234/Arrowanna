#include "Ultilities.h"
#include "TextureLoader.h";

SDL_Renderer *GameConfig::renderer = nullptr;

SDL_Point getRectCenter(const SDL_Rect& rect) {
    SDL_Point center;
    center.x = rect.x + rect.w / 2;
    center.y = rect.y + rect.h / 2;
    return center;
}

//SCREEN SHAKE EFFECT
SDL_Renderer* ScreenShakeEffect::renderer = GameConfig::renderer;
SDL_Rect ScreenShakeEffect::camera = {0, 0, GameConfig::SCREEN_WIDTH, GameConfig::SCREEN_HEIGHT}; // Example screen size
bool ScreenShakeEffect::isShaking = false;
Uint32 ScreenShakeEffect::screenShakeStartTime = 0;
void ScreenShakeEffect::StartScreenShake() {
    screenShakeStartTime = SDL_GetTicks();
    isShaking = true;
}

void ScreenShakeEffect::UpdateScreenShake() {
    if (!isShaking) return;

    Uint32 elapsed = SDL_GetTicks() - screenShakeStartTime;
    if (elapsed >= screenShakeDuration) {
        isShaking = false;
        camera.x = 0;
        camera.y = 0;
        return;
    }

    // Apply random offset to camera position
    camera.x = (rand() % (screenShakeIntensity * 2 + 1)) - screenShakeIntensity;
    camera.y = (rand() % (screenShakeIntensity * 2 + 1)) - screenShakeIntensity;
}



#include "Ultilities.h"

SDL_Point getRectCenter(const SDL_Rect& rect) {
    SDL_Point center;
    center.x = rect.x + rect.w / 2;
    center.y = rect.y + rect.h / 2;
    return center;
}

// bool GameConfig::IS_DEBUG_MODE = false;
SDL_Renderer* GameConfig::renderer = nullptr;
int GameConfig::WAVE = 1;
#include "DamageObject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>

DamageObject::DamageObject(Vector pos, int damage, SDL_Renderer* renderer, TTF_Font* font)
    : position(pos), damage(damage)
{
    // Create texture for damage text
    SDL_Color color = {255, 80, 40, 255};
    std::stringstream ss;
    ss << damage;
    SDL_Surface* surf = TTF_RenderText_Solid(font, ss.str().c_str(), color);
    if (surf) {
        texture = SDL_CreateTextureFromSurface(renderer, surf);
        texW = surf->w;
        texH = surf->h;
        SDL_FreeSurface(surf);
    }
}

DamageObject::~DamageObject() {
    if (texture) SDL_DestroyTexture(texture);
}

void DamageObject::update() {
    age += 16.0f; // Assume ~60fps, or you can pass dt
    float t = age / duration;
    if (t < 0.3f) {
        scale = minScale + (maxScale - minScale) * (t / 0.3f); // Grow up
    } else {
        scale = maxScale - (maxScale - minScale) * ((t - 0.3f) / 0.7f); // Shrink back
        if (scale < minScale) scale = minScale;
    }
    if (t > 0.5f) {
        alpha = static_cast<Uint8>(255 * (1.0f - (t - 0.5f) / 0.5f));
        if (alpha > 255) alpha = 255;
        if (alpha < 0) alpha = 0;
    }
    // Move up slightly
    position.y -= 0.7f;
}

void DamageObject::render(SDL_Renderer* renderer) {
    if (!texture) return;
    SDL_Rect dst;
    dst.w = static_cast<int>(texW * scale);
    dst.h = static_cast<int>(texH * scale);
    dst.x = static_cast<int>(position.x - dst.w / 2);
    dst.y = static_cast<int>(position.y - dst.h / 2);
    SDL_SetTextureAlphaMod(texture, alpha);
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

bool DamageObject::isAlive() const {
    return age < duration;
}

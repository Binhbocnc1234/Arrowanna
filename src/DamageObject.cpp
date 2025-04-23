#include "DamageObject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>

DamageObject::DamageObject(Vector pos, int damage, SDL_Renderer* renderer, TTF_Font* font)
    : position(pos), damage(damage)
{
    // Create texture for damage text (main: red, border: white)
    SDL_Color borderColor = {255, 255, 255, 255}; // White border
    SDL_Color fillColor = {255, 40, 40, 255};     // Red fill

    std::stringstream ss;
    ss << damage;
    std::string dmgStr = ss.str();

    // Render border by drawing text multiple times offset by 1px in 8 directions
    const int borderSize = 2;
    SDL_Surface* borderSurfaces[8] = {nullptr};
    SDL_Surface* fillSurface = TTF_RenderText_Solid(font, dmgStr.c_str(), fillColor);

    // Create a surface big enough for border + fill
    int w = fillSurface->w + borderSize * 2;
    int h = fillSurface->h + borderSize * 2;
    SDL_Surface* finalSurface = SDL_CreateRGBSurface(0, w, h, 32,
        0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

    // Render border in 8 directions
    for (int i = 0; i < 8; ++i) {
        int dx = (i % 3) - 1;
        int dy = (i / 3) - 1;
        if (dx == 0 && dy == 0) continue;
        borderSurfaces[i] = TTF_RenderText_Solid(font, dmgStr.c_str(), borderColor);
        SDL_Rect dst = { borderSize + dx, borderSize + dy, borderSurfaces[i]->w, borderSurfaces[i]->h };
        SDL_BlitSurface(borderSurfaces[i], nullptr, finalSurface, &dst);
        SDL_FreeSurface(borderSurfaces[i]);
    }
    // Render fill in center
    SDL_Rect fillDst = { borderSize, borderSize, fillSurface->w, fillSurface->h };
    SDL_BlitSurface(fillSurface, nullptr, finalSurface, &fillDst);
    SDL_FreeSurface(fillSurface);

    texture = SDL_CreateTextureFromSurface(renderer, finalSurface);
    texW = finalSurface->w;
    texH = finalSurface->h;
    SDL_FreeSurface(finalSurface);
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
    dst.w = static_cast<int>(texW * scale * 1.5f); // Make it bigger
    dst.h = static_cast<int>(texH * scale * 1.5f);
    dst.x = static_cast<int>(position.x - dst.w / 2);
    dst.y = static_cast<int>(position.y - dst.h / 2);
    SDL_SetTextureAlphaMod(texture, alpha);
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

bool DamageObject::isAlive() const {
    return age < duration;
}

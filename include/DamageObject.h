#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Ultilities.h"

class DamageObject {
public:
    DamageObject(Vector pos, int damage, SDL_Renderer* renderer, TTF_Font* font);
    ~DamageObject();

    void update();
    void render(SDL_Renderer* renderer);
    bool isAlive() const;

private:
    Vector position;
    int damage;
    float age = 0.0f;
    float duration = 900.0f; // ms
    float scale = 1.0f;
    float maxScale = 1.6f;
    float minScale = 1.0f;
    Uint8 alpha = 255;
    SDL_Texture* texture = nullptr;
    int texW = 0, texH = 0;
};

#pragma once
#include <SDL2/SDL.h>
#include "Ultilities.h"

class Particle {
public:
    Vector position;
    Vector velocity;
    Color color;
    float lifetime; // ms
    float age = 0.0f;
    float gravity = -0.05f; // negative gravity (float up)
    int size;

    Particle(Vector pos, Vector vel, Color color, float lifetime, int size = 6);

    void update(float dt);
    void render(SDL_Renderer* renderer);
    bool isAlive() const;
};

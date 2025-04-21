#include "Particle.h"

Particle::Particle(Vector pos, Vector vel, Color color, float lifetime, int size)
    : position(pos), velocity(vel), color(color), lifetime(lifetime), size(size) {}

void Particle::update(float dt) {
    velocity.y += gravity * dt;
    position = position + velocity * dt;
    age += dt;
    // Fade out
    color.a = static_cast<int>(255 * (1.0f - age / lifetime));
    if (color.a < 0) color.a = 0;
}

void Particle::render(SDL_Renderer* renderer) {
    // Glow effect: draw several larger, more transparent rectangles behind the main particle
    int glowLayers = 3;
    int glowStep = 6;
    for (int i = glowLayers; i > 0; --i) {
        int glowSize = size + i * glowStep;
        int glowAlpha = static_cast<int>(color.a * (0.10f * i)); // Fainter as it gets bigger
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, glowAlpha);
        SDL_Rect glowRect = { static_cast<int>(position.x - glowSize/2), static_cast<int>(position.y - glowSize/2), glowSize, glowSize };
        SDL_RenderFillRect(renderer, &glowRect);
    }
    // Main particle
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { static_cast<int>(position.x - size/2), static_cast<int>(position.y - size/2), size, size };
    SDL_RenderFillRect(renderer, &rect);
}

bool Particle::isAlive() const {
    return age < lifetime && color.a > 0;
}

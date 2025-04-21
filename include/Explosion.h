#pragma once
#include <vector>
#include "Particle.h"

class Explosion {
public:
    Vector center;
    std::vector<Particle*> particles;

    Explosion(Vector center, int numParticles = 16, float R1 = 10.0f, float R2 = 40.0f);
    ~Explosion();

    void update(float dt);
    void render(SDL_Renderer* renderer);
    bool isAlive() const;
};

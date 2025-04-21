#include "Explosion.h"
#include <cmath>
#include <cstdlib>

Explosion::Explosion(Vector center, int numParticles, float R1, float R2)
    : center(center)
{
    for (int i = 0; i < numParticles; ++i) {
        float angle = (2 * M_PI * i) / numParticles;
        float dist = R1 + static_cast<float>(rand()) / RAND_MAX * (R2 - R1); // R2 = 80.0f
        Vector pos = center + Vector(cos(angle), sin(angle)) * dist;

        // Bigger and more varied initial velocity
        float speed = 0.08f + 0.22f * (rand() / (float)RAND_MAX); // 0.08 to 0.3
        Vector vel = Vector(cos(angle), sin(angle)) * speed;

        // Color: dark orange to light orange (e.g. RGB(180~255, 80~200, 0))
        int r = 180 + rand() % 76; // 180-255
        int g = 80 + rand() % 121; // 80-200
        Color color = Color(r, g, 0, 255);

        // Particle size: 8 to 24
        int size = 8 + rand() % 17; // 8-24

        float lifetime = 600 + rand() % 400; // ms
        Particle* p = new Particle(pos, vel, color, lifetime, size);
        p->gravity = -0.0012f;
        particles.push_back(p);
    }
}

Explosion::~Explosion() {
    for (auto* p : particles) delete p;
    particles.clear();
}

void Explosion::update(float dt) {
    for (auto it = particles.begin(); it != particles.end(); ) {
        (*it)->update(dt);
        if (!(*it)->isAlive()) {
            delete *it;
            it = particles.erase(it);
        } else {
            ++it;
        }
    }
}

void Explosion::render(SDL_Renderer* renderer) {
    for (auto* p : particles) {
        p->render(renderer);
    }
}

bool Explosion::isAlive() const {
    return !particles.empty();
}

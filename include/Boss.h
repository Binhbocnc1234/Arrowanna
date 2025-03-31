#ifndef BOSS_H
#define BOSS_H

#include "Ultilities.h"
#include "TextureLoader.h"
#include "HorizontalObstacle.h"
#include <vector>

class Boss {
public:
    Boss(int x, int y);
    void update();
    void render(SDL_Renderer* renderer);

private:
    GameObject gameObject;
    int health;
    std::vector<HorizontalObstacle*> obstacles;
    std::vector<string> sprites;
    int currentSpriteIndex;
    Uint32 lastSpriteChangeTime;
};

#endif // BOSS_H

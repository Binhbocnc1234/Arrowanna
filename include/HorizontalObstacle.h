#ifndef HORIZONTAL_OBSTACLE_H
#define HORIZONTAL_OBSTACLE_H
#pragma once

#include "Ultilities.h"
#include <SDL2/SDL.h>

class HorizontalObstacle {
public:
    HorizontalObstacle(float y, float speed);

    void update();
    void render(SDL_Renderer* renderer);

private:
    GameObject gameObject;
    float speed;
    bool movingRight;
};

#endif

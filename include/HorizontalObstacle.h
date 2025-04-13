#ifndef HORIZONTAL_OBSTACLE_H
#define HORIZONTAL_OBSTACLE_H
#pragma once

#include "Ultilities.h"
#include <SDL2/SDL.h>

class HorizontalObstacle {
public:
    HorizontalObstacle(float x, float y, float speed);
    int index;
    GameObject gameObject;
    void update();
    void render(SDL_Renderer* renderer);

private:
    float speed;
    bool movingRight;
};

#endif

#include "HorizontalObstacle.h"
#include "Ultilities.h"

HorizontalObstacle::HorizontalObstacle(float x, float y, float spd)
    : speed(spd), movingRight(true), gameObject(x, y) {
    gameObject.color = Color(0, 255, 0, 255);
    gameObject.width = 150;  // Large width
    gameObject.height = 10;  // Small height
}

void HorizontalObstacle::update() {
    if (movingRight) {
        gameObject.position.x += speed;
        if (gameObject.position.x + gameObject.width / 2 >= GameConfig::SCREEN_WIDTH) {
            movingRight = false;
        }
    } else {
        gameObject.position.x -= speed;
        if (gameObject.position.x - gameObject.width / 2 <= 0) {
            movingRight = true;
        }
    }
}

void HorizontalObstacle::render(SDL_Renderer* renderer) {
    gameObject.RectRender();
}

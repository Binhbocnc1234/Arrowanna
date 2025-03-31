#include "HorizontalObstacle.h"
#include "Ultilities.h"

HorizontalObstacle::HorizontalObstacle(float y, float spd)
    : speed(spd), movingRight(true), gameObject(GameConfig::SCREEN_WIDTH / 2, y) {
    gameObject.color = Color(0, 255, 0, 255);
    gameObject.width = 100;  // Large width
    gameObject.height = 20;  // Small height
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

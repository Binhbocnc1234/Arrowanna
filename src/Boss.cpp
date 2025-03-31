#include "Boss.h"
#include "Ultilities.h"

Boss::Boss(int x, int y) : gameObject(x, y, 32, 32), health(100), currentSpriteIndex(0), lastSpriteChangeTime(0) {
    TextureLoader::loadSprites("Boss", 3, 32, 32);
    for (int i = 0; i < 3; ++i){
        sprites.push_back("Boss_" + to_string(i));
    }
    // Create 4 obstacles evenly spaced along the Y-axis
    int spacing = GameConfig::SCREEN_HEIGHT / 5;
    for (int i = 1; i <= 4; ++i) {
        obstacles.push_back(new HorizontalObstacle(x, i * spacing));
    }
}

void Boss::update() {
    Uint32 currentTime = SDL_GetTicks();

    // Change sprite every 500ms
    if (currentTime - lastSpriteChangeTime >= 500) {
        lastSpriteChangeTime = currentTime;
        currentSpriteIndex = (currentSpriteIndex + 1) % sprites.size();
    }

    // Update all obstacles
    for (auto& obstacle : obstacles) {
        obstacle->update();
    }
}

void Boss::render(SDL_Renderer* renderer) {
    gameObject.TextureRender(sprites[currentSpriteIndex]);
    // Render all obstacles
    for (auto& obstacle : obstacles) {
        obstacle->render(renderer);
    }
}

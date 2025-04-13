#include "Boss.h"
#include "Wave.h"
#include "GameManager.h"
#include "Ultilities.h"

Boss *Boss::instance = nullptr;
Boss* Boss::getInstance(){
    return instance;
}
Boss::Boss(int x, int y, int maxHealth) : gameObject(x, y, 80, 80), health(maxHealth), maxHealth(maxHealth), 
currentSpriteIndex(0), lastSpriteChangeTime(0), wave(GameConfig::SCREEN_WIDTH, GameConfig::SCREEN_HEIGHT) {
    TextureLoader::loadSprites("Boss", 3, 32, 32);
    for (int i = 0; i < 3; ++i){
        sprites.push_back("Boss_" + to_string(i));
    }
    if (instance == nullptr){
        instance = this;
    } else {
        std::cerr << "Two or more instances of Player!" << std::endl;
    }
}

void Boss::update() {
    renderBoss(GameConfig::renderer);
    if (GameManager::getInstance()->gameState == GameState::PlayerTurn){
        // Update all obstacles
        for (auto& obstacle : obstacles) {
            obstacle->update();
        }
    }
    else{
        wave.update();
    }
}

void Boss::renderBoss(SDL_Renderer* renderer) {
    Uint32 currentTime = SDL_GetTicks();

    // Change sprite every 500ms
    if (currentTime - lastSpriteChangeTime >= 500) {
        lastSpriteChangeTime = currentTime;
        currentSpriteIndex = (currentSpriteIndex + 1) % sprites.size();
    }
    gameObject.TextureRender(sprites[currentSpriteIndex]);
    // Render all obstacles
    for (auto& obstacle : obstacles) {
        obstacle->render(renderer);
    }
}
void Boss::InPlayerTurn(){
    // Create 4 obstacles evenly spaced along the Y-axis
    int spacing = 10;
    for (int i = 1; i <= 4; ++i) {
        HorizontalObstacle* ob = new HorizontalObstacle(rand() % GameConfig::SCREEN_WIDTH, 80 + i*spacing, 5);
        obstacles.push_back(ob);
        ob->index = 4 - i;
    }
}
void Boss::InBossTurn(){
    wave.clearProjectiles();
    float healthRatio = health / float(maxHealth);
    float factor = max(healthRatio + 0.2f, 0.2f);
    wave = Wave(GameConfig::SCREEN_WIDTH*factor, GameConfig::SCREEN_HEIGHT*factor);
}
void Boss::GetDamage(int index){
    health -= index * 5;
    if (health == 0){
        GameManager::getInstance()->Win();
    }
}
#include "Wave.h"
#include <iostream>
using namespace std;

Wave::Wave(int screenWidth, int screenHeight) 
    : screenWidth(GameConfig::SCREEN_WIDTH), screenHeight(screenHeight) {}
void Wave::spawnProjectile() {
    int randDir = rand() % 4;
    Direction dir = static_cast<Direction>(randDir);
    float speed = rand() % (GameConfig::WAVE) + 3;

    int startX, startY;
    switch(dir){
        case Direction::LEFT:
            startX = 0;
            startY = screenHeight / 2;
            break;
        case Direction::RIGHT:
            startX = screenWidth;
            startY = screenHeight / 2;
            break;
        case Direction::UP:
            startX = screenWidth / 2;
            startY = 0;
            break;
        case Direction::DOWN:
            startX = screenWidth / 2;
            startY = screenHeight;
        default:
            break;
    }

    Projectile projectile = Projectile(startX, startY, dir, speed);
    projectiles.push_back(projectile);
    cout << projectiles.size() << ' ';
}
void Wave::update(){
    ++frameCount;
    // cout << "frameCount: " << frameCount << ' ';
    if (frameCount >= 60 
    && projectiles.size() <= 1){
        frameCount = 0;
        cout << "Spawn\n";
        spawnProjectile();
    }
}
void Wave::updateProjectiles() {
    for (auto it = projectiles.begin(); it != projectiles.end(); ) {
        it->update();
        if (it->isAlive == false) {
            it = projectiles.erase(it);
        }
        else{
            ++it;
        }
    }
    renderProjectiles();
}

void Wave::renderProjectiles() {
    for (auto& proj : projectiles)
    {
        proj.render(GameConfig::renderer);
    }
}

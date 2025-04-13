#include "Wave.h"
#include "Player.h"
#include "GameManager.h"
#include <iostream>
using namespace std;

Wave::Wave(){
    width = GameConfig::SCREEN_WIDTH;
    height = GameConfig::SCREEN_HEIGHT;
}
Wave::Wave(int width, int height) : width(width), height(height){

}
void Wave::spawnProjectile() {
    int randDir = rand() % 4;
    Direction dir = static_cast<Direction>(randDir);
    float speed = rand() % (1) + 3;

    int startX, startY;
    switch(dir){
        case Direction::LEFT:
            startX = 0;
            startY = Player::getInstance()->gameObject.position.y;
            break;
        case Direction::RIGHT:
            startX = width;
            startY = Player::getInstance()->gameObject.position.y;
            break;
        case Direction::UP:
            startX = Player::getInstance()->gameObject.position.x;
            startY = 0;
            break;
        case Direction::DOWN:
            startX = Player::getInstance()->gameObject.position.x;
            startY = height;
        default:
            break;
    }
    int type = rand() % 6;
    Projectile* projectile;
    if (type <= 4){
        projectile = new EnemyProjectile(startX, startY, dir, speed);
    }
    else{
        projectile = new BuffProjectile(startX, startY, dir, speed);
    }
    projectiles.push_back(projectile);
    cout << projectiles.size() << '\n';
}

void Wave::update(){
    ++frameCount;

    if (frameCount >= 60){
        frameCount = 0;
        cout << "Spawn\n";
        spawnProjectile();
    }
    updateProjectiles();
    renderBoundaries();
}

void Wave::updateProjectiles() {
    for (auto it = projectiles.begin(); it != projectiles.end(); ) {
        (*it)->update();  // Dereference pointer

        if (!(*it)->isAlive) {  // Check isAlive
            cout << "Projectile destroyed\n";
            delete *it;         // Free memory
            it = projectiles.erase(it);  // Erase from vector
        } else {
            ++it;
        }
    }
    renderProjectiles();
}

void Wave::renderProjectiles() {
    for (auto& proj : projectiles)
    {
        proj->render(GameConfig::renderer);
    }
}

void Wave::renderBoundaries() {
    // Centered main rectangle
    SDL_Rect boundary = {
        (GameConfig::SCREEN_WIDTH - width) / 2,
        (GameConfig::SCREEN_HEIGHT - height) / 2,
        width,
        height
    };

    SDL_Renderer* renderer = GameConfig::renderer;
    // Draw 4 thick white borders (top, bottom, left, right)
    const int thickness = 5;
    //Set white color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // Top border
    SDL_Rect top = { boundary.x, boundary.y, boundary.w, thickness };
    SDL_RenderFillRect(renderer, &top);
    // Bottom border
    SDL_Rect bottom = { boundary.x, boundary.y + boundary.h - thickness, boundary.w, thickness };
    SDL_RenderFillRect(renderer, &bottom);
    // Left border
    SDL_Rect left = { boundary.x, boundary.y, thickness, boundary.h };
    SDL_RenderFillRect(renderer, &left);
    // Right border
    SDL_Rect right = { boundary.x + boundary.w - thickness, boundary.y, thickness, boundary.h };
    SDL_RenderFillRect(renderer, &right);
}

void Wave::clearProjectiles(){
    projectiles.clear();
}

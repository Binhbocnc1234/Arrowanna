#include "Player.h"
#include "Ultilities.h"
#include <bits/stdc++.h>
using namespace std;

Player* Player::instance = nullptr;

Player* Player::getInstance(){
    return instance;
}
Player::Player(int x, int y, int health) : health(health), 
    shieldDir(Direction::NONE), gameObject(x, y, 50, 50), shieldObject(0, 0, 0, 0){
    gameObject.color = Color(0, 0, 255, 255);
    shieldObject.color = Color(255, 255, 0, 255);
    if (instance == nullptr){
        instance = this;
    }
}

void Player::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_w: shieldDir = Direction::UP; break;
            case SDLK_s: shieldDir = Direction::DOWN; break;
            case SDLK_a: shieldDir = Direction::LEFT; break;
            case SDLK_d: shieldDir = Direction::RIGHT; break;
                
        }
    }
}

void Player::update() {
    // Vẽ người chơi (màu xanh)
    gameObject.RectRender();
    Vector p = gameObject.position;
    switch (shieldDir) {
        case Direction::UP: shieldObject.SetAttribute(p.x, p.y - 40, 50, 10); break;
        case Direction::DOWN: shieldObject.SetAttribute(p.x, p.y + 40, 50, 10); break;
        case Direction::LEFT: shieldObject.SetAttribute(p.x - 40, p.y, 10, 50); break;
        case Direction::RIGHT: shieldObject.SetAttribute(p.x + 40, p.y, 10, 50); break;
        default: return;
    }
    shieldObject.RectRender();
}

void Player::takeDamage(int projectileDir) {
    if (static_cast<int>(shieldDir) != projectileDir) {
        health--;
        std::cout << "Hit! Health: " << health << std::endl;
        if (health <= 0) {
            std::cout << "Game Over!" << std::endl;
        }
    }
    else {
        std::cout << "Blocked!" << std::endl;
    }
}

bool Player::isAlive() const {
    return health > 0;
}

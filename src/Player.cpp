#include "Player.h"
#include "Ultilities.h"
#include "TextureLoader.h";
#include <bits/stdc++.h>
using namespace std;

Player* Player::instance = nullptr;

Player* Player::getInstance(){
    return instance;
}

Player::Player(int x, int y, int health) 
    : health(health), 
      shieldDir(Direction::UP), oldShieldDir(Direction::UP),
      gameObject(x, y, 50, 50), 
      shieldObject(x, y, 50, 10), oldShieldObject(x, y, 50, 10) {
    
    gameObject.color = Color(0, 0, 255, 255);  // Player color
    shieldObject.color = Color(255, 255, 0, 255); // Shield color
    oldShieldObject.color = Color(255, 255, 0, 255); // Old shield for fading effect

    gameObject.textureNameList = {"player", "player_hurt"};
    gameObject.mainTextureName = "player";
    if (instance == nullptr){
        instance = this;
    } else {
        std::cerr << "Two or more instances of Player!" << std::endl;
    }
}

void Player::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        if (!isShieldTransitioning) {  
            switch (e.key.keysym.sym) {
                case SDLK_w: shieldDir = Direction::UP; break;
                case SDLK_s: shieldDir = Direction::DOWN; break;
                case SDLK_a: shieldDir = Direction::LEFT; break;
                case SDLK_d: shieldDir = Direction::RIGHT; break;
                default:
                    return;
            }

            if (shieldDir != oldShieldDir) {
                cout << "Player change shield direction," << " from " << (int)oldShieldDir << " to " << int(shieldDir) << endl;
                isShieldTransitioning = true;
                shieldTransitionStart = SDL_GetTicks();  
                
            }
            else{
                oldShieldDir = shieldDir; 
            }
        }
    }
}

void Player::update() {
    Uint32 currentTime = SDL_GetTicks();
    float progress = 1.0f;

    if (isShieldTransitioning) {
        Uint32 elapsed = currentTime - shieldTransitionStart;
        progress = min(1.0, elapsed / double(GameConfig::SHIELD_ROTATION_DELAY));  // 200ms fade effect

        if (elapsed >= GameConfig::SHIELD_ROTATION_DELAY) {  // Transition finished
            isShieldTransitioning = false;
            oldShieldDir = shieldDir;  // Update old direction
        }
    }

    // Update shield positions
    Vector newShieldPos = gameObject.position;
    Vector oldShieldPos = gameObject.position;

    int shieldWidth = 50, shieldHeight = 10;
    int oldWidth = 50, oldHeight = 10;

    // Old shield position (fade-out)
    switch (oldShieldDir) {
        case Direction::UP: oldShieldPos.y -= 40; break;
        case Direction::DOWN: oldShieldPos.y += 40; break;
        case Direction::LEFT: oldShieldPos.x -= 40; oldWidth = 10; oldHeight = 50; break;
        case Direction::RIGHT: oldShieldPos.x += 40; oldWidth = 10; oldHeight = 50; break;
        default: break;
    }

    // New shield position (fade-in)
    switch (shieldDir) {
        case Direction::UP: newShieldPos.y -= 40; break;
        case Direction::DOWN: newShieldPos.y += 40; break;
        case Direction::LEFT: newShieldPos.x -= 40; shieldWidth = 10; shieldHeight = 50; break;
        case Direction::RIGHT: newShieldPos.x += 40; shieldWidth = 10; shieldHeight = 50; break;
        default: break;
    }

    // Update shield object attributes
    shieldObject.SetAttribute(newShieldPos.x, newShieldPos.y, shieldWidth, shieldHeight);
    oldShieldObject.SetAttribute(oldShieldPos.x, oldShieldPos.y, oldWidth, oldHeight);
    
    SDL_SetRenderDrawBlendMode(GameConfig::renderer, SDL_BLENDMODE_BLEND);
    // Render player
    gameObject.TextureRender();
    //Render shield
    
    if (isShieldTransitioning) {
        oldShieldObject.color.a = (1.0f - progress) * 255;  // Decrease opacity
        oldShieldObject.RectRender();
    }
    shieldObject.color.a = progress * 255;  // Increase opacity
    shieldObject.RectRender();
}

void Player::takeDamage(int projectileDir) {
    if (static_cast<int>(shieldDir) != projectileDir) {
        health--;
        std::cout << "Hit! Health: " << health << std::endl;
        if (health <= 0) {
            std::cout << "Game Over!" << std::endl;
        }
    } else {
        std::cout << "Blocked!" << std::endl;
    }
}

bool Player::isAlive() const {
    return health > 0;
}

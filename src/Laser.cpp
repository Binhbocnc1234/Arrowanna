#include "Laser.h"
#include "Player.h"
#include "TextureLoader.h"
#include <algorithm>

Laser::Laser(Direction lane, Uint32 chargeTime, Uint32 fireTime, Uint32 collapseTime)
    : lane(lane), chargeTime(chargeTime), fireTime(fireTime), collapseTime(collapseTime)
{
    maxWidth = 80.0f;
    color = {255, 240, 240, 220};
    state = LaserState::Inactive;
    laserTexture = TextureLoader::loadTexture("Dread-eye");
    damageDealt = false;
}

void Laser::activate(Direction lane) {
    this->lane = lane;
    state = LaserState::Charging;
    startTime = SDL_GetTicks();
    width = 0.0f;
    damageDealt = false;
}

void Laser::deactivate() {
    state = LaserState::Inactive;
}

bool Laser::isActive() const {
    return state != LaserState::Inactive;
}

void Laser::update() {
    if (state == LaserState::Inactive) return;
    Uint32 now = SDL_GetTicks();
    Uint32 elapsed = now - startTime;

    if (state == LaserState::Charging) {
        float t = std::min(1.0f, elapsed / float(chargeTime));
        width = 10.0f + (maxWidth - 10.0f) * t;
        if (elapsed >= chargeTime) {
            state = LaserState::Firing;
            startTime = now;
            damageDealt = false;
        }
    } else if (state == LaserState::Firing) {
        width = maxWidth;
        if (elapsed >= fireTime) {
            state = LaserState::Collapsing;
            startTime = now;
        }
    } else if (state == LaserState::Collapsing) {
        float t = std::min(1.0f, elapsed / float(collapseTime));
        width = maxWidth * (1.0f - t);
        if (width < 2.0f) width = 0.0f;
        if (elapsed >= collapseTime) {
            state = LaserState::Inactive;
        }
    }
}

void Laser::render(SDL_Renderer* renderer) {
    if (state == LaserState::Inactive || width <= 0.0f) return;

    Vector playerPos = Player::getInstance()->gameObject.position;
    int x = static_cast<int>(playerPos.x), y = static_cast<int>(playerPos.y);
    int w = static_cast<int>(width), h = static_cast<int>(width);
    int laserLength = 0;
    SDL_Rect laserRect;
    switch (lane) {
        case Direction::UP:
            laserLength = y - 40;
            laserRect = {x - w/2, 40, w, laserLength};
            break;
        case Direction::DOWN:
            laserLength = GameConfig::SCREEN_HEIGHT - y - 40;
            laserRect = {x - w/2, y + 40, w, laserLength};
            break;
        case Direction::LEFT:
            laserLength = x - 40;
            laserRect = {40, y - h/2, laserLength, h};
            break;
        case Direction::RIGHT:
            laserLength = GameConfig::SCREEN_WIDTH - x - 40;
            laserRect = {x + 40, y - h/2, laserLength, h};
            break;
        default:
            return;
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &laserRect);

    SDL_Rect eyeRect = {0, 0, 64, 64};
    switch (lane) {
        case Direction::UP:    eyeRect.x = x - 32; eyeRect.y = 40 - 32; break;
        case Direction::DOWN:  eyeRect.x = x - 32; eyeRect.y = GameConfig::SCREEN_HEIGHT - 40 - 32; break;
        case Direction::LEFT:  eyeRect.x = 40 - 32; eyeRect.y = y - 32; break;
        case Direction::RIGHT: eyeRect.x = GameConfig::SCREEN_WIDTH - 40 - 32; eyeRect.y = y - 32; break;
        default: break;
    }
    if (laserTexture)
        SDL_RenderCopy(renderer, laserTexture, nullptr, &eyeRect);
}

bool Laser::checkBlock() {
    if (state != LaserState::Firing) return false;
    Player* player = Player::getInstance();
    return (player->shieldDir == lane);
}

bool Laser::checkHit() {
    if (state != LaserState::Firing) return false;
    Player* player = Player::getInstance();
    return (player->shieldDir != lane);
}

bool Laser::shouldDealDamage() {
    // Only return true on the first call in Firing state
    if (state == LaserState::Firing && !damageDealt) {
        damageDealt = true;
        return true;
    }
    return false;
}

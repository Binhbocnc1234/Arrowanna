#include "Boss.h"
#include "Wave.h"
#include "GameManager.h"
#include "Ultilities.h"
#include "Laser.h"
#include "DamageObject.h"
#include <SDL2/SDL_ttf.h>

Boss *Boss::instance = nullptr;
Boss* Boss::getInstance(){
    return instance;
}

// Add swing effect variables at file scope
static int swingOffset = 0;
static int swingDirection = 1;
static Uint32 swingStartTime = 0;
static const int swingDuration = 400; // ms
static const int swingAmplitude = 18; // px

// Add laser spawn logic variables at file scope
static Uint32 lastLaserTime = 0;
static const Uint32 laserInterval = 6000; // 6 seconds in ms

Boss::Boss(int x, int y, int maxHealth) : gameObject(x, y, 80, 80), health(maxHealth), maxHealth(maxHealth), 
currentSpriteIndex(0), lastSpriteChangeTime(0), wave(GameConfig::SCREEN_WIDTH, GameConfig::SCREEN_HEIGHT), laser(nullptr) {
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
    // Swing effect update
    if (swingStartTime > 0) {
        Uint32 now = SDL_GetTicks();
        Uint32 elapsed = now - swingStartTime;
        if (elapsed < swingDuration) {
            // Simple sinusoidal swing
            float t = elapsed / float(swingDuration);
            swingOffset = int(sin(t * 6.28f * 2) * swingAmplitude * (1.0f - t)); // 2 cycles, fade out
        } else {
            swingOffset = 0;
            swingStartTime = 0;
        }
    } else {
        swingOffset = 0;
    }

    // Update and render damage objects
    for (auto it = damageObjects.begin(); it != damageObjects.end(); ) {
        (*it)->update();
        (*it)->render(GameConfig::renderer);
        if (!(*it)->isAlive()) {
            delete *it;
            it = damageObjects.erase(it);
        } else {
            ++it;
        }
    }

    renderBoss(GameConfig::renderer);

    // Laser attack logic: only during BossTurn and health <= half
    if (GameManager::getInstance()->gameState == GameState::BossTurn && health <= maxHealth / 2) {
        Uint32 now = SDL_GetTicks();
        // Only spawn/activate laser every 6 seconds
        if ((!laser || !laser->isActive()) && (now - lastLaserTime >= laserInterval)) {
            tryActivateLaser();
            lastLaserTime = now;
        }
        if (laser && laser->isActive()) {
            // Set laser width to match shield width (50)
            laser->setMaxWidth(50);

            // Change color based on state
            if (laser->getState() == LaserState::Firing) {
                laser->setColor({200, 40, 40, 180}); // semi-red, more visible
            } else {
                laser->setColor({255, 240, 240, 90}); // light red
            }

            laser->update();
            laser->render(GameConfig::renderer);

            // Only deal damage once per Firing state, using Laser's logic
            if (laser->getState() == LaserState::Firing) {
                if (laser->checkBlock()) {
                    Player::getInstance()->PlayBlockSound();
                } else if (laser->checkHit() && laser->shouldDealDamage()) {
                    Player::getInstance()->health -= 4;
                    if (Player::getInstance()->health <= 0) {
                        GameManager::getInstance()->Lose();
                    }
                }
            }
        }
    }

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
    // Apply swing effect to boss position
    int oldX = gameObject.position.x;
    gameObject.position.x += swingOffset;
    gameObject.TextureRender(sprites[currentSpriteIndex]);
    gameObject.position.x = oldX;
    // Render all obstacles
    for (auto& obstacle : obstacles) {
        obstacle->render(renderer);
    }
}

void Boss::tryActivateLaser() {
    // Only activate/reactivate if not already active
    if (!laser) {
        Direction lane = static_cast<Direction>(rand() % 4);
        laser = new Laser(lane);
        laser->activate(lane);
    } else if (!laser->isActive()) {
        Direction lane = static_cast<Direction>(rand() % 4);
        laser->activate(lane);
    }
}

void Boss::InPlayerTurn(){
    // Create 4 obstacles evenly spaced along the Y-axis, 20px closer to Player
    int spacing = 10;
    int yOffset = 20; // Move closer to Player
    for (int i = 1; i <= 4; ++i) {
        HorizontalObstacle* ob = new HorizontalObstacle(rand() % GameConfig::SCREEN_WIDTH, 80 + i*spacing + yOffset, 5);
        obstacles.push_back(ob);
        ob->index = 4 - i;
    }
}
void Boss::InBossTurn(){
    // Clear and delete all obstacles
    for (auto ob : obstacles) {
        delete ob;
    }
    obstacles.clear();

    wave.clearProjectiles();

    // Wave area is proportional to boss health, with a minimum area
    float healthRatio = std::max(health / float(maxHealth), 0.0f);
    float minAreaRatio = 0.5f; // Minimum 9% of screen area (0.3*0.3)
    float areaRatio = std::max(healthRatio, minAreaRatio);

    int screenW = GameConfig::SCREEN_WIDTH;
    int screenH = GameConfig::SCREEN_HEIGHT;
    float aspect = float(screenW) / float(screenH);

    float waveArea = screenW * screenH * areaRatio;
    int waveWidth = static_cast<int>(sqrt(waveArea * aspect));
    int waveHeight = static_cast<int>(sqrt(waveArea / aspect));

    std::cout << "Wave area ratio: " << areaRatio << ", width: " << waveWidth << ", height: " << waveHeight << '\n';
    wave = Wave(waveWidth, waveHeight);
}
void Boss::TakeDamage(int index){
    health -= index * 5;
    // Start swing effect
    swingStartTime = SDL_GetTicks();
    // Create DamageObject at boss position
    static TTF_Font* font = nullptr;
    if (!font) font = TTF_OpenFont("Assets/RadiantKingdom-mL5eV.ttf", 36);
    Vector pos = gameObject.position;
    damageObjects.push_back(new DamageObject(pos, index * 5, GameConfig::renderer, font));
    if (health == 0){
        GameManager::getInstance()->Win();
    }
}

int Boss::GetHealth() const {
    return health;
}
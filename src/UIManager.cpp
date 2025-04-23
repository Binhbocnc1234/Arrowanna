#include "UIManager.h"
#include "Ultilities.h"
#include "Player.h"
#include "Boss.h"
#include <iostream>

// Thêm biến static để lưu trạng thái thanh máu Boss
static int lastBossHealth = 0;
static float displayedBossHealth = 0.0f;
static Uint32 bossHealthBarShowTime = 0;
static const Uint32 bossHealthBarDuration = 2000; // ms

UIManager::UIManager(SDL_Renderer* renderer) : renderer(renderer) {
    if (TTF_Init() == -1) {
        std::cerr << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
    }
    font = TTF_OpenFont("Assets/RadiantKingdom-mL5eV.ttf", 24);  // ✅ Ensure this font exists
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
    textColor = {255, 255, 255, 255}; // White color
}

UIManager::~UIManager() {
    TTF_CloseFont(font);
    TTF_Quit();
}

void UIManager::render(int health, int score, int goldEnergy, int maxGoldEnergy) {
    renderText("Health: " + std::to_string(health), 10, 10, 1.0f, Alignment::Left);
    renderText("Score: " + std::to_string(score), 10, 40, 1.0f, Alignment::Left);
    renderGoldEnergyBar(10, 70, goldEnergy, maxGoldEnergy);
    RenderBossHealthBar();
}

void UIManager::renderGameOver() {
    renderText("You raised your shield too late... and paid the price.", GameConfig::SCREEN_WIDTH / 2, GameConfig::SCREEN_HEIGHT / 2, 2);
}

void UIManager::renderWin(){
    renderText("Even the Boss fall when faced with unwavering resolve.", GameConfig::SCREEN_WIDTH / 2, GameConfig::SCREEN_HEIGHT / 2, 2);
}

void UIManager::renderText(const std::string& text, int x, int y, float scale, Alignment align) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (!textSurface) return;

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    int w = textSurface->w * scale;
    int h = textSurface->h * scale;
    SDL_Rect renderQuad = {x - w/2, y - h/2, w, h};
    if (align == Alignment::Left){
        renderQuad.x = x;
        renderQuad.y = y;
    }

    SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void UIManager::renderGoldEnergyBar(int x, int y, int goldEnergy, int maxEnergy) {
    const int blockWidth = 20;
    const int blockHeight = 20;
    const int spacing = 5;

    for (int i = 0; i < maxEnergy; ++i) {
        SDL_Rect block = {x + i * (blockWidth + spacing), y, blockWidth, blockHeight};

        if (i < goldEnergy) {
            SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255); // Gold
        } else {
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Grey
        }
        SDL_RenderFillRect(renderer, &block);
    }
}

void UIManager::RenderBossHealthBar() {
    Boss* boss = Boss::getInstance();
    if (!boss) return;

    int maxHealth = boss->maxHealth;
    int currentHealth = boss->GetHealth();

    // Chỉ hiển thị khi Boss mất máu và trong 2s sau khi mất máu
    Uint32 now = SDL_GetTicks();
    if (currentHealth < maxHealth) {
        if (currentHealth != lastBossHealth) {
            bossHealthBarShowTime = now;
            lastBossHealth = currentHealth;
        }
    }
    // Nếu chưa từng mất máu hoặc đã hết thời gian hiển thị thì không render
    if (currentHealth == maxHealth || now - bossHealthBarShowTime > bossHealthBarDuration)
        return;

    // Thanh máu giảm từ từ (lerp)
    if (displayedBossHealth > currentHealth) {
        float lerpSpeed = 0.08f; // càng nhỏ càng mượt
        displayedBossHealth = displayedBossHealth * (1 - lerpSpeed) + currentHealth * lerpSpeed;
        if (displayedBossHealth < currentHealth) displayedBossHealth = currentHealth;
    } else {
        displayedBossHealth = currentHealth;
    }

    // Bar dimensions and position
    int barWidth = 300;
    int barHeight = 12;
    int x = (GameConfig::SCREEN_WIDTH - barWidth) / 2;
    int y = 100;

    // Background (gray)
    SDL_Rect bgRect = { x, y, barWidth, barHeight };
    SDL_SetRenderDrawColor(GameConfig::renderer, 80, 80, 80, 255);
    SDL_RenderFillRect(GameConfig::renderer, &bgRect);

    // Health (red)
    int healthWidth = static_cast<int>((displayedBossHealth / (float)maxHealth) * barWidth);
    SDL_Rect healthRect = { x, y, healthWidth, barHeight };
    SDL_SetRenderDrawColor(GameConfig::renderer, 200, 40, 40, 255);
    SDL_RenderFillRect(GameConfig::renderer, &healthRect);

    // Optional: border
    SDL_SetRenderDrawColor(GameConfig::renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(GameConfig::renderer, &bgRect);
}

#include "UIManager.h"
#include "Ultilities.h"
#include "Player.h"
#include <iostream>

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
}
void UIManager::renderGameOver() {
    renderText("GAME OVER", GameConfig::SCREEN_WIDTH / 2, GameConfig::SCREEN_HEIGHT / 2, 3);
}
void UIManager::renderWin(){
    renderText("GAME OVER", GameConfig::SCREEN_WIDTH / 2, GameConfig::SCREEN_HEIGHT / 2, 3);
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

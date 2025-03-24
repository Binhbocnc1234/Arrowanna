#include "UIManager.h"
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

void UIManager::render(int health, int score) {
    renderText("Health: " + std::to_string(health), 10, 10);
    renderText("Score: " + std::to_string(score), 10, 40);
}

void UIManager::renderText(const std::string& text, int x, int y) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (!textSurface) return;

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};

    SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);
    
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

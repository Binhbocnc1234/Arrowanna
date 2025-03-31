#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class UIManager {
public:
    UIManager(SDL_Renderer* renderer);
    ~UIManager();
    
    void render(int health, int score);
    void renderGameOver();

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Color textColor;

    void renderText(const std::string& text, int x, int y);
};

#endif

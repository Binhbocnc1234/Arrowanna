#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

enum Alignment
{
    Center,
    Left,
    Right,
};
class UIManager {
public:
    UIManager(SDL_Renderer* renderer);
    ~UIManager();
    
    void render(int health, int score, int goldEnergy, int maxGoldEnergy);
    void renderGameOver();
    void renderWin();
    void renderGoldEnergyBar(int x, int y, int goldEnergy, int maxEnergy);

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Color textColor;

    void renderText(const std::string& text, int x, int y, float scale = 1.0f, Alignment align = Alignment::Center);
};

#endif

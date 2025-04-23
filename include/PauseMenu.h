#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class PauseButton {
public:
    PauseButton(int x, int y, int size);
    void render(SDL_Renderer* renderer);
    bool isHovered(int mx, int my) const;
    bool isClicked(int mx, int my, bool mouseDown) const;
    SDL_Rect rect;
    bool hovered = false;
};

class PauseMenu {
public:
    PauseMenu(SDL_Renderer* renderer, TTF_Font* font);
    // Returns: 0 = continue, 1 = quit, -1 = nothing
    int updateAndRender(int& musicVolume);
    bool isActive = false;
private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Rect menuRect;
    SDL_Rect sliderRect;
    int sliderPos = 0;
    int sliderMin = 0, sliderMax = 100;
    bool draggingSlider = false;
    SDL_Rect continueBtn, quitBtn;
};

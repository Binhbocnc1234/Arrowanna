#include "PauseMenu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

// --- PauseButton ---
PauseButton::PauseButton(int x, int y, int size) : rect{x, y, size, size} {}

void PauseButton::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, hovered ? 180 : 80, 80, 180, 220);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
    // Draw pause icon (two vertical bars)
    int barW = rect.w / 4;
    int gap = rect.w / 4;
    SDL_Rect bar1 = {rect.x + gap/2, rect.y + rect.h/6, barW, rect.h - rect.h/3};
    SDL_Rect bar2 = {rect.x + gap/2 + barW + gap/2, rect.y + rect.h/6, barW, rect.h - rect.h/3};
    SDL_RenderFillRect(renderer, &bar1);
    SDL_RenderFillRect(renderer, &bar2);
}

bool PauseButton::isHovered(int mx, int my) const {
    return mx >= rect.x && mx <= rect.x+rect.w && my >= rect.y && my <= rect.y+rect.h;
}
bool PauseButton::isClicked(int mx, int my, bool mouseDown) const {
    return isHovered(mx, my) && mouseDown;
}

// --- PauseMenu ---
PauseMenu::PauseMenu(SDL_Renderer* renderer, TTF_Font* font)
    : renderer(renderer), font(font)
{
    menuRect = {220, 120, 360, 320};
    sliderRect = {menuRect.x + 60, menuRect.y + 120, 240, 16};
    continueBtn = {menuRect.x + 60, menuRect.y + 200, 100, 40};
    quitBtn = {menuRect.x + 200, menuRect.y + 200, 100, 40};
}

int PauseMenu::updateAndRender(int& musicVolume) {
    int mx, my;
    Uint32 mouseState = SDL_GetMouseState(&mx, &my);
    bool mouseDown = mouseState & SDL_BUTTON(SDL_BUTTON_LEFT);

    // Draw semi-transparent background
    SDL_SetRenderDrawColor(renderer, 20, 20, 40, 200);
    SDL_Rect bg = {0, 0, 800, 600};
    SDL_RenderFillRect(renderer, &bg);

    // Draw menu box
    SDL_SetRenderDrawColor(renderer, 40, 40, 80, 240);
    SDL_RenderFillRect(renderer, &menuRect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &menuRect);

    // Draw title
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surf = TTF_RenderText_Blended(font, "PAUSED", color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    int tw = surf->w, th = surf->h;
    SDL_Rect dst = {menuRect.x + (menuRect.w-tw)/2, menuRect.y + 30, tw, th};
    SDL_RenderCopy(renderer, tex, nullptr, &dst);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);

    // Draw volume slider label
    surf = TTF_RenderText_Blended(font, "Music Volume", color);
    tex = SDL_CreateTextureFromSurface(renderer, surf);
    tw = surf->w; th = surf->h;
    SDL_Rect labelRect = {sliderRect.x, sliderRect.y - 30, tw, th};
    SDL_RenderCopy(renderer, tex, nullptr, &labelRect);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);

    // Draw slider bar
    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
    SDL_RenderFillRect(renderer, &sliderRect);
    // Draw slider knob
    int knobX = sliderRect.x + (musicVolume * (sliderRect.w-20)) / 128;
    SDL_Rect knob = {knobX, sliderRect.y - 6, 20, sliderRect.h + 12};
    SDL_SetRenderDrawColor(renderer, 200, 200, 255, 255);
    SDL_RenderFillRect(renderer, &knob);

    // Handle slider drag
    if (mouseDown && mx >= sliderRect.x && mx <= sliderRect.x+sliderRect.w && my >= sliderRect.y-6 && my <= sliderRect.y+sliderRect.h+6) {
        int rel = mx - sliderRect.x;
        if (rel < 0) rel = 0;
        if (rel > sliderRect.w-1) rel = sliderRect.w-1;
        musicVolume = (rel * 128) / (sliderRect.w-20);
        if (musicVolume < 0) musicVolume = 0;
        if (musicVolume > 128) musicVolume = 128;
    }

    // Draw Continue button
    SDL_SetRenderDrawColor(renderer, 80, 180, 80, 255);
    SDL_RenderFillRect(renderer, &continueBtn);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &continueBtn);
    surf = TTF_RenderText_Blended(font, "Continue", color);
    tex = SDL_CreateTextureFromSurface(renderer, surf);
    tw = surf->w; th = surf->h;
    dst = {continueBtn.x + (continueBtn.w-tw)/2, continueBtn.y + (continueBtn.h-th)/2, tw, th};
    SDL_RenderCopy(renderer, tex, nullptr, &dst);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);

    // Draw Quit button
    SDL_SetRenderDrawColor(renderer, 180, 80, 80, 255);
    SDL_RenderFillRect(renderer, &quitBtn);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &quitBtn);
    surf = TTF_RenderText_Blended(font, "Quit", color);
    tex = SDL_CreateTextureFromSurface(renderer, surf);
    tw = surf->w; th = surf->h;
    dst = {quitBtn.x + (quitBtn.w-tw)/2, quitBtn.y + (quitBtn.h-th)/2, tw, th};
    SDL_RenderCopy(renderer, tex, nullptr, &dst);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);

    // Handle button clicks
    if (mouseDown) {
        if (mx >= continueBtn.x && mx <= continueBtn.x+continueBtn.w && my >= continueBtn.y && my <= continueBtn.y+continueBtn.h)
            return 0; // Continue
        if (mx >= quitBtn.x && mx <= quitBtn.x+quitBtn.w && my >= quitBtn.y && my <= quitBtn.y+quitBtn.h)
            return 1; // Quit
    }
    return -1;
}

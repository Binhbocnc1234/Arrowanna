#include "Lobby.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cstdlib>
#include <ctime>

// -------- Button --------
Button::Button(int x, int y, int w, int h, const std::string& text, TTF_Font* font)
    : rect{x, y, w, h}, text(text), font(font) {}

void Button::render(SDL_Renderer* renderer) {
    // Draw button background
    SDL_SetRenderDrawColor(renderer, hovered ? 80 : 30, 30, 80, 220);
    SDL_RenderFillRect(renderer, &rect);
    // Draw border
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
    // Draw text
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    int tw = surf->w, th = surf->h;
    SDL_Rect dst = {rect.x + (rect.w-tw)/2, rect.y + (rect.h-th)/2, tw, th};
    SDL_RenderCopy(renderer, tex, nullptr, &dst);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);
}

bool Button::isHovered(int mx, int my) const {
    return mx >= rect.x && mx <= rect.x+rect.w && my >= rect.y && my <= rect.y+rect.h;
}
bool Button::isClicked(int mx, int my, bool mouseDown) const {
    return isHovered(mx, my) && mouseDown;
}

// -------- GalaxyBackground --------
GalaxyBackground::GalaxyBackground(int width, int height, int numStars)
    : width(width), height(height)
{
    srand((unsigned)time(nullptr));
    for (int i = 0; i < numStars; ++i) {
        Star s;
        s.x = rand() % width;
        s.y = rand() % height;
        s.size = 1.0f + (rand() % 100) / 60.0f;
        s.speed = 0.2f + (rand() % 100) / 200.0f;
        s.alpha = 120 + rand() % 120;
        stars.push_back(s);
    }
}
void GalaxyBackground::update() {
    for (auto& s : stars) {
        s.y += s.speed;
        if (s.y > height) {
            s.y = 0;
            s.x = rand() % width;
        }
    }
}
void GalaxyBackground::render(SDL_Renderer* renderer) {
    for (auto& s : stars) {
        SDL_SetRenderDrawColor(renderer, 200, 200, 255, s.alpha);
        SDL_Rect r = {int(s.x), int(s.y), int(s.size), int(s.size)};
        SDL_RenderFillRect(renderer, &r);
    }
}

// -------- Lobby --------
Lobby::Lobby(SDL_Renderer* renderer)
    : renderer(renderer)
{
    TTF_Init();
    titleFont = TTF_OpenFont("Assets/RadiantKingdom-mL5eV.ttf", 64);
    buttonFont = TTF_OpenFont("Assets/RadiantKingdom-mL5eV.ttf", 32);
    galaxy = new GalaxyBackground(800, 600);
    startButton = new Button(300, 400, 200, 60, "START", buttonFont);
}
Lobby::~Lobby() {
    delete galaxy;
    delete startButton;
    if (titleFont) TTF_CloseFont(titleFont);
    if (buttonFont) TTF_CloseFont(buttonFont);
    TTF_Quit();
}

bool Lobby::updateAndRender() {
    int mx, my;
    Uint32 mouseState = SDL_GetMouseState(&mx, &my);
    bool mouseDown = mouseState & SDL_BUTTON(SDL_BUTTON_LEFT);

    galaxy->update();

    // Draw background
    SDL_SetRenderDrawColor(renderer, 10, 10, 30, 255);
    SDL_RenderClear(renderer);
    galaxy->render(renderer);

    // Draw title
    std::string title = "ARROWANNA";
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surf = TTF_RenderText_Blended(titleFont, title.c_str(), color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    int tw = surf->w, th = surf->h;
    SDL_Rect dst = {400 - tw/2, 120, tw, th};
    SDL_RenderCopy(renderer, tex, nullptr, &dst);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);

    // Draw start button
    startButton->hovered = startButton->isHovered(mx, my);
    startButton->render(renderer);

    SDL_RenderPresent(renderer);

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) exit(0);
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            if (startButton->isHovered(mx, my)) {
                return true;
            }
        }
    }
    return false;
}

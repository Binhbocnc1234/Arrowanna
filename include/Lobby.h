#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>

// Simple Button class
class Button {
public:
    Button(int x, int y, int w, int h, const std::string& text, TTF_Font* font);
    void render(SDL_Renderer* renderer);
    bool isHovered(int mx, int my) const;
    bool isClicked(int mx, int my, bool mouseDown) const;
    SDL_Rect rect;
    std::string text;
    TTF_Font* font;
    bool hovered = false;
};

// Galaxy background with many star particles
class GalaxyBackground {
public:
    struct Star {
        float x, y, speed, size;
        Uint8 alpha;
    };
    GalaxyBackground(int width, int height, int numStars = 120);
    void update();
    void render(SDL_Renderer* renderer);
private:
    std::vector<Star> stars;
    int width, height;
};

// Lobby scene
class Lobby {
public:
    Lobby(SDL_Renderer* renderer);
    ~Lobby();
    // Returns true if user pressed Start
    bool updateAndRender();
private:
    SDL_Renderer* renderer;
    TTF_Font* titleFont;
    TTF_Font* buttonFont;
    GalaxyBackground* galaxy;
    Button* startButton;
};

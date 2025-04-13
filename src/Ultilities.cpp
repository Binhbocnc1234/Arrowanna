#include "Ultilities.h"
#include "TextureLoader.h"

SDL_Renderer *GameConfig::renderer = nullptr;
bool GameConfig::running = true;
SDL_Event GameConfig::e = SDL_Event{};

SDL_Point getRectCenter(const SDL_Rect& rect) {
    SDL_Point center;
    center.x = rect.x + rect.w / 2;
    center.y = rect.y + rect.h / 2;
    return center;
}

// SCREEN SHAKE EFFECT
SDL_Renderer* ScreenShakeEffect::renderer = GameConfig::renderer;
SDL_Rect ScreenShakeEffect::camera = {0, 0, GameConfig::SCREEN_WIDTH, GameConfig::SCREEN_HEIGHT}; // Example screen size
bool ScreenShakeEffect::isShaking = false;
Uint32 ScreenShakeEffect::screenShakeStartTime = 0;
void ScreenShakeEffect::StartScreenShake() {
    screenShakeStartTime = SDL_GetTicks();
    // camera = {0, 0, 0, 0};
    isShaking = true;
}

void ScreenShakeEffect::UpdateScreenShake() {
    if (!isShaking) return;

    Uint32 elapsed = SDL_GetTicks() - screenShakeStartTime;
    if (elapsed >= screenShakeDuration) {
        isShaking = false;
        camera.x = 0;
        camera.y = 0;
        return;
    }

    // Apply random offset to camera position
    camera.x = (rand() % (screenShakeIntensity * 2 + 1)) - screenShakeIntensity;
    camera.y = (rand() % (screenShakeIntensity * 2 + 1)) - screenShakeIntensity;
}

// GAMEOBJECT
GameObject::GameObject(int x, int y) {
    position.x = x;
    position.y = y;
}

GameObject::GameObject(int x, int y, int width, int height)
    : position{x, y}, width(width), height(height) {
}

void GameObject::Translate() {
    position.x += direction.x;
    position.y += direction.y;
}

void GameObject::SetAttribute(int x, int y, int width, int height) {
    position = {x, y};
    this->width = width;
    this->height = height;
}

void GameObject::RectRender() {
    SDL_SetRenderDrawColor(GameConfig::renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = GameObject::GetRect();
    SDL_RenderFillRect(GameConfig::renderer, &rect);
}

void GameObject::TextureRender() {
    TextureRender(mainTextureName);
}

void GameObject::TextureRender(const std::string& name) {
    SDL_Rect rect = GameObject::GetRect();
    SDL_RenderCopy(GameConfig::renderer, TextureLoader::loadTexture(name), nullptr, &rect);
}
SDL_Rect GameObject::GetRect(){
    SDL_Rect rect = {int(position.x) - width / 2 + ScreenShakeEffect::camera.x, int(position.y) - height / 2 + ScreenShakeEffect::camera.y, width, height};
    return rect;
}
bool GameObject::IsCollide(Vector p) {
    return (p.x >= position.x - width / 2 && p.x <= position.x + width / 2 &&
            p.y >= position.y - height / 2 && p.y <= position.y + height / 2);
}
bool GameObject::IsCollide(GameObject& other){
    SDL_Rect a = this->GetRect();
    SDL_Rect b = other.GetRect();
    return SDL_HasIntersection(&a, &b) == SDL_TRUE;
}
std::ostream& operator<<(std::ostream& os, const GameObject& obj) {
    os << "GameObject(Position: (" << obj.position.x << ", " << obj.position.y
       << "), Size: [" << obj.width << "x" << obj.height << "])";
    return os;
}
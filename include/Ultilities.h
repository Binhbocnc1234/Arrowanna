#pragma once
#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include "TextureLoader.h"
using namespace std;

enum class Direction { LEFT, RIGHT, UP, DOWN, NONE };

class GameConfig {
public:
    static constexpr int SCREEN_WIDTH = 800;
    static constexpr int SCREEN_HEIGHT = 600;
    static constexpr int FPS = 60;
    static constexpr bool IS_DEBUG_MODE = true, IS_LOSE = false;
    static constexpr int SHIELD_ROTATION_DELAY = 200; //miliseconds
    static int MAX_ENERGY;
    static bool running;
    static SDL_Event e;
    static SDL_Renderer *renderer;
};

template <typename T>
class Singleton {
protected:
    Singleton() {} // Protected constructor to be called only by derived classes
    virtual ~Singleton() {}

public:
    Singleton(const Singleton&) = delete; // Delete copy constructor
    Singleton& operator=(const Singleton&) = delete; // Delete copy assignment operator

    static T& getInstance() {
        static T instance;
        return instance;
    }
};

SDL_Point getRectCenter(const SDL_Rect &rect);

class ScreenShakeEffect{
    public:
        static SDL_Renderer* renderer;
        static SDL_Rect camera;
        static constexpr int screenShakeDuration = 100;
        static constexpr int screenShakeIntensity = 2;
        static bool isShaking;
        static void StartScreenShake();
        static void UpdateScreenShake();
        static Uint32 screenShakeStartTime;
};
    
struct Vector {
    float x = 0, y = 0;

    Vector() : x(0), y(0) {} // Default constructor
    Vector(float x, float y) : x(x), y(y) {} // Parameterized constructor

    // Addition
    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y);
    }

    // Subtraction
    Vector operator-(const Vector& other) const {
        return Vector(x - other.x, y - other.y);
    }

    // Scalar multiplication
    Vector operator*(float scalar) const {
        return Vector(x * scalar, y * scalar);
    }

    // Dot product
    float dot(const Vector& other) const {
        return x * other.x + y * other.y;
    }

    // Get magnitude (length)
    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    // Normalize (unit vector)
    Vector normalize() const {
        float mag = magnitude();
        return (mag > 0) ? Vector(x / mag, y / mag) : Vector(0, 0);
    }
    Vector Lerp(const Vector& end, float t) {
        Vector result;
        result.x = x + (end.x - x) * t;
        result.y = y + (end.y - y) * t;
        return result;
    }
    float GetDistance(const Vector& other) const{
        return sqrt((x-other.x)*(x-other.x) + (y-other.y)*(y-other.y));
    }
};
struct Color{
    int r , g , b , a ;
    Color() : r(0), g(0), b(0), a(255) {};
    Color(int r, int g, int b, int a){
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

struct GameObject {
    Vector position;
    Vector direction;
    Color color;
    std::string mainTextureName;
    std::vector<std::string> textureNameList;
    int width, height;
    int alpha = 255; // Thêm thuộc tính alpha, mặc định 255

    GameObject(int x = 0, int y = 0);
    GameObject(int x, int y, int width, int height);

    void Translate();
    void SetAttribute(int x, int y, int width, int height);
    void RectRender();
    void TextureRender();
    void TextureRender(const std::string& name);
    SDL_Rect GetRect();
    bool IsCollide(Vector p);
    bool IsCollide(GameObject& gameObject);
    bool IsOutOfScreen();
    friend std::ostream& operator<<(std::ostream& os, const GameObject& obj);
};
struct LerpVector{
    Vector currentPos;
    Vector destination;
    float smooth;
    LerpVector(Vector currentPos, Vector destination, float smooth) : currentPos(currentPos), destination(destination), smooth(smooth){}
    //Return False if distance between currentPosition and destination is trivial
    bool Lerping(){
        currentPos = currentPos.Lerp(destination, smooth);
        return currentPos.GetDistance(destination) >= 0.1f;
    }
};
class LerpVectorController{
private:
    static inline vector<pair<GameObject*, LerpVector>> list;
public:
    static void Lerping(){
        for(auto it = list.begin(); it != list.end();){
            // Fix: update GameObject position before checking distance
            if (it->first) it->first->position = it->second.currentPos;
            if (it->second.Lerping()){
                ++it;
            }
            else{
                it = list.erase(it);
            }
        }
    }
    static void AddLerp(GameObject &gameObject, Vector destination){
        list.push_back({&gameObject, LerpVector(gameObject.position, destination, 0.2f)});
    }
};
// struct SpriteRenderer{
//     GameObject gameObject;
//     string textureName;
//     SpriteRenderer(GameObject gameObject) : gameObject(gameObject){
        
//     }
//     void Render(){
//         SDL_RenderCopy(GameConfig::renderer, TextureLoader::loadTexture(textureName), nullptr, gameObject.GetRect());
//     }
// };
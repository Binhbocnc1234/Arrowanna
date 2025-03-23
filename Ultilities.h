#ifndef ULTI
#define ULTI
#pragma once
#include <SDL2/SDL.h>
#include <bits/stdc++.h>

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

enum class Direction { LEFT, RIGHT, UP, DOWN, NONE };

class GameConfig {
public:
    static constexpr const int SCREEN_WIDTH = 800;
    static constexpr int SCREEN_HEIGHT = 600;
    static constexpr int FPS = 60;
    static constexpr bool IS_DEBUG_MODE = false;
    static int WAVE;
    static SDL_Renderer* renderer;
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

struct GameObject{
    Vector position;
    Vector direction;
    Color color;
    int width, height;

    GameObject(int x, int y){
        position.x = x;
        position.y = y;
    }
    GameObject(int x, int y, int width, int height) : position{x, y}, width(width), height(height){

    }
    void Translate(){
        position.x += direction.x;
        position.y += direction.y;
    }
    void SetAttribute(int x, int y, int width, int height){
        position.x = x;
        position.y = y;
        this->width = width;
        this->height = height;
    }
    void RectRender(){
        SDL_SetRenderDrawColor(GameConfig::renderer, color.r, color.g, color.b, color.a);
        SDL_Rect rect = { int(position.x) - width / 2, int(position.y) - height / 2, width, height };
        SDL_RenderFillRect(GameConfig::renderer, &rect);
    }
    bool IsCollide(Vector p){
        return (p.x >= position.x - width / 2 && p.x <= position.x + width / 2 &&
            p.y >= position.y - height / 2 && p.y <= position.y + height / 2);
    }
    friend std::ostream& operator<<(std::ostream& os, const GameObject& obj) {
        os << "GameObject(Position: (" << obj.position.x << ", " << obj.position.y
           << "), Size: [" << obj.width << "x" << obj.height << "] )";
        return os;
    }
};
SDL_Point getRectCenter(const SDL_Rect &rect);

#endif
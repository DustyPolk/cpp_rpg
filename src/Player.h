#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

enum Direction {
    DOWN = 0,
    UP = 1,
    RIGHT = 2,
    LEFT = 3
};

class Player {
private:
    float x, y;
    float velocityX, velocityY;
    int width, height;
    Rectangle rect;
    
    // Sprite and animation properties
    Texture2D spriteSheet;
    Direction currentDirection;
    int currentFrame;
    float frameTimer;
    bool isMoving;

public:
    Player(float startX, float startY);
    ~Player();
    
    void handleInput();
    void update(float deltaTime);
    void render();
    void setPosition(float newX, float newY);
    
    // Boundary checking
    void constrainToWindow(int windowWidth, int windowHeight);
    
    // Collision detection
    bool checkCollision(const Rectangle& other) const;
    Rectangle getRect() const { return rect; }
    
    // Getters
    float getX() const { return x; }
    float getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
private:
    void updateAnimation(float deltaTime);
};

#endif // PLAYER_H
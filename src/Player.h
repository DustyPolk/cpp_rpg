#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
private:
    float x, y;
    float velocityX, velocityY;
    int width, height;
    Rectangle rect;

public:
    Player(float startX, float startY);
    
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
};

#endif // PLAYER_H
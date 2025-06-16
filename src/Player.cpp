#include "Player.h"
#include "Constants.h"
#include <cmath>

Player::Player(float startX, float startY) 
    : x(startX), y(startY), velocityX(0), velocityY(0), 
      width(PLAYER_SIZE), height(PLAYER_SIZE) {
    rect = {x, y, (float)width, (float)height};
}

void Player::handleInput() {
    velocityX = 0;
    velocityY = 0;
    
    // Handle arrow keys or WASD
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        velocityX = -1;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        velocityX = 1;
    }
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        velocityY = -1;
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        velocityY = 1;
    }
    
    // Normalize diagonal movement
    if (velocityX != 0 && velocityY != 0) {
        float length = std::sqrt(velocityX * velocityX + velocityY * velocityY);
        velocityX /= length;
        velocityY /= length;
    }
}

void Player::update(float deltaTime) {
    // Update position based on velocity and delta time
    x += velocityX * PLAYER_SPEED * deltaTime;
    y += velocityY * PLAYER_SPEED * deltaTime;
    
    // Update rectangle for rendering
    rect.x = x;
    rect.y = y;
}

void Player::render() {
    DrawRectangleRec(rect, (Color){PLAYER_COLOR.r, PLAYER_COLOR.g, 
                                   PLAYER_COLOR.b, PLAYER_COLOR.a});
}

void Player::constrainToWindow(int windowWidth, int windowHeight) {
    // Keep player within window boundaries
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x + width > windowWidth) x = windowWidth - width;
    if (y + height > windowHeight) y = windowHeight - height;
    
    // Update rect position
    rect.x = x;
    rect.y = y;
}

bool Player::checkCollision(const Rectangle& other) const {
    return CheckCollisionRecs(rect, other);
}

void Player::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
    rect.x = x;
    rect.y = y;
}
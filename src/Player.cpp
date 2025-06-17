#include "Player.h"
#include "Constants.h"
#include <cmath>
#include <iostream>

Player::Player(float startX, float startY) 
    : x(startX), y(startY), velocityX(0), velocityY(0), 
      width(SPRITE_SIZE * SPRITE_SCALE), height(SPRITE_SIZE * SPRITE_SCALE),
      currentDirection(DOWN), currentFrame(0), frameTimer(0.0f), isMoving(false) {
    rect = {x, y, (float)width, (float)height};
    
    // Load sprite sheet
    spriteSheet = LoadTexture(PLAYER_SPRITE_PATH);
    if (spriteSheet.id == 0) {
        std::cerr << "Failed to load player sprite sheet!" << std::endl;
    }
}

Player::~Player() {
    UnloadTexture(spriteSheet);
}

void Player::handleInput() {
    velocityX = 0;
    velocityY = 0;
    
    // Handle arrow keys or WASD
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        velocityX = -1;
        currentDirection = LEFT;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        velocityX = 1;
        currentDirection = RIGHT;
    }
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        velocityY = -1;
        currentDirection = UP;
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        velocityY = 1;
        currentDirection = DOWN;
    }
    
    // Normalize diagonal movement
    if (velocityX != 0 && velocityY != 0) {
        float length = std::sqrt(velocityX * velocityX + velocityY * velocityY);
        velocityX /= length;
        velocityY /= length;
    }
    
    // Update moving state
    isMoving = (velocityX != 0 || velocityY != 0);
}

void Player::update(float deltaTime) {
    // Update position based on velocity and delta time
    x += velocityX * PLAYER_SPEED * deltaTime;
    y += velocityY * PLAYER_SPEED * deltaTime;
    
    // Update rectangle for collision detection
    rect.x = x;
    rect.y = y;
    
    // Update animation
    updateAnimation(deltaTime);
}

void Player::render() {
    if (spriteSheet.id != 0) {
        // Calculate source rectangle from sprite sheet
        Rectangle sourceRect = {
            (float)(currentFrame * SPRITE_CELL_SIZE),  // x position in sprite sheet
            (float)(currentDirection * SPRITE_CELL_SIZE),  // y position based on direction
            (float)SPRITE_CELL_SIZE,
            (float)SPRITE_CELL_SIZE
        };
        
        // Destination rectangle for drawing
        Rectangle destRect = {
            x,
            y,
            (float)width,
            (float)height
        };
        
        // Draw the sprite
        DrawTexturePro(spriteSheet, sourceRect, destRect, {0, 0}, 0.0f, WHITE);
    } else {
        // Fallback to rectangle if sprite loading failed
        DrawRectangleRec(rect, (Color){PLAYER_COLOR.r, PLAYER_COLOR.g, 
                                       PLAYER_COLOR.b, PLAYER_COLOR.a});
    }
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

void Player::updateAnimation(float deltaTime) {
    if (isMoving) {
        // Update frame timer
        frameTimer += deltaTime;
        
        // Check if it's time to advance to the next frame
        if (frameTimer >= ANIMATION_SPEED) {
            frameTimer = 0.0f;
            currentFrame = (currentFrame + 1) % 4; // 4 frames per direction
        }
    } else {
        // Reset to first frame when not moving
        currentFrame = 0;
        frameTimer = 0.0f;
    }
}
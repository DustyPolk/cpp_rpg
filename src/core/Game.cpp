#include "core/Game.h"
#include "config/Constants.h"
#include <iostream>

Game::Game() : isRunning(false), screenWidth(0), screenHeight(0) {}

Game::~Game() {
    clean();
}

bool Game::init(const char* title, int width, int height) {
    screenWidth = width;
    screenHeight = height;
    
    // Initialize window
    InitWindow(width, height, title);
    
    // Set target FPS
    SetTargetFPS(FPS);
    
    // Initialize player at center of screen
    player = std::make_unique<Player>(width / 2.0f - PLAYER_SIZE / 2.0f, 
                                     height / 2.0f - PLAYER_SIZE / 2.0f);
    
    // Create some test walls
    Color wallColor = {WALL_COLOR.r, WALL_COLOR.g, WALL_COLOR.b, WALL_COLOR.a};
    
    // Top wall
    walls.emplace_back(100, 50, 600, 50, wallColor);
    
    // Bottom wall
    walls.emplace_back(100, 500, 600, 50, wallColor);
    
    // Left wall
    walls.emplace_back(50, 100, 50, 350, wallColor);
    
    // Right wall
    walls.emplace_back(700, 100, 50, 350, wallColor);
    
    // Some obstacles in the middle (keeping clear of center spawn point)
    walls.emplace_back(200, 150, 100, 50, wallColor);
    walls.emplace_back(500, 400, 100, 50, wallColor);
    walls.emplace_back(600, 200, 50, 100, wallColor);
    
    isRunning = true;
    return true;
}

void Game::handleEvents() {
    // Check for window close
    if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) {
        isRunning = false;
    }
    
    // Handle continuous input
    player->handleInput();
}

void Game::update(float deltaTime) {
    // Store old position
    float oldX = player->getX();
    float oldY = player->getY();
    
    // Update player position
    player->update(deltaTime);
    
    // Check collision with walls
    bool collision = false;
    for (const auto& wall : walls) {
        if (player->checkCollision(wall.getRect())) {
            collision = true;
            break;
        }
    }
    
    // If collision occurred, restore old position
    if (collision) {
        player->setPosition(oldX, oldY);
    }
    
    player->constrainToWindow(screenWidth, screenHeight);
}

void Game::render() {
    BeginDrawing();
    
    // Clear screen with background color
    ClearBackground((Color){BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, 
                           BACKGROUND_COLOR.b, BACKGROUND_COLOR.a});
    
    // Render walls
    for (const auto& wall : walls) {
        const_cast<Wall&>(wall).render();
    }
    
    // Render player
    player->render();
    
    EndDrawing();
}

void Game::clean() {
    CloseWindow();
}
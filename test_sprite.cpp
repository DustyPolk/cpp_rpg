#include "raylib.h"
#include <iostream>

int main() {
    InitWindow(800, 600, "Sprite Test");
    SetTargetFPS(60);
    
    // Load the sprite sheet
    Texture2D spriteSheet = LoadTexture("assets/Sprout Lands - Sprites - Basic pack/Characters/Basic Charakter Spritesheet.png");
    
    if (spriteSheet.id == 0) {
        std::cout << "Failed to load sprite!" << std::endl;
    } else {
        std::cout << "Sprite loaded: " << spriteSheet.width << "x" << spriteSheet.height << std::endl;
    }
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        if (spriteSheet.id != 0) {
            // Draw the entire sprite sheet
            DrawTexture(spriteSheet, 10, 10, WHITE);
            
            // Draw grid lines to see the 48x48 divisions
            for (int i = 0; i <= 4; i++) {
                DrawLine(10 + i * 48, 10, 10 + i * 48, 10 + 192, RED);
                DrawLine(10, 10 + i * 48, 10 + 192, 10 + i * 48, RED);
            }
            
            // Draw just the first sprite scaled up
            Rectangle source = {0, 0, 48, 48};
            Rectangle dest = {300, 50, 144, 144}; // 3x scale
            DrawTexturePro(spriteSheet, source, dest, {0, 0}, 0, WHITE);
            DrawRectangleLinesEx(dest, 2, GREEN);
        }
        
        DrawText("Full sprite sheet with grid", 10, 220, 20, BLACK);
        DrawText("First sprite 3x scale", 300, 200, 20, BLACK);
        
        EndDrawing();
    }
    
    UnloadTexture(spriteSheet);
    CloseWindow();
    
    return 0;
}
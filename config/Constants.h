#ifndef CONSTANTS_H
#define CONSTANTS_H

// Window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Game settings
const int FPS = 60;

// Player settings
const float PLAYER_SPEED = 200.0f; // pixels per second
const int PLAYER_SIZE = 48; // Size of the player hitbox

// Sprite settings
const int SPRITE_SIZE = 16; // Original sprite size in pixels
const int SPRITE_CELL_SIZE = 48; // Size of each cell in the sprite sheet (192px / 4 = 48px)
const float SPRITE_SCALE = 3.0f; // Scale factor for display (makes it 48x48)
const float ANIMATION_SPEED = 0.1f; // Seconds per animation frame
const char PLAYER_SPRITE_PATH[] = "assets/Sprout Lands - Sprites - Basic pack/Characters/Basic Charakter Spritesheet.png";

// Colors (RGBA)
struct GameColor {
    unsigned char r, g, b, a;
};

const GameColor BACKGROUND_COLOR = {50, 50, 50, 255};
const GameColor PLAYER_COLOR = {0, 255, 0, 255};
const GameColor WALL_COLOR = {100, 100, 100, 255};

#endif // CONSTANTS_H
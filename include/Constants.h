#ifndef CONSTANTS_H
#define CONSTANTS_H

// Window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Game settings
const int FPS = 60;

// Player settings
const float PLAYER_SPEED = 200.0f; // pixels per second
const int PLAYER_SIZE = 32;

// Colors (RGBA)
struct GameColor {
    unsigned char r, g, b, a;
};

const GameColor BACKGROUND_COLOR = {50, 50, 50, 255};
const GameColor PLAYER_COLOR = {0, 255, 0, 255};
const GameColor WALL_COLOR = {100, 100, 100, 255};

#endif // CONSTANTS_H
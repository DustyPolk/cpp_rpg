#include "raylib.h"
#include <iostream>
#include "Game.h"
#include "Constants.h"

int main(int argc, char* argv[]) {
    Game game;
    
    if (!game.init("Zelda-like Game", WINDOW_WIDTH, WINDOW_HEIGHT)) {
        std::cerr << "Failed to initialize game!" << std::endl;
        return -1;
    }
    
    while (game.running()) {
        float deltaTime = GetFrameTime();
        
        game.handleEvents();
        game.update(deltaTime);
        game.render();
    }
    
    return 0;
}
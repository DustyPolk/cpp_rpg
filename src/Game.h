#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <memory>
#include <vector>
#include "Player.h"
#include "Wall.h"

class Game {
private:
    bool isRunning;
    std::unique_ptr<Player> player;
    std::vector<Wall> walls;
    int screenWidth;
    int screenHeight;

public:
    Game();
    ~Game();
    
    bool init(const char* title, int width, int height);
    void handleEvents();
    void update(float deltaTime);
    void render();
    void clean();
    
    bool running() const { return isRunning; }
};

#endif // GAME_H
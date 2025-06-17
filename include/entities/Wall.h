#ifndef WALL_H
#define WALL_H

#include <raylib.h>

class Wall {
private:
    float x;
    float y;
    float width;
    float height;
    Color color;

public:
    Wall(float x, float y, float width, float height, Color color);
    
    void render() const;
    Rectangle getRect() const;
};

#endif
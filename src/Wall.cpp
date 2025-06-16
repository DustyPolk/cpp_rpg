#include "Wall.h"

Wall::Wall(float x, float y, float width, float height, Color color)
    : x(x), y(y), width(width), height(height), color(color) {}

void Wall::render() const {
    DrawRectangle(x, y, width, height, color);
}

Rectangle Wall::getRect() const {
    return Rectangle{x, y, width, height};
}
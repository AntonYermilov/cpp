#include "rectangle.h"
#include <cstdio>

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y) {
    _width = width;
    _height = height;
}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", _id, _x, _y, _width, _height);
}

bool Rectangle::is_inside(int x, int y) const {
    return _x * 2 - _width <= 2 * x && 2 * x <= _x * 2 + _width && 
           _y * 2 - _height <= 2 * y && 2 * y <= _y * 2 + _height;
    //zoomed twice to avoid use of floats
}

void Rectangle::zoom(int factor) {
    _width *= factor;
    _height *= factor;
}

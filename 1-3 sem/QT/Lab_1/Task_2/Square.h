#ifndef SQUARE_H
#define SQUARE_H

#include <rectangle.h>

class Square : public Rectangle {
public:
    Square(short width = 0, double rotation = 0) :
        Rectangle(width, width, rotation) {}
};

#endif // SQUARE_H

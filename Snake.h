#ifndef SNAKE_H
#define SNAKE_H

#include "Point.h"


class Snake {
public:
    Point body[100]; 
    int length;      

    Snake();
    void draw();
    void move(int direction);
    bool checkCollision();
    void grow();
};

#endif 

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Point.h"
#include "Snake.h"

class Environment {
public:
    Point food;        
    Point specialFood; 
    bool effect;       

    Environment();
    void drawWall();
    void generateFood();
    void generateSpecialFood();
    bool checkFoodEaten(Point head);
    bool checkSpecialFoodEaten(Point head);
    void toggleEffect(bool status);
    void applyEffect(Snake& snake);
};

#endif 

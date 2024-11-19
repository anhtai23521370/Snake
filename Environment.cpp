#include "Environment.h"
#include "ConsoleUtils.h"
#include <ctime>
#include <cstdlib>

Environment::Environment() {
    effect = false;
    generateFood();
}

void Environment::drawWall() {
    for (int i = 1; i < 100; i++) {
        gotoxy(i, 1); cout << "v";
        gotoxy(i, 26); cout << "^";
    }
    for (int i = 1; i < 27; i++) {
        gotoxy(1, i); cout << ">";
        gotoxy(99, i); cout << "<";
    }
}

void Environment::generateFood() {
    srand(time(NULL));
    food.x = rand() % (98 - 2 + 1) + 2;
    food.y = rand() % (25 - 2 + 1) + 2;
    gotoxy(food.x, food.y);
    cout << "$";
}

void Environment::generateSpecialFood() {
    srand(time(NULL) + 3);
    specialFood.x = rand() % (98 - 2 + 1) + 2;
    specialFood.y = rand() % (25 - 2 + 1) + 2;
    gotoxy(specialFood.x, specialFood.y);
    SetColor(4);
    cout << "+";
    SetColor(15);
}

bool Environment::checkFoodEaten(Point head) {
    return head.sosanhbang(food);
}

bool Environment::checkSpecialFoodEaten(Point head) {
    return head.sosanhbang(specialFood);
}

void Environment::toggleEffect(bool status) {
    effect = status;
}

void Environment::applyEffect(Snake& snake) {
    if (effect) {
        for (int i = 0; i < snake.length; i++) {
            SetColor(rand() % 15 + 1);
            gotoxy(snake.body[i].x, snake.body[i].y);
            cout << "X";
        }
    }
}

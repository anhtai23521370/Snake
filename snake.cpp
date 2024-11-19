#include "Snake.h"
#include "ConsoleUtils.h" 

Snake::Snake() {
    length = 3;
    body[0] = {15, 10};
    body[1] = {14, 10};
    body[2] = {13, 10};
}

void Snake::draw() {
    for (int i = 0; i < length; i++) {
        gotoxy(body[i].x, body[i].y);
        cout << "X";
    }
    gotoxy(body[length].x, body[length].y);
    cout << " ";
}

void Snake::move(int direction) {
    for (int i = length - 1; i > 0; i--) {
        body[i] = body[i - 1];
    }
    switch (direction) {
        case 0: body[0].x += 1; break; 
        case 1: body[0].y += 1; break;
        case 2: body[0].x -= 1; break; 
        case 3: body[0].y -= 1; break; 
    }
}

bool Snake::checkCollision() {
    for (int i = 1; i < length; i++) {
        if (body[0].sosanhbang(body[i])) {
            return true;
        }
    }
    return false;
}

void Snake::grow() {
    length++;
}

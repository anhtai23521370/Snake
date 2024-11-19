#include "Snake.h"
#include "Environment.h"
#include "ConsoleUtils.h"
#include <conio.h>

int main() {
    Snake snake;
    Environment env;

    int direction = 0; // Mặc định là rắn di chuyển sang phải
    env.drawWall();
    env.generateFood();
    char input;

    while (true) {
        if (kbhit()) {
            input = getch();
            if (input == 'a' && direction != 0) direction = 2; 
            else if (input == 'w' && direction != 1) direction = 3; 
            else if (input == 'd' && direction != 2) direction = 0; 
            else if (input == 's' && direction != 3) direction = 1; 
        }

        snake.move(direction);

        if (env.checkFoodEaten(snake.body[0])) {
            snake.grow();
            env.generateFood();
        }

        snake.draw();
        env.applyEffect(snake);

        if (snake.checkCollision()) {
            gotoxy(1, 30);
            cout << "GAME OVER";
            break;
        }

        Sleep(100);
    }

    return 0;
}

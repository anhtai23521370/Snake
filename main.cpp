#include "include.h"
void initScore() {
    if (isEmpty()) {
        for (int i = 0; i < 5; i++) {
            strcpy(highscore[i].name, "PLAYER");
            highscore[i].score = 0;
        }
        getHighScore();
    }
    else {
        char arr[20];
        int count = 0;
        FILE* f = fopen("highscore.txt", "r");

        if (f == NULL) {
            // Tệp không thể mở, có thể thông báo lỗi hoặc xử lý theo cách khác
            return;
        }

        for (int i = 0; i < 5;) {
            while (fscanf(f, "%s", arr) != EOF) {  // Đọc từ tệp đến hết
                count++;
                if (count % 2 == 1) {
                    strcpy(highscore[i].name, arr);
                }
                else {
                    highscore[i].score = atoi(arr);
                    i++;
                }
            }
        }

        fclose(f);  // Đóng tệp sau khi hoàn tất
    }
}

void showText(int x, int y, const char* str) {
    int c = getcolor();
    int color = rand() % 16 + 1;
    setcolor(color);
    outtextxy(x + 3, y, str);
    setcolor(c);
    delay(50);
}
void showTextBackground(int x, int y, const char* str, int color) {
    int bk = getbkcolor();
    setbkcolor(color);
    outtextxy(x, y, str);
    delay(100);
    setbkcolor(bk);
}
bool isEmpty() {
    FILE* fp;
    long size;
    fp = fopen("highscore.txt", "r");
    if (fp) {
        fseek(fp, 0, SEEK_END);
        size = ftell(fp);
        fclose(fp);
    }
    return(size == 0);
}
bool checkPoint() {
    for (int i = 0; i < snakeLength; i++) {
        if (food.x == snake[i].x && food.y == snake[i].y)
            return false;
    }
    return true;
}
bool my_kbhit() {
    // Kiểm tra trạng thái của tất cả các phím từ 0 đến 255
    for (int i = 0; i < 256; i++) {
        // Nếu bit cao nhất của phím được nhấn (0x8000), tức là phím đó đang được nhấn
        if (GetAsyncKeyState(i) & 0x8000) {
            return true;  // Trả về true nếu có phím nhấn
        }
    }
    return false;  // Không có phím nhấn nào
}

// Hàm đọc phím nhấn
char my_getch() {
    // Tìm phím nhấn ngay lập tức mà không trì hoãn
    for (int i = 0; i < 256; i++) {
        if (GetAsyncKeyState(i) & 0x8000) {
            return (char)i;  // Trả về ký tự của phím nhấn
        }
    }
    return '\0';  // Nếu không có phím nào nhấn, trả về ký tự rỗng
}


void drawPoint(int x, int y, int r) {
    circle(x, y, r);
    floodfill(x, y, getcolor());
}
void drawSnake() {
    setfillstyle(1, 10);
    int count = 0;
    for (int i = 0; count < snakeLength; i++) {
        drawPoint(snake[i].x, snake[i].y, 5);
        count++;
    }
    //delete point when snake move
    int x = getcolor();
    setfillstyle(1, BACKGROUND);
    drawPoint(snake[snakeLength - 1].x0, snake[snakeLength - 1].y0, 5);
    setcolor(15);
    circle(snake[snakeLength - 1].x0, snake[snakeLength - 1].y0, 5);
    setcolor(x);
    setfillstyle(1, 5);
}
void drawFood() {
    int x = getcolor();
    int c = rand() % 14 + 1;
    setcolor(c); setfillstyle(SOLID_FILL, c);
    drawPoint(food.x, food.y, 5);
    setcolor(x); setfillstyle(1, BACKGROUND);
}
//Ve toan bo giao dien game
void drawGame() {
    drawSnake();
    drawFood();
    int x = getcolor();
    setcolor(2);
    sprintf(score_str, "%d", snakeLength - 3);    //show score
    settextstyle(4, 0, 3);
    outtextxy(450, 20, "SCORE:");
    setcolor(12);
    outtextxy(600, 20, score_str);
    setcolor(x);
}

void showHighScore() {
    FILE* f;
    f = fopen("highscore.txt", "r");
    char ch[20];
    settextstyle(1, 0, 5);
    setcolor(15);
    outtextxy(150, 50, "HIGH SCORE");
    settextstyle(1, 0, 4);
    int y = 150, count = 0;
    while (!feof(f)) {
        if (count == 10) break;
        count++;
        fscanf(f, "%s", ch);
        if (count % 2 == 1) {
            setcolor(10);
            outtextxy(180, y, ch);
            y += 50;
        }
        else {
            setcolor(12);
            outtextxy(500, y - 50, ch);
        }
    }
    fclose(f);
}
void getHighScore() {
    FILE* f;
    f = fopen("highscore.txt", "w");
    for (int i = 0; i < 5; i++) {
        fputs(highscore[i].name, f);
        fputs(" ", f);
        fprintf(f, "%d", highscore[i].score);
        fputs("\n", f);
    }
    fclose(f);
}
void checkHighScore(int _score) {
    char _name[20] = { "" };
    for (int i = 0; i < 5; i++) {
        if (_score > highscore[i].score) {
            //to do sth
            settextstyle(1, 0, 3);
            for (int j = 0; j < 50; j++) {
                if (j % 2 == 0) {
                    setcolor(14);
                    if (i == 0)
                        outtextxy(460, 100, "BEST SCORE");
                    else
                        outtextxy(460, 100, "HIGH SCORE");
                    delay(100);
                }
                else {
                    setcolor(9);
                    if (i == 0)
                        outtextxy(460, 100, "BEST SCORE");
                    else
                        outtextxy(460, 100, "HIGH SCORE");
                    delay(100);
                }
            }
            settextstyle(1, 0, 2);
            setcolor(4); outtextxy(430, 150, "Player:");
            delay(100);
            char ch1 = 0;
            int x = 0;
            char str[2];
            str[1] = 0;
            while (ch1 != 13 && x < 10) {
                do {
                    ch1 = my_getch();
                } while (ch1 < 65 && ch1 >90 || ch1 < 97 && ch1 > 132);
                x++;
                str[0] = ch1;
                strcat(_name, str);
                outtextxy(540, 150, _name);
            }
            for (int j = 4; j > i; j--) {
                strcpy(highscore[j].name, highscore[j - 1].name);
                highscore[j].score = highscore[j - 1].score;
            }
            strcpy(highscore[i].name, _name);
            highscore[i].score = _score;
            break;
        }
    }
    getHighScore();
}

void newFood() {
    srand(time(NULL));  // Khởi tạo hàm sinh số ngẫu nhiên
    do {
        food.x = (rand() % (39) + 3) * 10;  // Sinh tọa độ x cho thực phẩm
        food.y = (rand() % (19) + 3) * 10;  // Sinh tọa độ y cho thực phẩm
    } while (checkPoint() == false);

}
void basic() {
    for (int i = 0; i < snakeLength; i++) {
        if (i == 0) {
            snake[0].x0 = snake[0].x; snake[0].y0 = snake[0].y;
            snake[0].x += direction.x;
            snake[0].y += direction.y;
        }
        else {
            snake[i].x0 = snake[i].x; snake[i].y0 = snake[i].y;
            snake[i].x = snake[i - 1].x0; snake[i].y = snake[i - 1].y0;
        }

        if (snake[i].x >= MAXX || snake[i].x <= MINX || snake[i].y >= MAXY || snake[i].y <= MINY) {
            endGame = true;  // Đặt cờ kết thúc trò chơi
            break;  // Thoát hàm nếu rắn đụng tường
        }

        if (i != 0 && snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            endGame = true;
            break;  // Thoát ngay lập tức nếu va chạm
        }
    }
    if (snake[0].x == food.x && snake[0].y == food.y) {
        snake[snakeLength].x = snake[snakeLength - 1].x0; 
        snake[snakeLength].y = snake[snakeLength - 1].y0;
        snakeLength++;

        //Làm mới vị trị đồ ăn sau khi bị đớp
        newFood();
    }
}
void initGame() {
    setbkcolor(15);  // Đặt màu nền cho cửa sổ đồ họa là màu trắng (15 - Màu trắng trong bảng màu 16 màu)
    cleardevice();  // Xóa toàn bộ nội dung trên màn hình
    endGame = false;    // Biến này có thể được dùng để kiểm tra xem trò chơi đã kết thúc chưa
    setfillstyle(1, 5);  // Chọn kiểu tô và màu để vẽ các hình vuông, hình chữ nhật
    bar(MINX, MINY, MAXX, MINY + 5);  // Vẽ thanh ngang phía trên
    bar(MAXX, MINY, MAXX - 5, MAXY);  // Vẽ thanh dọc bên phải
    bar(MAXX, MAXY, MINX, MAXY - 5);  // Vẽ thanh ngang phía dưới
    bar(MINX, MINY, MINX + 5, MAXY);  // Vẽ thanh dọc bên trái
    setcolor(0);
    int bk = getbkcolor();
    setfillstyle(SOLID_FILL, 0);
    int a[] = { 15,350,30,350,30,345,50,355,30,365,30,360,15,360,15,350 };
    fillpoly(8, a);  // Vẽ mũi tên "Right"
    outtextxy(70, 340, "d");

    int b[] = { 15,410,30,400,30,405,45,405,45,415,30,415,30,420,15,410 };
    fillpoly(8, b);  // Vẽ mũi tên "Left"
    outtextxy(70, 400, "a");

    int c[] = { 235,370,235,355,230,355,240,340,250,355,245,355,245,370,235,370 };
    fillpoly(8, c);  // Vẽ mũi tên "Up"
    outtextxy(265, 340, "w");

    int d[] = { 235,400,235,415,230,415,240,430,250,415,245,415,245,400,235,400 };
    fillpoly(8, d);  // Vẽ mũi tên "Down"
    outtextxy(265, 400, "s");

    bar(50, 450, 170, 480); setcolor(15); settextstyle(1, 0, 1); setbkcolor(0); outtextxy(60, 455, "SPACE"); setbkcolor(bk);
    setcolor(0); settextstyle(4, 0, 3); outtextxy(200, 450, "Pause/Resum");

    bar(50, 500, 170, 530); setcolor(15); settextstyle(1, 0, 1); setbkcolor(0); outtextxy(80, 505, "ESC"); setbkcolor(bk);
    setcolor(0); settextstyle(4, 0, 3); outtextxy(200, 500, "End Game");
    // khởi tạo vị trí ban đầu của con rắn
    snake[0].x = 60; snake[0].y = 50;
    snake[1].x = 50; snake[1].y = 50;
    snake[2].x = 40; snake[2].y = 50;
    snakeLength = 3;  // Đặt chiều dài ban đầu của con rắn là 3
    setfillstyle(1, BACKGROUND);
    bar(25, 25, 415, 215);
    direction.x = 10; direction.y = 0; // Khoi tao di theo huong trai qua phai
    setcolor(2);
    newFood();
}

void mainLoop(void (*xxx)()) {
    int x = getcolor();
    char ch = my_getch();

    if (ch == '\0') {
        if (!paused) {
            xxx();  
        }
        return;
    }
    
        if (ch == 32) { //nhấn space
            paused = (paused == 0) ? 1 : 0;  // đổi trạng thái paused
            setcolor(0);
            if (paused) {
                outtextxy(100, 100, "Game Paused");  //in "Game Paused"
                return;
            }
            else {
                setcolor(15);
                outtextxy(100, 100, "Game Paused");  // mất "Game Paused" 
            }
            setcolor(x);
            delay(200);  
            return;
        }

        // các nút điều khiển
        if (!paused) {
            if (ch == 'w' || ch == 'W') {  //lên
                changeDirecton(72);
            }
            else if (ch == 's' || ch == 'S') {  // xuống
                changeDirecton(80);
            }
            else if (ch == 'a' || ch == 'A') {  // trái
                changeDirecton(75);
            }
            else if (ch == 'd' || ch == 'D') {  // phải
                changeDirecton(77);
            }
            else if (ch == 27) { // ESC nghỉ game
                changeDirecton(27);
                return;
            }
        }
        return;
}

void changeDirecton(int x) {
    switch (x) {
    case 72:
        if (direction.y != DIRECTION) {
            direction.y = -DIRECTION; direction.x = 0;
        }
        break;
    case 80:
        if (direction.y != -DIRECTION) {
            direction.y = DIRECTION; direction.x = 0;
        }
        break;
    case 77:
        if (direction.x != -DIRECTION) {
            direction.x = DIRECTION; direction.y = 0;
        }
        break;
    case 75:
        if (direction.x != DIRECTION) {
            direction.x = -DIRECTION; direction.y = 0;
        }
        break;
    case 27:
        endGame = true;
        break;
    }
}
void run() {
    initwindow(800, 600, "SNAKE GAME", 100, 100);  // Khởi tạo cửa sổ đồ họa
     //initScore();
    int bk = getbkcolor();  // Lưu lại màu nền hiện tại
    cleardevice();  // Xóa màn hình hiện tại
    setbkcolor(0);  // Thiết lập màu nền là màu đen
    cleardevice();  // Xóa lại màn hình sau khi thay đổi màu nền
    clearmouseclick(WM_LBUTTONDOWN);  // Xóa sự kiện chuột nếu có

    while (true) {
    x1:
        int bk = getbkcolor();
        cleardevice();
        setbkcolor(0);
        cleardevice();
        clearmouseclick(WM_LBUTTONDOWN);

        while (!ismouseclick(WM_LBUTTONDOWN) || mousex() < 200 || mousey() > 465 || mousey() < 190 || mousex() > 580) {
            settextstyle(1, 0, 6);
            setcolor(10);
            outtextxy(120, 70, "GAME MENU");
            settextstyle(10, 0, 5);
            showText(220, 200, "NEW GAME");
            showText(220, 270, "HIGH SCORE");
            showText(220, 340, "QUIT GAME");
            showText(220, 410, "HELP");
        }
        clearmouseclick(WM_LBUTTONDOWN);
        if (mousey() <= 255) {
            showTextBackground(220, 200, "NEW GAME", 15);
        x2:
            setbkcolor(0);
            cleardevice();
            clearmouseclick(WM_LBUTTONDOWN);
            initGame();
            while (!endGame) {
                delay(200);
                drawGame();
                mainLoop(basic);
            }
           
            settextstyle(1, 0, 4);
            setcolor(0);
            outtextxy(100, 110, "GAME OVER!");
            setcolor(8);
            settextstyle(1, 0, 2);
            outtextxy(100, 160, "Your Score : ");
            setcolor(10);
            outtextxy(300, 160, score_str);

            //Here is check high score
            checkHighScore(snakeLength-3);
            setcolor(10); settextstyle(4, 0, 5);
            outtextxy(100, 200, "Play Again ?");
            settextstyle(4, 0, 3);
            setcolor(1);
            clearmouseclick(WM_LBUTTONDOWN);
            while (!ismouseclick(WM_LBUTTONDOWN)) {
                showTextBackground(150, 270, "YES", 12); showTextBackground(300, 270, "NO", 7);
            }
            if (ismouseclick(WM_LBUTTONDOWN)) {
                if (mousex() >= 140 && mousex() <= 230 && mousey() >= 260 && mousey() <= 310) {
                    showTextBackground(150, 270, "YES", 7);
                    delay(100);
                    goto x2;
                }
                else if (mousex() >= 290 && mousex() <= 360 && mousey() >= 260 && mousey() <= 310) {
                    showTextBackground(300, 270, "NO", 12);
                    delay(100);
                    goto x1;
                }
            }
        }
        else if (mousey() <= 325) {
            showTextBackground(220, 270, "HIGH SCORE", 15);
            cleardevice();
            showHighScore();
            while (!ismouseclick(WM_LBUTTONDOWN)) {
                delay(10);
            }
            
            goto x1;
        }
        else if (mousey() <= 395) {
            showTextBackground(220, 340, "QUIT GAME", 15);
            exit(0);
        }
        else {

            cleardevice();
            settextstyle(1, 0, 4);
            setcolor(15);
            int x = getcolor();
            while (!ismouseclick(WM_LBUTTONDOWN)) {
                settextstyle(10, 0, 6); setcolor(15);
                outtextxy(260, 20, "INSTRUCTION");
                settextstyle(10, 0, 4); setcolor(14);
                outtextxy(240, 100, "a  : LEFT");
                settextstyle(10, 0, 4); setcolor(14);
                outtextxy(240, 150, "d  : RIGHT");
                settextstyle(10, 0, 4); setcolor(14);
                outtextxy(240, 200, "s  : DOWN");
                settextstyle(10, 0, 4); setcolor(14);
                outtextxy(240, 250, "w  : UP");
                settextstyle(10, 0, 4); setcolor(14);
                outtextxy(240, 300, "space  : PAUSE GAME ");
                settextstyle(10, 0, 4); setcolor(14);
                outtextxy(240, 350, "esc  : STOP GAME ");
            }
            setcolor(x);
            settextstyle(1, 0, 2);
            setcolor(4);
            goto x1;
        }


    }
}
int main() {
    run();  // Chạy trò chơi
    delete score_str;
    my_getch();
    closegraph();  // Đóng cửa sổ đồ họa khi kết thúc

    return 0;
}

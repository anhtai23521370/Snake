#pragma once
#include <windows.h>
#include "graphics.h"
#pragma comment (lib,"graphics.lib")
#include <iostream>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>

using namespace std;

#define 	MINW 		20
#define 	MINH 		20
#define 	MAXW 		420
#define 	MAXH 		220
#define 	MINX 		20
#define 	MINY 		20
#define 	MAXX 		420
#define 	MAXY 		220
#define 	BACKGROUND	15

struct Point {
	int x, y, x0, y0;
};
struct HighScore {
	int score;
	char name[30];
};

void initGame();
bool checkPoint();
void drawPoint(int x, int y, int r);
void moveSnake();
void drawSnake();
void drawFood();
void drawGame();
void classic();
void modern();
void mainLoop(void (*gloop)());
void run();
void changeDirecton(int x);
void showHighScore();
void getHighScore();
void checkHighScore(int score);
void initScore();
bool isEmpty();
void showText(int x, int y, const char* str);
void showTextBackground(int x, int y,const char* str, int color);

bool paused = false; // trạng thái dừng

int level;
bool endGame;
int snakeLength;
Point snake[100];
Point direction;
Point food;
const int DIRECTION = 10;
HighScore  highscore[5];
char* score_str = new char[20];// Convert score to string
bool isPaused = false;  // Biến toàn cục để theo dõi trạng thái tạm dừng
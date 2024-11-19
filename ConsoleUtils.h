#ifndef CONSOLEUTILS_H
#define CONSOLEUTILS_H

#include <windows.h>
#include <iostream>
using namespace std;

void gotoxy(int column, int line);
void SetColor(WORD color);
void ShowCur(bool CursorVisibility);

#endif 

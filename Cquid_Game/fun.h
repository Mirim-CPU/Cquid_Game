/* fun.h */
#pragma once

#include <Windows.h>
#include <conio.h>


// HIDE: 커서 숨기기, UNDERBAR: _ 커서 보이기, BLOCK: 블록 커서 보이기
enum CURSOR_TYPE { HIDE, UNDERBAR, BLOCK };
// 콘솔 창 색깔 변경(setColor)할 때 쓰는 색깔코드
enum color {
	black1,
	DARK_BLUE,
	DARK_GREEN,
	DARK_SKYBLUE,
	DARK_RED,
	DARK_VIOLET,
	DARK_YELLOW,
	gray1,
	DARK_GRAY,
	blue1,
	green1,
	SKYBLUE,
	red1,
	VIOLET,
	yellow1,
	white1
};


void gotoxy1(int x, int y);
void movexy(int x, int y);
void setCursor(enum CURSOR_TYPE curType);
int curX();
int curY();
void clearBuffer();
void setColor1(enum color color);

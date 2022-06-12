/* fun.c */
#include "fun.h"

// (x, y) 좌표에 커서를 놓는다.
void gotoxy1(int x, int y) {
	static COORD pos = {0,};
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// x칸, y칸만큼 커서를 옮긴다.
void movexy(int x, int y) {
	gotoxy1(curX() + x, curY() + y);
}

// 커서 모양을 변경한다.
void setCursor(enum CURSOR_TYPE curType) {
	static CONSOLE_CURSOR_INFO CurInfo = { 0, };

	switch (curType) {
	case HIDE:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case UNDERBAR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = TRUE;
		break;
	case BLOCK:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	}

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

// 현재 커서의 X 좌표를 리턴
int curX() {
	static CONSOLE_SCREEN_BUFFER_INFO curInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	return curInfo.dwCursorPosition.X;
}

// 현재 커서의 Y 좌표를 리턴
int curY() {
	static CONSOLE_SCREEN_BUFFER_INFO curInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	return curInfo.dwCursorPosition.Y;
}

// stdin 버퍼 클리어
void clearBuffer() {
	while (_kbhit()) {
		int _ = _getch();
	}
}

// 콘솔 텍스트 색상 변경
void setColor1(enum color color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

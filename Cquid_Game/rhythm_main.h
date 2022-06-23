/* rhythm_main.h */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "fun.h"

#define SCREEN_WIDTH 120 // 콘솔 창 가로 길이
#define SCREEN_HEIGHT 30 // 콘솔 창 세로 길이

#define LINE 4 // 노트 라인의 수 = 누르는 키의 개수


enum KeyCode { // 키코드
	BACKSPACE = 8, // 백스페이스 키코드
	TAB = 9, // 탭 키코드
	enter = 13, // 엔터 키코드
	esc = 27, // ESC 키코드
	SPACE = 32, // 스페이스바 키코드
	up = 72, // 위쪽 방향키 키코드
	down = 80 // 아래쪽 방향키 키코드
};


int key[LINE]; // 각 라인을 누르는 키 목록
wchar_t keyName[LINE][5]; // 각 키의 이름
const char* mapFolder; // 맵이 저장된 폴더 경로 ("maps")


// selectmap.h
extern int mapCount;
extern char** mapList;

rhy_main();
void main_keysetting();
void main_title();
char* main_selectmap();
void main_gameplay(char* _mapName);
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <process.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define SCR_WIDTH 1920
#define SCR_HEIGHT 1080
#define NUM_SONG 3

// 색상 정의
#define BLACK	0
#define BLUE1	1
#define GREEN1	2
#define CYAN1	3
#define RED1	4
#define MAGENTA1 5
#define YELLOW1	6
#define GRAY1	7
#define GRAY2	8
#define BLUE2	9
#define GREEN2	10
#define CYAN2	11
#define RED2	12
#define MAGENTA2 13
#define YELLOW2	14
#define WHITE	15

#define SPECIAL1 0xe0 // 특수키는 0xe0 + key 값으로 구성된다.
#define SPECIAL2 0x00 // keypad 경우 0x00 + key 로 구성된다.
#define UP  0x48 // Up key는 0xe0 + 0x48 두개의 값이 들어온다.
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d
#define ENTER 13

void rhythm_main();
void removeCursor();
void cls();
void textcolor();
void Dkey_press();
void Fkey_press();
void Jkey_press();
void Kkey_press();
void render();
void draw_box();
void remove_box();
void draw_main_menu();
void draw_map(n);
void print_score(int score, int score_p, int score_g, int score_m);
void start_rhythmgame(int song);
void write_note(int song);
void select_song();
void go_option();
void draw_help();
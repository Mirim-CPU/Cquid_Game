#include "pushpull.h"
#include <conio.h>
#include <windows.h>

// _getch() value of ESC key
#define MAGIC_KEY 224
#define ESC 27
#define A 65
#define a 97
#define L 76
#define l 108
#define ENTER 13

void game_fun(void);
void start_game(void);

char key;
char t_name1[20];
char t_name2[20];
int x = 40;
int y = 11;
int win = 0;
int win_lose = 0;
int input = 0;

enum MENU
{
	GAMESTART = 0,
	EXIT
};

enum KEYBOARD
{
	UP = 72,
	LEFT = 75,
	RIGHT = 77,
	DOWN = 80
};

// 게임 시작 메인 함수
void main_pushpull() {
	system("cls");
	PlaySound(TEXT("./sound/push.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (1) {
		switch (game()) {
		case GAMESTART:
			x = 40;
			start_game();
			break;

		case EXIT:
			//PlaySound(NULL, 0, 0);
			system("cls");
			main();

			break;
		}
	}
	return 0;
}

// 게임 메인화면 함수
void main_show() {
	system("cls");
	gotoxy(36, 5);
	printf("               △□○ 줄다리기 △□○");
	gotoxy(36, 7);
	printf("★          이번게임은 줄다리기 입니다          ★");
	gotoxy(36, 9);
	printf("★ A와 L키 연타로 눌러서 우승한 팀은 통과입니다 ★");
	gotoxy(36, 11);
	printf("★       그럼 시작하기 눌러서 입장하십시오      ★");
	gotoxy(36, 13);
	printf("★               게임종료 = 메뉴화면            ★");
	gotoxy(36, 15);
	printf("△□○  ★★★★★★★★★★★★★★★★★★ △□○");

	gotoxy(40, 17);
	printf("●");
	gotoxy(39, 18);
	printf("＼|/");
	gotoxy(40, 19);
	printf("456");
	gotoxy(40, 20);
	printf("/＼");

	x = 6;
	y = 5;
	print_auto_y(&x, &y, " ./＼＿／＼");
	print_auto_y(&x, &y, " ／ _/　_ ＼");
	print_auto_y(&x, &y, " |　━　 ━　i");
	print_auto_y(&x, &y, " ＼= (_人_) ");
	print_auto_y(&x, &y, "   ========");
	print_auto_y(&x, &y, "  ／￣￣⌒＼/⌒)―――――――");
	print_auto_y(&x, &y, ". /　　　　＿／　");
	print_auto_y(&x, &y, ". |　　　＼");
	print_auto_y(&x, &y, "  ＼ ＼_　＼");
	print_auto_y(&x, &y, "   ＼/.＼_/");

	x = 90;
	y = 10;
	print_auto_y(&x, &y, "             ／⌒＼");
	print_auto_y(&x, &y, "           ／　   ＼");
	print_auto_y(&x, &y, "	    /　　　  ＼");
	print_auto_y(&x, &y, "	   /　　　　   ＼");
	print_auto_y(&x, &y, "	   ( / 　 　    )");
	print_auto_y(&x, &y, "	   f  　       ｜");
	print_auto_y(&x, &y, "	   | ●　　●　｜");
	print_auto_y(&x, &y, "	   |　 ▽　　　｜");
	print_auto_y(&x, &y, "         |＿＿ 　 　ノ");
	print_auto_y(&x, &y, "	   丁丁丁丁丁￣l＼");
	print_auto_y(&x, &y, "	   く(_(_(＿L＿)ノ");



	gotoxy(77, 17);
	printf(" ●");
	gotoxy(76, 18);
	printf("＼|/");
	gotoxy(77, 19);
	printf("001");
	gotoxy(77, 20);
	printf("/＼");

	gotoxy(56, 18);
	printf("게임 시작");

	gotoxy(56, 20);
	printf("게임 종료");

	print_by_name("전유리 고에스더 김민주");
}

// 메뉴 선택 커서 함수
enum MENU game() {
	int y = 0;
	while (1) {
		main_show();

		if (y <= 0)
		{
			y = 0;
		}
		else if (y >= 4)
		{
			y = 2;
		}

		gotoxy(53, 18 + y);
		printf(">");

		input = _getch();

		if (input == MAGIC_KEY)
		{
			switch (_getch())
			{
			case UP:
				gotoxy(53, 18 + y);
				printf("  ");
				y = y - 2;
				break;
			case DOWN:
				gotoxy(53, 18 + y);
				printf("  ");
				y = y + 2;
				break;
			}
		}
		else if (input == 13)
		{
			switch (y)
			{
			case 0:
				return GAMESTART;
			case 2:
				return EXIT;
			}
		}
	}
}


// 줄다리기 그려주는 함수
void line(int x, int y)
{
	system("cls");
	int i, line[21] = { 0 };
	line[10] = 1;
	line[2] = 2;
	line[18] = 2;
	gotoxy(31, 13);
	for (i = 0; i < 78; i++)
		printf(" ");

	gotoxy(28, 8);
	printf("%s", t_name1);
	gotoxy(86, 8);
	printf("%s", t_name2);

	int peple = 0;
	gotoxy(x - 16, 10);
	printf("● ● ●  ●  ●  ● ");
	gotoxy(x - 16, 11);
	printf("＼□＼□＼□□□＼□□＼□□＼");
	gotoxy(x - 15, 12);
	printf("| |  |  | | | | | |");
	gotoxy(x - 16, 13);
	printf("/＼/＼/＼/＼/＼/＼/＼");

	gotoxy(x + 37, 10);
	printf(" ●  ●  ●  ● ● ●");
	gotoxy(x + 34, 11);
	printf("/□/□/□□□/|□/□□/");
	gotoxy(x + 37, 12);
	printf(" | | | |  |  | | | |");
	gotoxy(x + 37, 13);
	printf("/＼/＼/＼/＼/＼/＼/＼");

	gotoxy(0, 14);
	printf("■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(77, 14);
	printf("■■■■■■■■■■■■■■■■■■■■■");

	gotoxy(40, 24);
	printf("● ＼__ /_          /●/__-_       ＼●_   _/  (");
	gotoxy(28, 25);
	printf("▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲");

	// x,y함수로 line그려줌 x =40, y = 11
	gotoxy(x, 11);
	for (i = 0; i < 21; i++)
		if (line[i] == 0)
			printf("□");
		else if (line[i] == 1)
			printf("■");
		else
			printf("◆");

	//공중 줄 그리기
	for (int i = 0; i <= 9; i++) {
		gotoxy(58, i);
		printf("  |  ");
	}
	gotoxy(60, 10);
	printf("▼");
	gotoxy(60, 12);
	printf("▲");
	gotoxy(44, 2);
	printf("움직이지 않는다면 한영키를 바꾸십시오.");


	gotoxy(45, 27);
	printf("메뉴로 돌아가려면 ESC를 눌러주세요\n");

	char end = _getch();
	if (end == ESC) {
		main_pushpull();
	}
}

void start_game() {
	system("cls");
	gotoxy(62, 12);
	printf("VS");
	gotoxy(45, 9);
	printf("게임을 진행할 팀 등록을 진행하십시오\n");
	gotoxy(25, 12);
	printf("첫번째 팀 이름입력 후 엔터> ");
	scanf_s("%s", &t_name1, 20);
	gotoxy(68, 12);
	printf("두번째 팀 이름입력 후 엔터> ");
	scanf_s("%s", &t_name2, 20);
	// 이름 입력 후 화면 지우기
	system("cls");
	//line 그려줌
	line(x, y);
	//게임함수 실행
	game_fun();
}

void game_fun() {
	while (1) {
		char click = _getch();

		switch (click) {
		case A: case a: // A
			x -= 2;
			line(x, y);
			Sleep(100);
			if (x <= 25) {
				gotoxy(78, 14);
				printf("                                         ");
				Sleep(500);
				system("color 40");
				Sleep(1000);
				system("color 0C");
				system("cls");
				print_by_text(t_name1, "RED", 55, 15);
				gotoxy(48, 17);
				printf("2초 뒤 메인화면으로 돌아갑니다.");
				Sleep(2000);
				main_pushpull();
			}
			break;

		case L: case l: // L
			x += 2;
			line(x, y);
			Sleep(100);
			if (x >= 55) {
				gotoxy(0, 14);
				printf("                                              ");
				Sleep(500);
				system("color 40");
				Sleep(1000);
				system("color 0C");
				system("cls");
				print_by_text(t_name1, "RED", 55, 15);
				gotoxy(48, 17);
				printf("2초 뒤 메인화면으로 돌아갑니다.");
				Sleep(2000);
				main_pushpull();
			}
			break;
		case ESC:
			main_pushpull();
		}
	}
}